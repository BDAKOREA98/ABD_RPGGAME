

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "WarriorTypes/WarriorEnumType.h"
#include "C_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UC_SaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	EGameDifficulty SavedCurrentGameDifficulty;

	
};
