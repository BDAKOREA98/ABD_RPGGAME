// Vince Petrelli All Rights Reserved


#include "Animation/C_WarriorAnimInstance.h"
#include "Creature/C_Creature.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "KismetAnimationLibrary.h"

void UC_WarriorAnimInstance::NativeInitializeAnimation()
{
	OwnerCreature=	Cast<AC_Creature>(TryGetPawnOwner());
	if (OwnerCreature)
	{
		OwnerMovement = OwnerCreature->GetCharacterMovement();

	}




}

void UC_WarriorAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwnerCreature|| !OwnerMovement)
	{
		return;
	}

	GroundSpeed = OwnerCreature->GetVelocity().Size2D();

	bHasAcceleration = OwnerMovement->GetCurrentAcceleration().SizeSquared2D() > 0.0f;

	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwnerCreature->GetVelocity(), OwnerCreature->GetActorRotation());



}
