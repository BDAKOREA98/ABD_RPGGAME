


#include "Interface/PawnUIInterface.h"

// Add default functionality here for any IPawnUIInterface functions that are not pure virtual.

UC_HeroUIComponent* IPawnUIInterface::GetHeroUIComponent() const
{
    return nullptr;
}

UC_EnemyUIComponent* IPawnUIInterface::GetEnemyUIComponent() const
{
    return nullptr;
}
