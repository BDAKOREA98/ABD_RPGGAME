// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_CreatureAnimInstance.h"
#include "C_WarriorAnimInstance.generated.h"


class AC_Creature;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UC_WarriorAnimInstance : public UC_CreatureAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
	void NormalizeDirection();


protected:

	UPROPERTY()
	AC_Creature* OwnerCreature;

	UPROPERTY()
	UCharacterMovementComponent* OwnerMovement;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "AnimData|LocomotionData")
	float LocomotionDirection;



};
