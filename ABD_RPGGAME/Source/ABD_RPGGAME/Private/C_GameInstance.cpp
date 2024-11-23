


#include "C_GameInstance.h"

TSoftObjectPtr<UWorld> UC_GameInstance::GetGameLevelByTag(FGameplayTag InTag) const
{
	for (const FGameLevelSet& GameLevelSet : GameLevelSets)
	{
		if (!GameLevelSet.IsValid())
		{
			continue;
		}
		if (GameLevelSet.LevelTag == InTag)
		{
			return GameLevelSet.Level;
		}
	}

	return TSoftObjectPtr<UWorld>();
}
