


#include "Creature/C_Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Combat/C_EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartUpData/C_DataAsset_StartUpDataBase.h"
#include "DataAssets/StartUpData/C_Enemy_DataAsset_StartUpData.h"
#include "Components/WidgetComponent.h"
#include "Components/UI/C_EnemyUIComponent.h"
#include "Widgets/C_WarriorWidgetBase.h"

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

	EnemyUIComponent =	CreateDefaultSubobject< UC_EnemyUIComponent>("EnemyUIComponent");

	EnemyHealthWidgetComponent = CreateDefaultSubobject< UWidgetComponent>("EnemyHealthWidgetComponent");
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());


}

UC_PawnCombatComponent* AC_Enemy::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UC_PawnUIComponent* AC_Enemy::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

UC_EnemyUIComponent* AC_Enemy::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

void AC_Enemy::BeginPlay()
{
	Super::BeginPlay();

	if (UC_WarriorWidgetBase* HealthWidget = Cast<UC_WarriorWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreateWidget(this);
	}
	

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
					
					
					
					
				}

			}
		)

	);



}
