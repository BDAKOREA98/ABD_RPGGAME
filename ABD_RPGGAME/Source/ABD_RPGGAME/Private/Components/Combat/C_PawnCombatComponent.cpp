


#include "Components/Combat/C_PawnCombatComponent.h"
#include "Weapons/WarriorWeaponBase.h"
#include "Creature/C_Creature.h"


#include "WarriorDebugHelper.h"

void UC_PawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CraetureCarriedWeaponMap.Contains(InWeaponTagToRegister),TEXT("A named named %s has already been added as carried weapon"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);


	CraetureCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}


	const FString WeaponString = FString::Printf(TEXT("A Weapon named : %s  has been registered using the tag %s"), *InWeaponToRegister->GetName(), *InWeaponTagToRegister.ToString());
	Debug::Print(WeaponString);


}

AWarriorWeaponBase* UC_PawnCombatComponent::GetCreatureCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (CraetureCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (AWarriorWeaponBase* const* FoundWeapon = CraetureCarriedWeaponMap.Find(InWeaponTagToGet))
		{

			return *FoundWeapon;
		}
	}


	return nullptr;
}

AWarriorWeaponBase* UC_PawnCombatComponent::GetCreatureCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}



	return GetCreatureCarriedWeaponByTag(CurrentEquippedWeaponTag);
}