

#pragma once

#include "CoreMinimal.h"
#include "Creature/C_Creature.h"
#include "C_Enemy.generated.h"


class UC_EnemyCombatComponent;
class UC_EnemyUIComponent;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API AC_Enemy : public AC_Creature
{
	GENERATED_BODY()
public:
	AC_Enemy();

	//Begin IPawnCombatInterface Interface
	virtual UC_PawnCombatComponent* GetPawnCombatComponent() const override;
	//End IPawnCombatInterface Interface

	//Begin IPawnUIComponent Interface
	virtual UC_PawnUIComponent* GetPawnUIComponent()  const override;
	virtual UC_EnemyUIComponent* GetEnemyUIComponent() const override;
	//End IPawnUIComponent Interface

protected:
	virtual void BeginPlay() override;

	//begin APwan interfece
	virtual void PossessedBy(AController* NewController) override;
	//end APwan interfece

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UC_EnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UC_EnemyUIComponent* EnemyUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* EnemyHealthWidgetComponent;

private:
	void InitEnemyStartUpData();

public:

	FORCEINLINE UC_EnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }

};
