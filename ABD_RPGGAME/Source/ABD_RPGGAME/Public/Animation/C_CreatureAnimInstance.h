// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayTagContainer.h"
#include "C_CreatureAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UC_CreatureAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	UC_CreatureAnimInstance();

protected:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool DoesOwnerHaveTag(FGameplayTag TagToCheck) const;

};
