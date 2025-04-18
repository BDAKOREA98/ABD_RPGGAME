


#include "Weapons/WarriorWeaponBase.h"
#include "Components/BoxComponent.h"
#include "Creature/C_Enemy.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorDebugHelper.h"

// Sets default values
AWarriorWeaponBase::AWarriorWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(GetRootComponent());
	CollisionBox->SetBoxExtent(FVector(20.f));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlab);
	CollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlab);




}

void AWarriorWeaponBase::OnCollisionBoxBeginOverlab(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	APawn* WeaponOwningPawn =	GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forgot to Assign an Instigator as the Owning pawn for the Weapon %s "), *GetName());
	
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UWarriorFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			OnWeaponHitTarget.ExecuteIfBound(OtherActor); 
		}

	}


}

void AWarriorWeaponBase::OnCollisionBoxEndOverlab(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forgot to Assign an Instigator as the Owning pawn for the Weapon %s "), *GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UWarriorFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, HitPawn))
		{
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
		}

	}
}
