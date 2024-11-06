


#include "Components/Combat/C_HeroCombatComponent.h"
#include "Weapons/WarriorHeroWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "WArriorGameplayTags.h"
#include "WarriorDebugHelper.h"

AWarriorHeroWeapon* UC_HeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{

    return Cast<AWarriorHeroWeapon> (GetCreatureCarriedWeaponByTag(InWeaponTag));
    
}

void UC_HeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    if (OverlappedActors.Contains(HitActor))
    {
        return;
    }

    OverlappedActors.AddUnique(HitActor);

    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = HitActor;




    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
        GetOwningPawn(),
        WarriorGamePlayTags::Shared_Event_MeleeHit,
        Data

    );

}

void UC_HeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
    Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT("'s Weapon Pulled from ") + InteractedActor->GetActorNameOrLabel(), FColor::Red);
}
