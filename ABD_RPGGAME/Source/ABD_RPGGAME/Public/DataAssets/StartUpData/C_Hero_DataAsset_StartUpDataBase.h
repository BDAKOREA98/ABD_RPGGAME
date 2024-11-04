

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/C_DataAsset_StartUpDataBase.h"
#include "WarriorTypes/C_WarriorStrucTypes.h"
#include "GameplayTagContainer.h"
#include "C_Hero_DataAsset_StartUpDataBase.generated.h"




class UC_WarriorAbilityComponent;

/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UC_Hero_DataAsset_StartUpDataBase : public UC_DataAsset_StartUpDataBase
{


	GENERATED_BODY()


public:
	virtual void GiveToAbilitySystemComponent(UC_WarriorAbilityComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FWarriorHeroAbilitySet> HeroStartUpAbilitySets;
	
};
