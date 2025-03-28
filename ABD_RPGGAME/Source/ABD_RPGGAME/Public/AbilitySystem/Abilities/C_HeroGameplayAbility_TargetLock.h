


#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/C_WarriorHeroGameplayAbility.h"
#include "C_HeroGameplayAbility_TargetLock.generated.h"

class UC_WarriorWidgetBase;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UC_HeroGameplayAbility_TargetLock : public UC_WarriorHeroGameplayAbility
{
	GENERATED_BODY()


protected:
	// Begin UGameplayAbility Interface
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	// End UGameplayAbility Interface

	UFUNCTION(BlueprintCallable)
	void OnTargetLockTick(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void SwitchTarget(const FGameplayTag& InSwitchDirectionTag);


private:

	void TryLockOnTarget();
	void GetAvailableActorsToLock();
	AActor* GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors);
	void GetAvailableActorsAroundTarget(TArray<AActor*>& OutActorsOnLeft, TArray<AActor*>& OutActorsOnRight);
	void DrawTargetLockWidget();
	void SetTargetLockWidgetPosition();
	void InitTargetLockMovement();
	void InitTargetLockMappingContext();



	void CancelTargetLockAbility();
	void CleanUp();
	void ResetTargetLockMovement();
	void ResetTargetLockMappingContext();

	UPROPERTY(EditDefaultsOnly, Category ="Target Lock")
	float BoxTraceDistance = 5000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	FVector TraceBoxSize = FVector(5000.0f, 5000.0f, 300.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	TArray<TEnumAsByte<	EObjectTypeQuery> > BoxTraceChannel;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	bool bShowPersistenDebugShape = false;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	TSubclassOf<UC_WarriorWidgetBase> TargetLockWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float TargetLockRotationInterpSpeed = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float TargetLockMaxWalkSpeed = 150.f;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	UInputMappingContext* TargetLockMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float TargetLockCameraOffsetDistance_X = 20.f; 
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float TargetLockCameraOffsetDistance_Y = 20.f;

	UPROPERTY()
	TArray<AActor*> AvailableActorsToLock;

	UPROPERTY()
	AActor* CurrentLockedActor;


	UPROPERTY()
	UC_WarriorWidgetBase* TargetLockWidget;

	UPROPERTY()
	FVector2D TargetLockWidgetSize = FVector2D::ZeroVector;

	UPROPERTY()
	float CachedDefaultMaxWalkSpeed = 0.f;

};
