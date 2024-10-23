// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "C_Creature.generated.h"

class UC_WarriorAbilityComponent;
class UC_WarriorAttributeSet;
class UAbilitySystemComponent;
UCLASS()
class ABD_RPGGAME_API AC_Creature : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_Creature();

	//Begin IAbilitySystemInterface Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	//End IAbilitySystemInterface Interface
protected:
	//begin APwan interfece
	virtual void PossessedBy(AController* NewController) override;

	//End APwan interfece
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UC_WarriorAbilityComponent* WarriorAbilityComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UC_WarriorAttributeSet* WarriorAttributeSet;

public:
	FORCEINLINE UC_WarriorAbilityComponent* GetWarriorAbilitySystemComponent() const { return WarriorAbilityComponent; }
	FORCEINLINE UC_WarriorAttributeSet* GetWarriorAttributeSet() const { return WarriorAttributeSet; }


};
