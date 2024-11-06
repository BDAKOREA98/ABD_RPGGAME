

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "C_DataAsset_StartUpDataBase.generated.h"

class UC_WarriorGameplayAbility;
class UC_WarriorAbilityComponent;
class UGameplayEffect;
/**
 * 	
 */

UCLASS()
class ABD_RPGGAME_API UC_DataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:

	virtual void GiveToAbilitySystemComponent(UC_WarriorAbilityComponent* InASCToGive, int32 ApplyLevel = 1);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray <TSubclassOf< UC_WarriorGameplayAbility> > ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray <TSubclassOf< UC_WarriorGameplayAbility> > ReactivateAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray< TSubclassOf< UGameplayEffect> > StartUpGameplayEffect;


	void GrantAbilities(const TArray <TSubclassOf< UC_WarriorGameplayAbility> >& InAbilitiesToGive, UC_WarriorAbilityComponent* InASCToGive, int32 ApplyLevel = 1);

};
