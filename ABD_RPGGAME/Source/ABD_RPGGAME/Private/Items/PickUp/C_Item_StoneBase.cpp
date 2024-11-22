


#include "Items/PickUp/C_Item_StoneBase.h"
#include "Creature/C_Warrior.h"
#include "AbilitySystem/C_WarriorAbilityComponent.h"
#include "WArriorGameplayTags.h"

void AC_Item_StoneBase::Consume(UC_WarriorAbilityComponent* AbilitySystemComponent, int32 ApplyLevel)
{
	check(StoneGameplayEffectClass);

	UGameplayEffect* EffectCDO = StoneGameplayEffectClass->GetDefaultObject<UGameplayEffect>();

	AbilitySystemComponent->ApplyGameplayEffectToSelf(
		EffectCDO,
		ApplyLevel,
		AbilitySystemComponent->MakeEffectContext()
	);

	BP_OnStoneConsumed();



}
void AC_Item_StoneBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AC_Warrior* OverlappedHeroCharacter = Cast<AC_Warrior>(OtherActor))
	{
		OverlappedHeroCharacter->GetWarriorAbilitySystemComponent()->TryActivateAbilityByTag(WarriorGamePlayTags::Player_Ability_PickUp_Stone);


	}

}
