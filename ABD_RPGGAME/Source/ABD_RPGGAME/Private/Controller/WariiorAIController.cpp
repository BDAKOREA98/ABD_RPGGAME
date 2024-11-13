


#include "Controller/WariiorAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"



#include "WarriorDebugHelper.h"
AWariiorAIController::AWariiorAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	if (UCrowdFollowingComponent* CrowdComp = Cast< UCrowdFollowingComponent> (GetPathFollowingComponent()))
	{
		Debug::Print(TEXT("CrowdComponent Valid"), FColor::Green);
	}

	EnemyAISenseConfig_Sight = CreateDefaultSubobject< UAISenseConfig_Sight>("EnemyAISenseConfig_Sight");
	EnemyAISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	EnemyAISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	EnemyAISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	EnemyAISenseConfig_Sight->SightRadius = 5000.f;
	EnemyAISenseConfig_Sight->LoseSightRadius = 0.f;
	EnemyAISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f;


	EnemyPerceptionComponent = CreateDefaultSubobject< UAIPerceptionComponent>("EnemyPerceptionComponent");
	EnemyPerceptionComponent->ConfigureSense(*EnemyAISenseConfig_Sight);
	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPercepationUpdated);


	SetGenericTeamId(FGenericTeamId(1));


}

ETeamAttitude::Type AWariiorAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* PawnToCheck = Cast<const APawn>(&Other);
	

	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(PawnToCheck->GetController());
	
	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() != GetGenericTeamId())
	{
		return ETeamAttitude::Hostile;
	}

	return ETeamAttitude::Friendly;


}

void AWariiorAIController::OnEnemyPercepationUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed() && Actor)
	{
		Debug::Print(Actor->GetActorNameOrLabel() + TEXT(" Was Sensed"), FColor::Green);

	}
}
