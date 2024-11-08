// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interface/PawnCombatInterface.h"
#include "Interface/PawnUIInterface.h"
#include "C_Creature.generated.h"

class UC_WarriorAbilityComponent;
class UC_CreatureAttributeSet;
class UAbilitySystemComponent;
class UC_DataAsset_StartUpDataBase;


UCLASS()
class ABD_RPGGAME_API AC_Creature : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Creature();

	//Begin IAbilitySystemInterface Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//End IAbilitySystemInterface Interface

	//Begin IPawnCombatInterface Interface
	virtual UC_PawnCombatComponent* GetPawnCombatComponent() const override;
	//End IPawnCombatInterface Interface

	//Begin IPawnUIComponent Interface
	virtual UC_PawnUIComponent* GetPawnUIComponent()  const override;
	
	//End IPawnUIComponent Interface

protected:
	//begin APwan interfece
	virtual void PossessedBy(AController* NewController) override;
	//End APwan interfece
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UC_WarriorAbilityComponent* WarriorAbilityComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UC_CreatureAttributeSet* WarriorAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UC_DataAsset_StartUpDataBase> CharacterStartUpData;




public:
	FORCEINLINE UC_WarriorAbilityComponent* GetWarriorAbilitySystemComponent() const { return WarriorAbilityComponent; }
	FORCEINLINE UC_CreatureAttributeSet* GetWarriorAttributeSet() const { return WarriorAttributeSet; }
	

};
