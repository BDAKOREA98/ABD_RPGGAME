// Vince Petrelli All Rights Reserved


#include "AbilitySystem/C_WarriorAbilityComponent.h"

void UC_WarriorAbilityComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag))
		{
			continue;
		}
		TryActivateAbility(AbilitySpec.Handle);

	}
}

void UC_WarriorAbilityComponent::OnAbilityInputReleassed(const FGameplayTag& InInputTag)
{
}
