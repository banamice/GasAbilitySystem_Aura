// 


#include "UI/WidgetController/AuraOverlayController.h"

#include "AbilitySystem/AuraAbilitySystemComopnent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UAuraOverlayController::BroadCastInitValue()
{
	if (UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet))
	{
		OnMaxHealthChanged.Broadcast(AS->GetMaxHealth());
		OnHealthChanged.Broadcast(AS->GetHealth());
		OnManaChanged.Broadcast(AS->GetMana());
		OnMaxManaChanged.Broadcast(AS->GetMaxMana());
	}
}

void UAuraOverlayController::BindDelegateForModel()
{
	UAuraAbilitySystemComopnent* ASC = Cast<UAuraAbilitySystemComopnent>(AbilitySystemComponent);
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);
	if (!ASC || !AS) return;
	ASC->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnHealthChanged.Broadcast(Data.NewValue);
	}	
	);
	ASC->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	}	
	);
	ASC->GetGameplayAttributeValueChangeDelegate(AS->GetManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnManaChanged.Broadcast(Data.NewValue);
	}	
	);
	ASC->GetGameplayAttributeValueChangeDelegate(AS->GetMaxManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnMaxManaChanged.Broadcast(Data.NewValue);
	}	
	);
	
	
	ASC->OnGEApplySignature.AddLambda(
	[this ](const FGameplayTagContainer& AssetTags)
	{
		FGameplayTag Message =  FGameplayTag::RequestGameplayTag(FName("Message"));
		for (const auto& Tag : AssetTags)
		{
			if (Tag.MatchesTag(Message))
			{
				check(MessageDataTable);
				FMessageDataTable* MessageRow =  GetDataRow<FMessageDataTable>(Tag,MessageDataTable);
				if (MessageRow)
				{
					//广播
					OnMessageGEApply.Broadcast(*MessageRow);
				}
			}
		}
	} 
	);
}



