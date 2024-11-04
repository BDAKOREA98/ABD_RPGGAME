


#include "WarriorTypes/C_WarriorStrucTypes.h"
#include "AbilitySystem/Abilities/C_WarriorHeroGameplayAbility.h"
bool FWarriorHeroAbilitySet::IsValid() const
{
    return InputTag.IsValid() && AbilityToGrant;
}