


#include "Components/Combat/C_PawnCombatComponent.h"
#include "Weapons/WarriorWeaponBase.h"
#include "Creature/C_Creature.h"
#include "Components/BoxComponent.h"

#include "WarriorDebugHelper.h"

void UC_PawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CraetureCarriedWeaponMap.Contains(InWeaponTagToRegister),TEXT("A named named %s has already been added as carried weapon"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister);


	CraetureCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);


	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);

	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}


	


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

void UC_PawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{

	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		AWarriorWeaponBase* WeaponToToggle =	GetCreatureCurrentEquippedWeapon();

		check(WeaponToToggle);
		if (bShouldEnable)
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			
			
		}
		else
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			OverlappedActors.Empty();


		}

		
	}

	//TODO : Handle Body Collision Box



}

void UC_PawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{

	
}

void UC_PawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}
