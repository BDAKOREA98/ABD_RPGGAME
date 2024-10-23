// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FWarriorInputActionConfig
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UInputAction* InputAction;

};


/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (TitleProperty = "InputTag"))
	TArray<FWarriorInputActionConfig> NativeInputActions;

	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag) const;


};
