

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Item_PickUpBase.generated.h"

class USphereComponent;
UCLASS()
class ABD_RPGGAME_API AC_Item_PickUpBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Item_PickUpBase();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Pick Up Interaction")
	USphereComponent* PickUpCollisionSphere;

	UFUNCTION()
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
