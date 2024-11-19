


#include "WarriorFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/C_WarriorAbilityComponent.h"
#include "Interface/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "WArriorGameplayTags.h"


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
    //Debug::Print(DebugString, DotResult < -0.1f ? FColor::Green : FColor::Red);



    return DotResult < -0.1f ;
}

bool UWarriorFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
    UC_WarriorAbilityComponent* SourceASC = NativeGetWarriorASCFromActor(InInstigator);
    UC_WarriorAbilityComponent* TargetASC = NativeGetWarriorASCFromActor(InTargetActor);

    FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);



    return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}


