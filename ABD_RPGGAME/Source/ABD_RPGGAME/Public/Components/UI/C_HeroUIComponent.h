

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/C_PawnUIComponent.h"
#include "C_HeroUIComponent.generated.h"

/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UC_HeroUIComponent : public UC_PawnUIComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentRageChanged;

	
};
