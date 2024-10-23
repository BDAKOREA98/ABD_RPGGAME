// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Creature/C_Creature.h"
#include "C_Warrior.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;

struct FInputActionValue;
/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API AC_Warrior : public AC_Creature
{
	GENERATED_BODY()
	
public:
	AC_Warrior();

	

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

	

#pragma endregion
#pragma region Input
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	void Input_Move(const FInputActionValue& InputActionValue);

	void Input_Look(const FInputActionValue& InputActionValue);


#pragma endregion


};
