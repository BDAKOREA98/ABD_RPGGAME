

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "C_PawnExtensionComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABD_RPGGAME_API UC_PawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()
protected:

	template<class T> 
	T* GetOwningPawn() const
	{
		static_assert(TPointerIsConvertibleFromTo <T, APawn>::Value, "'T' Template Parameter get GetPawn must be derived from APawn");

		return CastChecked<T>(GetOwner());

	}


	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	template <class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo <T, AController>::Value, "'T' Template Parameter get GetController must be derived from AController");
		return GetOwningPawn<APawn>()->GetController<T>();
	}




};
