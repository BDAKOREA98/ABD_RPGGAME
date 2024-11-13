// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "C_WarriorController.generated.h"

/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API AC_WarriorController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()


public:
	AC_WarriorController();

	
	// Begin IGenericTeamAgentInterface Interface.
	virtual FGenericTeamId GetGenericTeamId() const;
	// End IGenericTeamAgentInterface Interface.


private:
	FGenericTeamId HeroTeamID;


};
