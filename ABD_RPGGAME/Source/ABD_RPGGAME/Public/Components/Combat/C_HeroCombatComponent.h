

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/C_PawnCombatComponent.h"
#include "C_HeroCombatComponent.generated.h"


class AWarriorHeroWeapon;

/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UC_HeroCombatComponent : public UC_PawnCombatComponent
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "Warrior|Combat")

	AWarriorHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;


};
