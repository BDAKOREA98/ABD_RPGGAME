// Vince Petrelli All Rights Reserved


#include "Animation/Hero/C_WarriorHeroAnimInstance.h"
#include "Creature/C_Warrior.h"
void UC_WarriorHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwnerCreature)
	{
		OwnerCharacter = Cast<AC_Warrior>(OwnerCreature);
	}

}

void UC_WarriorHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);


	if (bHasAcceleration)
	{
		IdleElpasedTime = 0.0f;
		bShouldEnterRelaxState = false;

	}
	else
	{
		IdleElpasedTime += DeltaSeconds;

		bShouldEnterRelaxState = (IdleElpasedTime >= EnterRelaxStateThreshold);


	}

	
}
