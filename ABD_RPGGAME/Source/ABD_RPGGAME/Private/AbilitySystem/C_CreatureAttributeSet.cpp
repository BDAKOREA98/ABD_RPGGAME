


#include "AbilitySystem/C_CreatureAttributeSet.h"
#include "GameplayEffectExtension.h"

#include "WarriorDebugHelper.h"
UC_CreatureAttributeSet::UC_CreatureAttributeSet()
{
	InitCurrentHealth(1.0f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefencePower(1.f);

}

void UC_CreatureAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.0f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);
	}
	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.0f, GetMaxRage());
	}
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.0f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);


		const FString DebugString = FString::Printf(TEXT("Old Health %f, Damage Done %f, NewCurrentHealth %f"),
			OldHealth,
			DamageDone,
			NewCurrentHealth

		);

		Debug::Print(DebugString, FColor::Green);

		//TODO :: Notify the UI

		//TODO:: Handle Character death

		if (NewCurrentHealth == 0.0f)
		{
			
		}
	}

}
