

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/C_WarriorGameplayAbility.h"
#include "C_EnemyGameplayAbility.generated.h"

class AC_Enemy;
class UC_EnemyCombatComponent;
/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UC_EnemyGameplayAbility : public UC_WarriorGameplayAbility
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure, Category="Warrior|Ability")
	AC_Enemy* GetEnemyCharacterFromActorInfor();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	UC_EnemyCombatComponent* GetEnemyCombatComponentFromActorInfor();

private:

	TWeakObjectPtr<AC_Enemy> CachedWarriorEnemyCharacter;
	
};
