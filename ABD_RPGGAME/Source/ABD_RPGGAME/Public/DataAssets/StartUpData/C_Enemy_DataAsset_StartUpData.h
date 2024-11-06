

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/C_DataAsset_StartUpDataBase.h"
#include "C_Enemy_DataAsset_StartUpData.generated.h"

class UC_EnemyGameplayAbility;

/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UC_Enemy_DataAsset_StartUpData : public UC_DataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UC_WarriorAbilityComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf < UC_EnemyGameplayAbility >> EnemyCombatAbilities;

	

	
};
