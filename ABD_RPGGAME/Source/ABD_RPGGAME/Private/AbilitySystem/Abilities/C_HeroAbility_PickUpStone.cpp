


#include "AbilitySystem/Abilities/C_HeroAbility_PickUpStone.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Creature/C_Warrior.h"
#include "Items/PickUp/C_Item_StoneBase.h"
#include "Components/UI/C_HeroUIComponent.h"

void UC_HeroAbility_PickUpStone::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	GetHeroUIComponentActorInfo()->OnStoneInteracted.Broadcast(true);


	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UC_HeroAbility_PickUpStone::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	GetHeroUIComponentActorInfo()->OnStoneInteracted.Broadcast(false);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);


}

void UC_HeroAbility_PickUpStone::CollectStones()
{
	CollectedStones.Empty();
	
	TArray<FHitResult> TraceHits;


	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetHeroCharacterFromActorInfo(),
		GetHeroCharacterFromActorInfo()->GetActorLocation(),
		GetHeroCharacterFromActorInfo()->GetActorLocation() + GetHeroCharacterFromActorInfo()->GetActorUpVector() * BoxTraceDistance,
		TraceBoxSize / 2.f,
		GetHeroCharacterFromActorInfo()->GetActorUpVector().ToOrientationRotator(),
		StoneTraceChannel,
		false,
		TArray<AActor*>(),
		bDrawDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		TraceHits,
		true
	);

	for (const FHitResult& TraceHit : TraceHits)
	{
		if (AC_Item_StoneBase* FoundStone = Cast<AC_Item_StoneBase>(TraceHit.GetActor()))
		{
			CollectedStones.AddUnique(FoundStone);
		}
	}

	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}


}

void UC_HeroAbility_PickUpStone::ConsumeStones()
{
	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
		return;
	}

	for (AC_Item_StoneBase* CollectedStone : CollectedStones)
	{
		if (CollectedStone)
		{
			CollectedStone->Consume(GetWarriorAbilitySystemComponentFromActorInfo(), GetAbilityLevel());

		}
	}

}
