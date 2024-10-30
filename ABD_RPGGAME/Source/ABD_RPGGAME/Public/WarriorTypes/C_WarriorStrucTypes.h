

#pragma once

#include "C_WarriorStrucTypes.generated.h"

class UC_WarriorLinkedLayer;
USTRUCT(BlueprintType)
struct FWarriorHeroWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf< UC_WarriorLinkedLayer> WeaponAnimLayerToLink;

};