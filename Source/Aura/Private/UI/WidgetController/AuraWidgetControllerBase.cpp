// 


#include "UI/WidgetController/AuraWidgetControllerBase.h"

#include "AttributeSet.h"

void UAuraWidgetControllerBase::InitWidgetController(const FWidgetControllerParams& Params)
{
	PlayerState = Params.PlayerState;
	PlayerController = Params.PlayerController;
	AbilitySystemComponent = Params.AbilitySystemComponent;
	AttributeSet = Params.AttributeSet;
	
	BindDelegateForModel();
}

void UAuraWidgetControllerBase::BroadCastInitValue()
{
	return;
}

void UAuraWidgetControllerBase::BindDelegateForModel()
{
}

