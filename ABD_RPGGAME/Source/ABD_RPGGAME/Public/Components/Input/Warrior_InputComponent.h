// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Warrior_InputComponent.generated.h"

/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UWarrior_InputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	template<class UserObject, typename CallbackFunc>

	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc);
	


};

template<class UserObject, typename CallbackFunc>
inline void UWarrior_InputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	
	checkf(InInputConfig, TEXT("Input config data asset is null, can not proceed with binding"));

	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}

}
