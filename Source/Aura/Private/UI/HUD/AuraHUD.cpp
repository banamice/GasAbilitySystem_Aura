// 


#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWdigetBase.h"
#include "UI/WidgetController/AuraWidgetControllerBase.h"




void AAuraHUD::InitializeOverlayWidget( APlayerState* PS,  APlayerController* PC,
                                        UAbilitySystemComponent* ASC,  UAttributeSet* AS)
{
	checkf(OverlayWidgetControllerClass,TEXT("OverlayWidgetControllerClass is not set"))
	checkf(PlayerOverlayClass,TEXT("PlayerOverlayClass is not set"))
	
	
	OverlayWidgetController = GetOverlayWidgetController(FWidgetControllerParams(PC,PS,ASC,AS));
	
	PlayerOverlay = CreateWidget<UAuraUserWdigetBase>(GetWorld(), PlayerOverlayClass);
	PlayerOverlay->SetWidgetController(OverlayWidgetController);
	OverlayWidgetController->BroadCastInitValue();
	
	PlayerOverlay->AddToViewport();
	
}

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
	
	
}

UAuraWidgetControllerBase* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& Params)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UAuraWidgetControllerBase>(this,OverlayWidgetControllerClass);
		OverlayWidgetController->InitWidgetController(Params);
		return OverlayWidgetController;
	}else
	{
		return OverlayWidgetController;
	}
}
