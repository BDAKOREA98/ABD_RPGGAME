


#include "WarriorFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/C_WarriorAbilityComponent.h"
#include "Interface/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "WArriorGameplayTags.h"
#include "WarriorTypes/WarriorCountDownAction.h"
#include "C_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/C_SaveGame.h"

#include "WarriorDebugHelper.h"
UC_WarriorAbilityComponent* UWarriorFunctionLibrary::NativeGetWarriorASCFromActor(AActor* InActor)
{
    check(InActor);
    return CastChecked<UC_WarriorAbilityComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
    UC_WarriorAbilityComponent* ASC =   NativeGetWarriorASCFromActor(InActor);

    if (!ASC->HasMatchingGameplayTag(TagToAdd))
    {
        ASC->AddLooseGameplayTag(TagToAdd);
    }

}

void UWarriorFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
    UC_WarriorAbilityComponent* ASC = NativeGetWarriorASCFromActor(InActor);

    if (ASC->HasMatchingGameplayTag(TagToRemove))
    {
        ASC->RemoveLooseGameplayTag(TagToRemove);
    }

}

bool UWarriorFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
    UC_WarriorAbilityComponent* ASC = NativeGetWarriorASCFromActor(InActor);
    return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UWarriorFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EWarriorConfirmType& OutConfirmType)
{

    OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EWarriorConfirmType::YES : EWarriorConfirmType::NO;


}

UC_PawnCombatComponent* UWarriorFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
    check(InActor);
    if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
    {
        return PawnCombatInterface->GetPawnCombatComponent();
    }

    return nullptr;
}

UC_PawnCombatComponent* UWarriorFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, EWarriorValidType& OutValidType)
{
    UC_PawnCombatComponent* CombatComponent =    NativeGetPawnCombatComponentFromActor(InActor);
    OutValidType = CombatComponent ? EWarriorValidType::Valid : EWarriorValidType::InValid;

    return CombatComponent;
}

bool UWarriorFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
    check(QueryPawn && TargetPawn);

    IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
    IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

    if (QueryTeamAgent && TargetTeamAgent)
    {
        return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
    }


    return false;
}

float UWarriorFunctionLibrary::GetScalableFloatBalueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{

    return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UWarriorFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDiffenece)
{
    check(InAttacker && InVictim);
    const FVector VictimForwad = InVictim->GetActorForwardVector();
    const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

    const float DotResult =  FVector::DotProduct(VictimForwad, VictimToAttackerNormalized);
    OutAngleDiffenece =       UKismetMathLibrary::DegAcos(DotResult);

    
    const FVector CrossResult = FVector::CrossProduct(VictimForwad, VictimToAttackerNormalized);

    if (CrossResult.Z <0.0f)
    {
        OutAngleDiffenece *= -1.f;

    }

    if (OutAngleDiffenece >= -45.f && OutAngleDiffenece <= 45.f)
    {
        return WarriorGamePlayTags::Shared_Status_HitReact_Front;
    }
    else if (OutAngleDiffenece < -45.f && OutAngleDiffenece >= -135.f)
    {
        return WarriorGamePlayTags::Shared_Status_HitReact_Left;

    }
    else if (OutAngleDiffenece < -135.f || OutAngleDiffenece > 135.f)
    {
        return WarriorGamePlayTags::Shared_Status_HitReact_Back;

    }
    else if (OutAngleDiffenece > 45.f && OutAngleDiffenece <= 135.f)
    {
        return WarriorGamePlayTags::Shared_Status_HitReact_Right;

    }



    return WarriorGamePlayTags::Shared_Status_HitReact_Front;
}

bool UWarriorFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
    check(InAttacker && InDefender);

    const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());



    //const FString DebugString = FString::Printf(TEXT("Dot Result : %f %f"), DotResult, DotResult < -0.1f ? TEXT("Valid Block") : TEXT("InvalidBlock"));
    //
    // Print(DebugString, DotResult < -0.1f ? FColor::Green : FColor::Red);



    return DotResult < -0.1f ;
}

bool UWarriorFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
    UC_WarriorAbilityComponent* SourceASC = NativeGetWarriorASCFromActor(InInstigator);
    UC_WarriorAbilityComponent* TargetASC = NativeGetWarriorASCFromActor(InTargetActor);

    FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);



    return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

void UWarriorFunctionLibrary::CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime, EWarriorCountDownActionInput CountDownInput, UPARAM(DisplayName = "Output") EWarriorCountDownActionOutput& CountDownOutPut, FLatentActionInfo LatentInfo)
{
    UWorld* World = nullptr;
    
    if (GEngine)
    {
       World =  GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
    }

    if (!World)
    {
        return;
    }

    
    FLatentActionManager& LatentActionManager = World->GetLatentActionManager();

    FWarriorCountDownAction* FoundAction = LatentActionManager.FindExistingAction<FWarriorCountDownAction>(LatentInfo.CallbackTarget,LatentInfo.UUID);

    if (CountDownInput == EWarriorCountDownActionInput::Start)
    {
        if (!FoundAction)
        {
            LatentActionManager.AddNewAction(
                LatentInfo.CallbackTarget,
                LatentInfo.UUID,
                new FWarriorCountDownAction(TotalTime, UpdateInterval, OutRemainingTime, CountDownOutPut, LatentInfo)

            );


        }
    }

    if (CountDownInput == EWarriorCountDownActionInput::Cancel)
    {
        if (FoundAction)
        {
            FoundAction->CancelAction();

        }
    }

}

UC_GameInstance* UWarriorFunctionLibrary::GetGameInstance(const UObject* WorldContextObject)
{
    if (GEngine)
    {
        if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
        {
            return World->GetGameInstance<UC_GameInstance>();
        } 
    }
    return nullptr;
}

void UWarriorFunctionLibrary::ToggleInputMode(const UObject* WorldContextObject, EInputMode InInputMode)
{
    APlayerController* PlayerController = nullptr;

    if (GEngine)
    {
        if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
        {
            PlayerController = World->GetFirstPlayerController();
        }
    }

    if (!PlayerController)
    {
        return;
    }

    FInputModeGameOnly GameOnlyMode;
    FInputModeUIOnly UIOnlyMode;
    switch (InInputMode)
    {
    case EInputMode::GameOnly:
        PlayerController->SetInputMode(GameOnlyMode);
        PlayerController->bShowMouseCursor = false;

        break;
    case EInputMode::UIOnly:
        PlayerController->SetInputMode(UIOnlyMode);
        PlayerController->bShowMouseCursor = true;
        break;
    default:
        break;
    }

}

void UWarriorFunctionLibrary::SaveCurrentGameDifficulty(EGameDifficulty InDifficultyToSave)
{
    USaveGame* SaveGameObject =  UGameplayStatics::CreateSaveGameObject(UC_SaveGame::StaticClass());
    if (UC_SaveGame* WarriorSaveGameObject =   Cast<UC_SaveGame>(SaveGameObject))
    {
        WarriorSaveGameObject->SavedCurrentGameDifficulty = InDifficultyToSave;

        const bool bWasSaved = UGameplayStatics::SaveGameToSlot(WarriorSaveGameObject, WarriorGamePlayTags::GameData_SaveGame_Slot_1.GetTag().ToString(),0);
       // Debug::Print(bWasSaved ? TEXT("Difficulty Saved") : TEXT("Difficulty No Saved"));

    }

}

bool UWarriorFunctionLibrary::TryLoadSavedGameDifficulty(EGameDifficulty& OutDifficultyToSave)
{
    if (UGameplayStatics::DoesSaveGameExist(WarriorGamePlayTags::GameData_SaveGame_Slot_1.GetTag().ToString(), 0))
    {
        USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(WarriorGamePlayTags::GameData_SaveGame_Slot_1.GetTag().ToString(), 0);

        if (UC_SaveGame* WarriorSaveGameObject = Cast<UC_SaveGame>(SaveGameObject))
        {
            OutDifficultyToSave = WarriorSaveGameObject->SavedCurrentGameDifficulty;

            //Debug::Print(TEXT("Loading Successful"), FColor::Green);

            return true;
        }

    }

    return false;

}


