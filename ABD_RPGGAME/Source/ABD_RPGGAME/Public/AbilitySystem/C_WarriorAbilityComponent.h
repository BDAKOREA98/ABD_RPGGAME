// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "C_WarriorAbilityComponent.generated.h"

/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UC_WarriorAbilityComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleassed(const FGameplayTag& InInputTag);

	
};
