// Vince Petrelli All Rights Reserved


#include "AbilitySystem/C_WarriorGameplayAbility.h"
#include "AbilitySystem/C_WarriorAbilityComponent.h"
#include "Components/Combat/C_PawnCombatComponent.h"
#include "Abilities/GameplayAbility.h"
void UC_WarriorGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	if (AbilityActivationPolicy == EWarriorAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);

		}
	}
}

void UC_WarriorGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EWarriorAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);

		}
	}

}

UC_PawnCombatComponent* UC_WarriorGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{

	return GetAvatarActorFromActorInfo()->FindComponentByClass<UC_PawnCombatComponent>();



}

UC_WarriorAbilityComponent* UC_WarriorGameplayAbility::GetWarriorAbilitySystemComponentFromActorInfo() const
{

	return Cast<UC_WarriorAbilityComponent>(CurrentActorInfo->AbilitySystemComponent);


}
