


#include "Widgets/C_WarriorWidgetBase.h"
#include "Interface/PawnUIInterface.h"
#include "Components/UI/C_HeroUIComponent.h"
#include "Components/UI/C_EnemyUIComponent.h"
void UC_WarriorWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UC_HeroUIComponent* HeroUIComponent = PawnUIInterface->GetHeroUIComponent())
		{
			BP_OnOnwingHeroUIComponentInitialized(HeroUIComponent);
		}
	}
	
}

void UC_WarriorWidgetBase::InitEnemyCreateWidget(AActor* OwningEnemyActor)
{
	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningEnemyActor))
	{
		UC_EnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent();
		
		checkf(EnemyUIComponent, TEXT("Failed to extrac an EnemyUIComponent from %s"), *OwningEnemyActor->GetActorNameOrLabel());

		BP_OnOnwingEnemyUIComponentInitialized(EnemyUIComponent);
	}
}

