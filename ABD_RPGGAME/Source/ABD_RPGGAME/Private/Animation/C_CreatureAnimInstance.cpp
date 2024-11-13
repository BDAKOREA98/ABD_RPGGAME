// Vince Petrelli All Rights Reserved


#include "Animation/C_CreatureAnimInstance.h"
#include "WarriorFunctionLibrary.h"
UC_CreatureAnimInstance::UC_CreatureAnimInstance()
{
}

bool UC_CreatureAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UWarriorFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}
	return false;
}
