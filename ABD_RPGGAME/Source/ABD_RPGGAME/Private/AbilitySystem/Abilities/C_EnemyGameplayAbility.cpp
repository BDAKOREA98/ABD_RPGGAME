


#include "AbilitySystem/Abilities/C_EnemyGameplayAbility.h"
#include "Creature/C_Enemy.h"
#include "Components/Combat/C_EnemyCombatComponent.h"
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
