

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_WarriorWidgetBase.generated.h"

class UC_HeroUIComponent;
/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UC_WarriorWidgetBase : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnOnwingHeroUIComponentInitialized"))
	
	void BP_OnOnwingHeroUIComponentInitialized(UC_HeroUIComponent * OwningHeroUIComponent);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnOnwingEnemyUIComponentInitialized"))

	void BP_OnOnwingEnemyUIComponentInitialized(UC_EnemyUIComponent* OwningEnemyUIComponent);

public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreateWidget(AActor* OwningEnemyActor);
	


};
