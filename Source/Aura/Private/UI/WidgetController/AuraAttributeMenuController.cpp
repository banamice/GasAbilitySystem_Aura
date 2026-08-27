// 


#include "UI/WidgetController/AuraAttributeMenuController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/DataAsset/AuraAttributeDataAsset.h"

void UAuraAttributeMenuController::BroadCastInitValue()
{
	checkf(AttributeSet,TEXT("Attribute Set is null"))
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);
	for (auto& Pair: AS->TagValueMap)
	{
		FAuraAttributeData Data =  AttributeDataAsset->GetAttributeData(Pair.Key);
		Data.DefaultValue = Pair.Value.GetNumericValue(AS);
		OnAttributeMenuValueChange.Broadcast(Data);
	}
}

void UAuraAttributeMenuController::BindDelegateForModel()
{
	checkf(AttributeSet,TEXT("Attribute Set is null"))
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);
	
	for (auto& Pair: AS->TagValueMap)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value).AddLambda(
			[this,Pair](const FOnAttributeChangeData& ChangedData)
			{
				FAuraAttributeData Data =  AttributeDataAsset->GetAttributeData(Pair.Key);
				Data.DefaultValue = ChangedData.NewValue;
				OnAttributeMenuValueChange.Broadcast(Data);
			}
		);
	}
}
