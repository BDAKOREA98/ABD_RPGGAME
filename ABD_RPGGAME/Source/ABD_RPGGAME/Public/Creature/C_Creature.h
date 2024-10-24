// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "C_Creature.generated.h"

class UC_WarriorAbilityComponent;
class UC_WarriorAttributeSet;
class UAbilitySystemComponent;
class UC_DataAsset_StartUpDataBase;

UCLASS()
class ABD_RPGGAME_API AC_Creature : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Creature();

	//Begin IAbilitySystemInterface Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//End IAbilitySystemInterface Interface
protected:
	//begin APwan interfece
	virtual void PossessedBy(AController* NewController) override;

	//End APwan interfece
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UC_WarriorAbilityComponent* WarriorAbilityComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UC_WarriorAttributeSet* WarriorAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UC_DataAsset_StartUpDataBase> CharacterStartUpData;



public:
	FORCEINLINE UC_WarriorAbilityComponent* GetWarriorAbilitySystemComponent() const { return WarriorAbilityComponent; }
	FORCEINLINE UC_WarriorAttributeSet* GetWarriorAttributeSet() const { return WarriorAttributeSet; }


};
