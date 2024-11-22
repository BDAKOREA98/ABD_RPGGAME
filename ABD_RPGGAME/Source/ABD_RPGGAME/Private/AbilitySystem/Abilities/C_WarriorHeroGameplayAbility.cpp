



#include "AbilitySystem/Abilities/C_WarriorHeroGameplayAbility.h"
#include "Creature/C_Warrior.h"
#include "Controller/C_WarriorController.h"
#include "AbilitySystem/C_WarriorAbilityComponent.h"
#include "WArriorGameplayTags.h"
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

UC_HeroUIComponent* UC_WarriorHeroGameplayAbility::GetHeroUIComponentActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroUIComponent();
}

FGameplayEffectSpecHandle UC_WarriorHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetWarriorAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetWarriorAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
		);

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		WarriorGamePlayTags::Shared_SetByCaller_BaseDamage,
		InWeaponBaseDamage

	);


	if (InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
	}





	return EffectSpecHandle;
}

bool UC_WarriorHeroGameplayAbility::GetAbilityRemaningCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemaningCooldownTime)
{

	check(InCooldownTag.IsValid()); 
	FGameplayEffectQuery CooldownQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(InCooldownTag.GetSingleTagContainer());

	TArray<TPair<float,float>> TimeRemainingAndDuration = GetAbilitySystemComponentFromActorInfo()->GetActiveEffectsTimeRemainingAndDuration(CooldownQuery);
	
	if (!TimeRemainingAndDuration.IsEmpty())
	{
		RemaningCooldownTime =	TimeRemainingAndDuration[0].Key;
		TotalCooldownTime =	TimeRemainingAndDuration[0].Value;

	}

	return RemaningCooldownTime > 0.f;
}
