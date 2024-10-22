// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Creature/C_Creature.h"
#include "C_Warrior.generated.h"

class USpringArmComponent;
class UCameraComponent;


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

	virtual void BeginPlay() override;

private:

#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;



#pragma endregion


};
