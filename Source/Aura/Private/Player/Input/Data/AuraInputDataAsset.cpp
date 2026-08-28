// 


#include "Player/Input/Data/AuraInputDataAsset.h"

const UInputAction* UAuraInputDataAsset::GetInputAction(const FGameplayTag& InputTag)
{
	for (auto& InputData : InputDataArray)
	{
		if (InputData.InputAction && InputData.InputTag == InputTag)
		{
			return InputData.InputAction;
		}
	}
	return nullptr;
}
