


#include "Creature/C_Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Combat/C_EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartUpData/C_DataAsset_StartUpDataBase.h"
#include "DataAssets/StartUpData/C_Enemy_DataAsset_StartUpData.h"

#include "WarriorDebugHelper.h"
AC_Enemy::AC_Enemy()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.0f;


	EnemyCombatComponent =	CreateDefaultSubobject< UC_EnemyCombatComponent>("EnemyCombatComponent");



}

UC_PawnCombatComponent* AC_Enemy::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

void AC_Enemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData();

}

void AC_Enemy::InitEnemyStartUpData()
{
	if (CharacterStartUpData.IsNull())
	{
		return;
	}

	UAssetManager::GetStreamableManager().RequestAsyncLoad
	(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda
		(
			[this]()
			{
				if (UC_DataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get())
				{
				

					LoadedData->GiveToAbilitySystemComponent(WarriorAbilityComponent);
					
					Debug::Print(TEXT("Enemy Start Up DAta Loaded "),  FColor::Red);
					
					
				}

			}
		)

	);



}
