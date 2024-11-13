

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "C_BTS_OrientToTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UC_BTS_OrientToTargetActor : public UBTService
{
	GENERATED_BODY()
	
	UC_BTS_OrientToTargetActor();

	// ~ Begin UBTNode Interface

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticDescription() const override;
	// ~ End UBTNode Interface

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "Target")
	FBlackboardKeySelector InTargetActorKey;

	UPROPERTY(EditAnywhere, Category = "Target")
	float RotationInterpSpeed;


};
