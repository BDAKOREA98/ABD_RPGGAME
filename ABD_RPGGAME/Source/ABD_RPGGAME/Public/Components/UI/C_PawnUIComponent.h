

#pragma once

#include "CoreMinimal.h"
#include "Components/C_PawnExtensionComponentBase.h"
#include "C_PawnUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangedDelegate, float, NewPercent);

/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UC_PawnUIComponent : public UC_PawnExtensionComponentBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentHealthChanged;

	
	

};
