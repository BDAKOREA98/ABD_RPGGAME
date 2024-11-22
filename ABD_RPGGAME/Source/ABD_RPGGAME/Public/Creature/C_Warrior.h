// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Creature/C_Creature.h"
#include "GameplayTagContainer.h"
#include "C_Warrior.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;
class UC_HeroCombatComponent;
class UC_HeroUIComponent;

/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API AC_Warrior : public AC_Creature
{
	GENERATED_BODY()
	
public:
	AC_Warrior();

	//Begin IPawnCombatInterface Interface
	virtual UC_PawnCombatComponent* GetPawnCombatComponent() const override;
	//End IPawnCombatInterface Interface

	//Begin IPawnUIComponent Interface
	virtual UC_PawnUIComponent* GetPawnUIComponent()  const override;
	virtual UC_HeroUIComponent* GetHeroUIComponent() const;
	//End IPawnUIComponent Interface

protected:

	//begin APwan interfece
	virtual void PossessedBy(AController* NewController) override;
	//end APwan interfece

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

private:

#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UC_HeroCombatComponent* HeroCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UC_HeroUIComponent* HeroUIComponent;

	

#pragma endregion
#pragma region Input
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_SwitchTargetTriggerd(const FInputActionValue& InputActionValue);
	void Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue);

	FVector2D SwitchDirection = FVector2D::ZeroVector;

	void Input_PickUpStonesStarted(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleassed(FGameplayTag InInputTag);

#pragma endregion
public:

	FORCEINLINE UC_HeroCombatComponent* GetHeroCombatComponent() const { return HeroCombatComponent; }

};
