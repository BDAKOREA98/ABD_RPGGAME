

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnUIInterface.generated.h"

class UC_PawnUIComponent;
class UC_HeroUIComponent;
class UC_EnemyUIComponent;


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPawnUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ABD_RPGGAME_API IPawnUIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual UC_PawnUIComponent* GetPawnUIComponent() const = 0;
	virtual UC_HeroUIComponent* GetHeroUIComponent() const;
	virtual UC_EnemyUIComponent* GetEnemyUIComponent() const;

};
