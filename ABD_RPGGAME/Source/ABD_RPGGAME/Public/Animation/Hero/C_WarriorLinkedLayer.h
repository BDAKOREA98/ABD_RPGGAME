// Vince Petrelli All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/C_CreatureAnimInstance.h"

#include "C_WarriorLinkedLayer.generated.h"


class UC_WarriorHeroAnimInstance;

/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UC_WarriorLinkedLayer : public UC_CreatureAnimInstance
{
	GENERATED_BODY()
	
public:


	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UC_WarriorHeroAnimInstance* GetHeroAnimInstance() const;


};
