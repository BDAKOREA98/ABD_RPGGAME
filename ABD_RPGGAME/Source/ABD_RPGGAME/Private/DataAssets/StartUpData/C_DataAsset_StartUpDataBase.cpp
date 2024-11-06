


#include "DataAssets/StartUpData/C_DataAsset_StartUpDataBase.h"
#include "AbilitySystem/C_WarriorAbilityComponent.h"
#include "AbilitySystem/C_WarriorGameplayAbility.h"
void UC_DataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UC_WarriorAbilityComponent* InASCToGive, int32 ApplyLevel)
{

	check(InASCToGive);
	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactivateAbilities, InASCToGive, ApplyLevel);

	if (!StartUpGameplayEffect.IsEmpty())
	{
		for (const TSubclassOf< UGameplayEffect>& EffectClass : StartUpGameplayEffect)
		{
			if (!EffectClass)
			{
				continue;
			}
			UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();

			InASCToGive->ApplyGameplayEffectToSelf(

				EffectCDO,
				ApplyLevel,
				InASCToGive->MakeEffectContext()

			);
		}
	}


}

void UC_DataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UC_WarriorGameplayAbility>>& InAbilitiesToGive, UC_WarriorAbilityComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UC_WarriorGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability)
		{
			continue;
		}

		FGameplayAbilitySpec AbilitySpec(Ability);

		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;



		InASCToGive->GiveAbility(AbilitySpec);

	}
}
