


#include "DataAssets/StartUpData/C_Hero_DataAsset_StartUpDataBase.h"
#include "WarriorTypes/C_WarriorStrucTypes.h"
#include "AbilitySystem/C_WarriorAbilityComponent.h"
#include "AbilitySystem/Abilities/C_WarriorHeroGameplayAbility.h"



void UC_Hero_DataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UC_WarriorAbilityComponent* InASCToGive, int32 ApplyLevel)
{
    Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);



	for (const FWarriorHeroAbilitySet& AbilitySet : HeroStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);


		InASCToGive->GiveAbility(AbilitySpec);


	}

}
