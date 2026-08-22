// 


#include "UI/Widget/AuraUserWdigetBase.h"

void UAuraUserWdigetBase::SetWidgetController(UObject* NewWidgetController)
{
	AuraWidgetController = NewWidgetController;
	OnWidgetControllerSet();
}
