// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_WarriorAnimInstance.h"
#include "C_WarriorHeroAnimInstance.generated.h"

class AC_Warrior;



/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UC_WarriorHeroAnimInstance : public UC_WarriorAnimInstance
{
	GENERATED_BODY()
public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	


protected:

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "AnimData|Refrences")
	AC_Warrior* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "AnimData|LocomotionData")
	bool bShouldEnterRelaxState;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "AnimData|LocomotionData")
	float EnterRelaxStateThreshold = 2.0f;

	float IdleElpasedTime;


};
