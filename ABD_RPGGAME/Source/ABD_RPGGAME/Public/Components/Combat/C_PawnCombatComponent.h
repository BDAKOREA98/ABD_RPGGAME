

#pragma once

#include "CoreMinimal.h"
#include "Components/C_PawnExtensionComponentBase.h"
#include "GameplayTagContainer.h"
#include "C_PawnCombatComponent.generated.h"


class AWarriorWeaponBase;
/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UC_PawnCombatComponent : public UC_PawnExtensionComponentBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false );

	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	AWarriorWeaponBase* GetCreatureCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;


	UPROPERTY(BlueprintReadWrite, Category = "Warrior|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")
	AWarriorWeaponBase* GetCreatureCurrentEquippedWeapon() const;


private:

	TMap<FGameplayTag, AWarriorWeaponBase*> CraetureCarriedWeaponMap;


	
};
