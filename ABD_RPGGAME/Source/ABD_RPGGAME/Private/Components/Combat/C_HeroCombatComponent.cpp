


#include "Components/Combat/C_HeroCombatComponent.h"
#include "Weapons/WarriorHeroWeapon.h"
AWarriorHeroWeapon* UC_HeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{

    return Cast<AWarriorHeroWeapon> (GetCreatureCarriedWeaponByTag(InWeaponTag));
    
}
