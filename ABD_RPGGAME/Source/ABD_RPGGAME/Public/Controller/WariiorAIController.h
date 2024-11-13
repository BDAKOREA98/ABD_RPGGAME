

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WariiorAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API AWariiorAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AWariiorAIController(const FObjectInitializer& ObjectInitializer);

	// Begin IGenericTeamAgentInterface Interface.
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const;
	// End IGenericTeamAgentInterface Interface.

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionComponent* EnemyPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* EnemyAISenseConfig_Sight;

	UFUNCTION()
	virtual void OnEnemyPercepationUpdated(AActor* Actor, FAIStimulus Stimulus);


};
