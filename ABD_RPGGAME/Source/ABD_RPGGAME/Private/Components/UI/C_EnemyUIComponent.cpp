


#include "Components/UI/C_EnemyUIComponent.h"
#include "Widgets/C_WarriorWidgetBase.h"
void UC_EnemyUIComponent::RegisterEnemyDrawWidget(UC_WarriorWidgetBase* InWidgetToRegister)
{
	EnemyDrawWidgets.Add(InWidgetToRegister);
}

void UC_EnemyUIComponent::RemoveEnemyDrawnWidgetsIfAny()
{
	if (EnemyDrawWidgets.IsEmpty())
	{
		return;
	}
	for (UC_WarriorWidgetBase* DrawnWidget : EnemyDrawWidgets)
	{
		if (DrawnWidget)
		{
			DrawnWidget->RemoveFromParent();
		}
	}

	EnemyDrawWidgets.Empty();

}
