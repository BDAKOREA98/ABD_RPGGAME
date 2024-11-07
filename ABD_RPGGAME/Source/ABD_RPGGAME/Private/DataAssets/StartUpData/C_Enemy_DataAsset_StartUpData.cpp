


#include "DataAssets/StartUpData/C_Enemy_DataAsset_StartUpData.h"
#include "AbilitySystem/Abilities/C_EnemyGameplayAbility.h"
#include "AbilitySystem/C_WarriorAbilityComponent.h"

void UC_Enemy_DataAsset_StartUpData::GiveToAbilitySystemComponent(UC_WarriorAbilityComponent* InASCToGive, int32 ApplyLevel)
{
	
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
	if (!EnemyCombatAbilities.IsEmpty())
	{
		for (const TSubclassOf < UC_EnemyGameplayAbility >& AbilityClass : EnemyCombatAbilities)
		{

			if (!AbilityClass)
			{
				continue;
			}
			FGameplayAbilitySpec AbilitySpec(AbilityClass);

			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;

			InASCToGive->GiveAbility(AbilitySpec);



			
			float a = 1;

		}
	}
	
	


}
