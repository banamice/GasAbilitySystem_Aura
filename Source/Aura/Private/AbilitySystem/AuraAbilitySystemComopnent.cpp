// 


#include "AbilitySystem/AuraAbilitySystemComopnent.h"


void UAuraAbilitySystemComopnent::InitAsc()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComopnent::OnGEApply);
}

void UAuraAbilitySystemComopnent::OnGEApply(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GESpec,
	FActiveGameplayEffectHandle AGEHandle)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("OnGEApply")));
	FGameplayTagContainer OutContainer;
	GESpec.GetAllAssetTags(OutContainer);
	
	OnGEApplySignature.Broadcast(OutContainer);
}
