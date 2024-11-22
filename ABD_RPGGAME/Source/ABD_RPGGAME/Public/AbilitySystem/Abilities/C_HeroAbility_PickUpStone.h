

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/C_WarriorHeroGameplayAbility.h"
#include "C_HeroAbility_PickUpStone.generated.h"

class AC_Item_StoneBase;
/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UC_HeroAbility_PickUpStone : public UC_WarriorHeroGameplayAbility
{
	GENERATED_BODY()
protected:
	// Begin UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	// End UGameplayAbility Interface	

	UFUNCTION(BlueprintCallable)
	void CollectStones();

	UFUNCTION(BlueprintCallable)
	void ConsumeStones();


private:

	UPROPERTY(EditDefaultsOnly)
	float BoxTraceDistance = 50.f;

	UPROPERTY(EditDefaultsOnly)
	FVector TraceBoxSize = FVector(100.f);
	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<	EObjectTypeQuery> > StoneTraceChannel;

	UPROPERTY(EditDefaultsOnly)
	bool bDrawDebugShape = false;
	
	UPROPERTY()
	TArray< AC_Item_StoneBase*> CollectedStones;



};
