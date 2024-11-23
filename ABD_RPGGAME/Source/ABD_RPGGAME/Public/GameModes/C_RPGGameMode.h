// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WarriorTypes/WarriorEnumType.h"
#include "C_RPGGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API AC_RPGGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AC_RPGGameMode();

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Game Settings")
	EGameDifficulty CurrentGameDifficulty;

public:

	FORCEINLINE EGameDifficulty GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }


};
