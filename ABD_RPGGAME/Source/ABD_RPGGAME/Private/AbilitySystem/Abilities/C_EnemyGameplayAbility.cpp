


#include "AbilitySystem/Abilities/C_EnemyGameplayAbility.h"
#include "Creature/C_Enemy.h"
#include "Components/Combat/C_EnemyCombatComponent.h"
#include "AbilitySystem/C_WarriorAbilityComponent.h"
#include "WArriorGameplayTags.h"
AC_Enemy* UC_EnemyGameplayAbility::GetEnemyCharacterFromActorInfor()
{
	if (!CachedWarriorEnemyCharacter.IsValid())
	{
		CachedWarriorEnemyCharacter = Cast<AC_Enemy>(CurrentActorInfo->AvatarActor);
	}

    return CachedWarriorEnemyCharacter.IsValid() ? CachedWarriorEnemyCharacter.Get() : nullptr;
}

UC_EnemyCombatComponent* UC_EnemyGameplayAbility::GetEnemyCombatComponentFromActorInfor()
{
    return GetEnemyCharacterFromActorInfor()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UC_EnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
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
		InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel())
	);




	return EffectSpecHandle;
}
