// 

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Data/AuraInputDataAsset.h"
#include "AuraEnhancedInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AURA_API UAuraEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class OwnerClass ,typename PressedFunType,typename ReleasedFunType,typename HoldFunType>
	void BindAbilityInput(const UAuraInputDataAsset* InputDataAsset,OwnerClass* Owner,PressedFunType PressedFun,ReleasedFunType ReleasedFun,HoldFunType HoldFun);

};

template <class OwnerClass, typename PressedFunType, typename ReleasedFunType, typename HoldFunType>
void UAuraEnhancedInputComponent::BindAbilityInput(const UAuraInputDataAsset* InputDataAsset,OwnerClass* Owner, PressedFunType PressedFun, ReleasedFunType ReleasedFun, HoldFunType HoldFun)
{
	if (!IsValid(InputDataAsset) || !IsValid(Owner))
	{
		return;
	}

	for (const FAuraInputData& InputData : InputDataAsset->InputDataArray)
	{
		if (IsValid(InputData.InputAction) && InputData.InputTag.IsValid())
		{
			BindAction(InputData.InputAction,ETriggerEvent::Started,Owner,PressedFun,InputData.InputTag);
			BindAction(InputData.InputAction,ETriggerEvent::Completed,Owner,ReleasedFun,InputData.InputTag);
			BindAction(InputData.InputAction,ETriggerEvent::Triggered,Owner,HoldFun,InputData.InputTag);
		}
	}
}
