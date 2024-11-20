

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/C_PawnUIComponent.h"
#include "C_EnemyUIComponent.generated.h"

class UC_WarriorWidgetBase;
/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UC_EnemyUIComponent : public UC_PawnUIComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawWidget(UC_WarriorWidgetBase* InWidgetToRegister);

	UFUNCTION(BlueprintCallable)
	void RemoveEnemyDrawnWidgetsIfAny();


private:
	TArray< UC_WarriorWidgetBase*> EnemyDrawWidgets;



};
