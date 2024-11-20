



#include "AbilitySystem/Abilities/C_HeroGameplayAbility_TargetLock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Creature/C_Warrior.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/C_WarriorWidgetBase.h"
#include "Controller/C_WarriorController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "WarriorFunctionLibrary.h"
#include "WArriorGameplayTags.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"

#include "WarriorDebugHelper.h"
void UC_HeroGameplayAbility_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	TryLockOnTarget();
	

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UC_HeroGameplayAbility_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ResetTargetLockMovement();
	ResetTargetLockMappingContext();
	CleanUp();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UC_HeroGameplayAbility_TargetLock::OnTargetLockTick(float DeltaTime)
{
	if (!CurrentLockedActor ||
		UWarriorFunctionLibrary::NativeDoesActorHaveTag(CurrentLockedActor, WarriorGamePlayTags::Shared_Status_Dead) ||
		UWarriorFunctionLibrary::NativeDoesActorHaveTag(GetHeroCharacterFromActorInfo() , WarriorGamePlayTags::Shared_Status_Dead))
	{
		CancelTargetLockAbility();

		return;
	}

	SetTargetLockWidgetPosition();
	
	const bool bShouldOverrideRotation =
		!UWarriorFunctionLibrary::NativeDoesActorHaveTag(GetHeroCharacterFromActorInfo(), WarriorGamePlayTags::Player_Status_Rolling)
		&&
		!UWarriorFunctionLibrary::NativeDoesActorHaveTag(GetHeroCharacterFromActorInfo(), WarriorGamePlayTags::Player_Status_Blocking);


	if (bShouldOverrideRotation)
	{
		FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(
			GetHeroCharacterFromActorInfo()->GetActorLocation(),
			CurrentLockedActor->GetActorLocation()
		);

		LookAtRot -= FRotator(TargetLockCameraOffsetDistance_X, TargetLockCameraOffsetDistance_Y, 0.0f);


		const FRotator CurrentControlRot =GetHeroControllerFromActorInfo()->GetControlRotation();
		const FRotator TargetRot = FMath::RInterpTo(CurrentControlRot, LookAtRot, DeltaTime, TargetLockRotationInterpSpeed);

		GetHeroControllerFromActorInfo()->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.0f));
		GetHeroCharacterFromActorInfo()->SetActorRotation(FRotator(0.f, TargetRot.Yaw, 0.f));
	}


}

void UC_HeroGameplayAbility_TargetLock::SwitchTarget(const FGameplayTag& InSwitchDirectionTag)
{
	GetAvailableActorsToLock();
	TArray<AActor*> ActorsOnLeft;
	TArray<AActor*> ActorsOnRight;
	AActor* NewTargetToLock = nullptr;

	GetAvailableActorsAroundTarget(ActorsOnLeft, ActorsOnRight);

	if (InSwitchDirectionTag == WarriorGamePlayTags::Player_Event_SwitchTarget_Left)
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnLeft);
	}
	else
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnRight);
	}

	if (NewTargetToLock)
	{
		CurrentLockedActor = NewTargetToLock;
	}

}

void UC_HeroGameplayAbility_TargetLock::TryLockOnTarget()
{
	GetAvailableActorsToLock();

	if (AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	InitTargetLockMovement();
	InitTargetLockMappingContext();

	CurrentLockedActor = GetNearestTargetFromAvailableActors( AvailableActorsToLock);

	if (CurrentLockedActor)
	{
		DrawTargetLockWidget();
		SetTargetLockWidgetPosition();
	}
	else
	{
		CancelTargetLockAbility();
	}

}

void UC_HeroGameplayAbility_TargetLock::GetAvailableActorsToLock()
{
	AvailableActorsToLock.Empty();

	TArray<FHitResult> BoxTraceHits;


	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetHeroCharacterFromActorInfo(),
		GetHeroCharacterFromActorInfo()->GetActorLocation(),
		GetHeroCharacterFromActorInfo()->GetActorLocation() + GetHeroCharacterFromActorInfo()->GetActorForwardVector() * BoxTraceDistance,
		TraceBoxSize / 2.0f,
		GetHeroCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowPersistenDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		BoxTraceHits,
		true
	);

	for (const FHitResult& TraceHit : BoxTraceHits)
	{
		if (AActor* HitActor = TraceHit.GetActor())
		{
			if (HitActor != GetHeroCharacterFromActorInfo())
			{
				AvailableActorsToLock.AddUnique(HitActor);

				
			}
			

		}

	}

}

AActor* UC_HeroGameplayAbility_TargetLock::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
{
	float ClosestDistance = 0.0f;

	return UGameplayStatics::FindNearestActor(GetHeroCharacterFromActorInfo()->GetActorLocation(), InAvailableActors, ClosestDistance);

	
}

void UC_HeroGameplayAbility_TargetLock::GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight)
{
	if (!CurrentLockedActor || AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}
	const FVector PlayerLocation = GetHeroCharacterFromActorInfo()->GetActorLocation();
	const FVector PlayerToCurrentNormalized = (CurrentLockedActor->GetActorLocation() - PlayerLocation).GetSafeNormal();
	for (AActor* AvailableActor : AvailableActorsToLock)
	{

		if (!AvailableActor || AvailableActor == CurrentLockedActor)
		{
			continue;
		}
		const FVector PlayerToAvailableNormaized = (AvailableActor->GetActorLocation() - PlayerLocation).GetSafeNormal();

		const FVector CrossResult =	FVector::CrossProduct(PlayerToCurrentNormalized, PlayerToAvailableNormaized);
		if (CrossResult.Z > 0.f)
		{
			OutActorsOnRight.AddUnique(AvailableActor);
		}
		else
		{
			OutActorsOnLeft.AddUnique(AvailableActor);
		}

	}

}

void UC_HeroGameplayAbility_TargetLock::DrawTargetLockWidget()
{
	if (!TargetLockWidget)
	{
		checkf(TargetLockWidgetClass, TEXT("Forgot to assign a valid widget class in blueprint"));

		TargetLockWidget = CreateWidget< UC_WarriorWidgetBase>(GetHeroControllerFromActorInfo(), TargetLockWidgetClass);

		check(TargetLockWidget);

		TargetLockWidget->AddToViewport();
	}


	


}

void UC_HeroGameplayAbility_TargetLock::SetTargetLockWidgetPosition()
{
	if (!TargetLockWidget || !CurrentLockedActor)
	{
		CancelTargetLockAbility();
		return;
	}

	FVector2D ScreenPosition;

	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
		GetHeroControllerFromActorInfo(),
		CurrentLockedActor->GetActorLocation(),
		ScreenPosition,
		true

	);

	if (TargetLockWidgetSize == FVector2D::ZeroVector)
	{
		TargetLockWidget->WidgetTree->ForEachWidget(
			[this](UWidget* FoundWidget)
			{
				if (USizeBox* FoundSizeBox = Cast<USizeBox>(FoundWidget))
				{
					TargetLockWidgetSize.X = FoundSizeBox->GetWidthOverride();
					TargetLockWidgetSize.Y = FoundSizeBox->GetHeightOverride();


				}
			}
		);
	}

	

	ScreenPosition -= (TargetLockWidgetSize / 2.0f);
	

	TargetLockWidget->SetPositionInViewport(ScreenPosition, false);

}

void UC_HeroGameplayAbility_TargetLock::InitTargetLockMovement()
{
	CachedDefaultMaxWalkSpeed  = GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed;

	GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = TargetLockMaxWalkSpeed;


}

void UC_HeroGameplayAbility_TargetLock::InitTargetLockMappingContext()
{
	const ULocalPlayer* LocalPlayer = GetHeroControllerFromActorInfo()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* SubSystem =	ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(SubSystem);

	SubSystem->AddMappingContext(TargetLockMappingContext, 3);
}

void UC_HeroGameplayAbility_TargetLock::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);


}

void UC_HeroGameplayAbility_TargetLock::CleanUp()
{
	AvailableActorsToLock.Empty();

	CurrentLockedActor = nullptr;

	if (TargetLockWidget)
	{
		TargetLockWidget->RemoveFromParent();
	}

	TargetLockWidget = nullptr;
	TargetLockWidgetSize = FVector2D::ZeroVector;

}

void UC_HeroGameplayAbility_TargetLock::ResetTargetLockMovement()
{
	if (CachedDefaultMaxWalkSpeed > 0.f)
	{
		GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = CachedDefaultMaxWalkSpeed;
	}
}

void UC_HeroGameplayAbility_TargetLock::ResetTargetLockMappingContext()
{
	if (!GetHeroControllerFromActorInfo())
	{
		return;
	}

	const ULocalPlayer* LocalPlayer = GetHeroControllerFromActorInfo()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(SubSystem);

	SubSystem->RemoveMappingContext(TargetLockMappingContext);
}
