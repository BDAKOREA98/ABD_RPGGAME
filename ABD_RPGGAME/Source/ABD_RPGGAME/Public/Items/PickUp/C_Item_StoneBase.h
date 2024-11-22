

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUp/C_Item_PickUpBase.h"
#include "C_Item_StoneBase.generated.h"

class UC_WarriorAbilityComponent;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API AC_Item_StoneBase : public AC_Item_PickUpBase
{
	GENERATED_BODY()

public:
	void Consume(UC_WarriorAbilityComponent* AbilitySystemComponent, int32 ApplyLevel);


protected:
	virtual void OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Stone Consumed"))
	void BP_OnStoneConsumed();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> StoneGameplayEffectClass;

};
