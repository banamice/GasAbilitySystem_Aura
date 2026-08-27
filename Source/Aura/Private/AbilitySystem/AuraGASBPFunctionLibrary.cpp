// 


#include "AbilitySystem/AuraGASBPFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComopnent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Input/AuraPlayerController.h"
#include "Player/PlayerState/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetControllerBase.h"

 UAuraWidgetControllerBase* UAuraGASBPFunctionLibrary::GetOverlayWidgetController(
	const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;
	
	AAuraPlayerController* PC =  Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject,0));
	if (!PC) return nullptr;
	
	AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
	if (!PS) return nullptr;
	
	UAuraAbilitySystemComopnent* ASC = Cast<UAuraAbilitySystemComopnent>(PS->GetAbilitySystemComponent()); 
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(PS->GetAttributeSet());
	
	
	
	AAuraHUD* HUD = Cast<AAuraHUD>(PC->GetHUD());
	return HUD->GetOverlayWidgetController(FWidgetControllerParams(PC,PS,ASC,AS));
}

 UAuraWidgetControllerBase* UAuraGASBPFunctionLibrary::GetAttributeWidgetController(
	const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;
	
	AAuraPlayerController* PC =  Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject,0));
	if (!PC) return nullptr;
	
	AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
	if (!PS) return nullptr;
	
	UAuraAbilitySystemComopnent* ASC = Cast<UAuraAbilitySystemComopnent>(PS->GetAbilitySystemComponent()); 
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(PS->GetAttributeSet());
	
	
	
	AAuraHUD* HUD = Cast<AAuraHUD>(PC->GetHUD());
	return HUD->GetAttributeWidgetController(FWidgetControllerParams(PC,PS,ASC,AS));
}
