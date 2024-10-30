// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapons/WarriorWeaponBase.h"
#include "WarriorTypes/C_WarriorStrucTypes.h"
#include "WarriorHeroWeapon.generated.h"

/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API AWarriorHeroWeapon : public AWarriorWeaponBase
{
	GENERATED_BODY()


public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FWarriorHeroWeaponData HeroWeaponData;


	
};
