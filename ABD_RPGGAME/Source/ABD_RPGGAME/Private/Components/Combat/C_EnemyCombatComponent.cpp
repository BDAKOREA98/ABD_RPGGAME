


#include "Components/Combat/C_EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "WArriorGameplayTags.h"
#include "WarriorFunctionLibrary.h"
#include "Creature/C_Enemy.h"
#include "Components/BoxComponent.h"


#include "WarriorDebugHelper.h"

void UC_EnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{

	if (OverlappedActors.Contains(HitActor))
	{
		return;

	}

	OverlappedActors.AddUnique(HitActor);

	//TODO :: Implement block check

	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = UWarriorFunctionLibrary::NativeDoesActorHaveTag(HitActor, WarriorGamePlayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable= UWarriorFunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), WarriorGamePlayTags::Enemy_Status_Unblockable);

	

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		bIsValidBlock = UWarriorFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;



	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			WarriorGamePlayTags::Player_Event_SuccessfulBlock,
			EventData
		);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			WarriorGamePlayTags::Shared_Event_MeleeHit,
			EventData
		);
	}


}

void UC_EnemyCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	AC_Enemy* OwningEnemy = GetOwningPawn<AC_Enemy>();

	check(OwningEnemy);

	UBoxComponent* LeftHand = OwningEnemy->GetLeftHandCollisionBox();
	UBoxComponent* RightHand = OwningEnemy->GetRightHandCollisionBox();

	check(LeftHand && RightHand);

	switch (ToggleDamageType)
	{
	
	case EToggleDamageType::LeftHand:
		LeftHand->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	case EToggleDamageType::RightHand:
		RightHand->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	default:
		break;
	}

	if (!bShouldEnable)
	{
		OverlappedActors.Empty();

	}


}
