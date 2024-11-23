


#include "Creature/C_Warrior.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/Warrior_InputComponent.h"
#include "WArriorGameplayTags.h"
#include "AbilitySystem/C_WarriorAbilityComponent.h"
#include "DataAssets/StartUpData/C_Hero_DataAsset_StartUpDataBase.h"
#include "Components/Combat/C_HeroCombatComponent.h"
#include "Components/UI/C_HeroUIComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameModes/C_RPGGameMode.h"
#include "WarriorDebugHelper.h"
AC_Warrior::AC_Warrior()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 55.0f, 65.0f);
	CameraBoom->bUsePawnControlRotation = true;


	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	


	


	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;


	HeroCombatComponent = CreateDefaultSubobject<UC_HeroCombatComponent>(TEXT("HeroCombatComponent"));
	HeroUIComponent = CreateDefaultSubobject<UC_HeroUIComponent>(TEXT("HeroUIComponent"));

}

UC_PawnCombatComponent* AC_Warrior::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

UC_PawnUIComponent* AC_Warrior::GetPawnUIComponent() const
{
	return HeroUIComponent;
}

UC_HeroUIComponent* AC_Warrior::GetHeroUIComponent() const
{
	return HeroUIComponent;
}

void AC_Warrior::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!CharacterStartUpData.IsNull())
	{
		if (UC_DataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			int32 AbilityApplyLevel = 1;
			if (AC_RPGGameMode* BaseGameMode = GetWorld()->GetAuthGameMode<AC_RPGGameMode>())
			{
				switch (BaseGameMode->GetCurrentGameDifficulty())
				{
				case EGameDifficulty::Easy:
					AbilityApplyLevel = 4;
					Debug::Print(TEXT("Current Difficulty : Easy"));
					break;
				case EGameDifficulty::Normal:
					AbilityApplyLevel = 3;
					Debug::Print(TEXT("Current Difficulty : Normal"));
					break;
				case EGameDifficulty::Hard:
					AbilityApplyLevel = 2;
					Debug::Print(TEXT("Current Difficulty : Hard"));
					break;
				case EGameDifficulty::Hell:
					AbilityApplyLevel = 1;
					Debug::Print(TEXT("Current Difficulty : Hell"));
					break;

				default:
					break;
				}
			}

			LoadedData->GiveToAbilitySystemComponent(WarriorAbilityComponent, AbilityApplyLevel);
		}
	}
}

void AC_Warrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to Assign a valid data asset as input config"));


	ULocalPlayer* LocalPlayer =  GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* SubSystem =	ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(SubSystem);

	SubSystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UWarrior_InputComponent* WarriorInputComponent = CastChecked<UWarrior_InputComponent>(PlayerInputComponent);

	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset,WarriorGamePlayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset,WarriorGamePlayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	
	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGamePlayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &ThisClass::Input_SwitchTargetTriggerd);
	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGamePlayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &ThisClass::Input_SwitchTargetCompleted);

	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGamePlayTags::InputTag_PickUp_Stones, ETriggerEvent::Started, this, &ThisClass::Input_PickUpStonesStarted);

	WarriorInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleassed);



}

void AC_Warrior::BeginPlay()
{
	Super::BeginPlay();

	

}

void AC_Warrior::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

	if (MovementVector.Y != 0.0f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);

	}
	if (MovementVector.X != 0.0f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}



}

void AC_Warrior::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (LookAxisVector.X != 0.0f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.0f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}

}

void AC_Warrior::Input_SwitchTargetTriggerd(const FInputActionValue& InputActionValue)
{
	SwitchDirection = InputActionValue.Get<FVector2D>();
}

void AC_Warrior::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		SwitchDirection.X > 0.f ? WarriorGamePlayTags::Player_Event_SwitchTarget_Right : WarriorGamePlayTags::Player_Event_SwitchTarget_Left,
		Data

	);

	
}

void AC_Warrior::Input_PickUpStonesStarted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		WarriorGamePlayTags::Player_Event_ConsumeStones,
		Data
	);

}

void AC_Warrior::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	WarriorAbilityComponent->OnAbilityInputPressed(InInputTag);
}

void AC_Warrior::Input_AbilityInputReleassed(FGameplayTag InInputTag)
{
	WarriorAbilityComponent->OnAbilityInputReleassed(InInputTag);
}
