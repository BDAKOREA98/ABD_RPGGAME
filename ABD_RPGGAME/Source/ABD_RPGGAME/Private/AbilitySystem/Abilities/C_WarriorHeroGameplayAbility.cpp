


#include "AbilitySystem/Abilities/C_WarriorHeroGameplayAbility.h"
#include "Creature/C_Warrior.h"
#include "Controller/C_WarriorController.h"
#include "AbilitySystem/C_WarriorGameplayAbility.h"
AC_Warrior* UC_WarriorHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if (!CachedWarriorHeroCharacter.IsValid())
	{
		CachedWarriorHeroCharacter = Cast<AC_Warrior>(CurrentActorInfo->AvatarActor);
	}
	
	
	



	return CachedWarriorHeroCharacter.IsValid()? CachedWarriorHeroCharacter.Get() : nullptr;


}

AC_WarriorController* UC_WarriorHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if (!CachedWarriorHeroController.IsValid())
	{
		CachedWarriorHeroController = Cast<AC_WarriorController>(CurrentActorInfo->PlayerController);

	}

	return CachedWarriorHeroController.IsValid()? CachedWarriorHeroController.Get() : nullptr;
}

UC_HeroCombatComponent* UC_WarriorHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

FGameplayEffectSpecHandle UC_WarriorHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InCurrentComboCount)
{
	check(EffectClass);

	
	return FGameplayEffectSpecHandle();
}
