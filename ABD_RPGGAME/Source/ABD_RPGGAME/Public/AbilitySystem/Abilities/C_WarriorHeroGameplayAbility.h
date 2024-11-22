

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/C_WarriorGameplayAbility.h"
#include "C_WarriorHeroGameplayAbility.generated.h"

class AC_Warrior;
class AC_WarriorController;
/**
 * 
 */
UCLASS()
class ABD_RPGGAME_API UC_WarriorHeroGameplayAbility : public UC_WarriorGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	AC_Warrior* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	AC_WarriorController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	UC_HeroCombatComponent* GetHeroCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	UC_HeroUIComponent* GetHeroUIComponentActorInfo();


	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InUsedAttackTypeTag, int32 InCurrentComboCount);

	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability")
	bool GetAbilityRemaningCooldownByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemaningCooldownTime);

private:

	TWeakObjectPtr<AC_Warrior> CachedWarriorHeroCharacter;
	TWeakObjectPtr<AC_WarriorController> CachedWarriorHeroController;


};
