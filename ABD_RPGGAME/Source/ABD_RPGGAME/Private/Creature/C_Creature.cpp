// Vince Petrelli All Rights Reserved


#include "Creature/C_Creature.h"
#include "AbilitySystem/C_WarriorAbilityComponent.h"
#include "AbilitySystem/C_WarriorAttributeSet.h"
// Sets default values
AC_Creature::AC_Creature()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;



	WarriorAbilityComponent = CreateDefaultSubobject<UC_WarriorAbilityComponent>(TEXT("WarriorAbilitySystemComponent"));

	WarriorAttributeSet = CreateDefaultSubobject<UC_WarriorAttributeSet>(TEXT("WarriorAttributeSet"));

}

UAbilitySystemComponent* AC_Creature::GetAbilitySystemComponent() const 
{
	return GetWarriorAbilitySystemComponent();
}

void AC_Creature::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (WarriorAbilityComponent)
	{
		WarriorAbilityComponent->InitAbilityActorInfo(this, this);
		

		
		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
		

	}



}


