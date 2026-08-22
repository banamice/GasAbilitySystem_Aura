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
	ASC->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddUObject(this,
		&UAuraOverlayController::OnModelHealthChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddUObject(this,
		&UAuraOverlayController::OnModelMaxHealthChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(AS->GetManaAttribute()).AddUObject(this,
		&UAuraOverlayController::OnModelManaChanged);
	ASC->GetGameplayAttributeValueChangeDelegate(AS->GetMaxManaAttribute()).AddUObject(this,
		&UAuraOverlayController::OnModelMaxManaChanged);
}

void UAuraOverlayController::OnModelHealthChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UAuraOverlayController::OnModelMaxHealthChanged(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UAuraOverlayController::OnModelManaChanged(const FOnAttributeChangeData& Data)
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UAuraOverlayController::OnModelMaxManaChanged(const FOnAttributeChangeData& Data)
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
