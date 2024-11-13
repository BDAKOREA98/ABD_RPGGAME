


#include "Components/Combat/C_EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "WArriorGameplayTags.h"

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

	const bool bIsPlayerBlocking = false;

	const bool bIsMyAttackUnblockable = false;

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		//TODO :: Check if the block is valid
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;



	if (bIsValidBlock)
	{
		//TODO::Handle Successful block
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
