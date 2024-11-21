

#pragma once
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "C_WarriorStrucTypes.generated.h"

class UC_WarriorLinkedLayer;
class UC_WarriorGameplayAbility;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FWarriorHeroAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<UC_WarriorGameplayAbility> AbilityToGrant;

	bool IsValid() const;

};
USTRUCT(BlueprintType)
struct FWarriorHeroSpecialAbilitySet : public FWarriorHeroAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (Categories = "Player.Colldown"))
	TSoftObjectPtr<UMaterialInterface> AbilityIconMaterial;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FGameplayTag AbilityColldownTag;





};



USTRUCT(BlueprintType)
struct FWarriorHeroWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf< UC_WarriorLinkedLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FWarriorHeroAbilitySet> DefaultWeaponAbilities;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FWarriorHeroSpecialAbilitySet> DefaultSpecialWeaponAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)

	FScalableFloat WeaponBaseDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> SoftWeaponIconTexture;

};