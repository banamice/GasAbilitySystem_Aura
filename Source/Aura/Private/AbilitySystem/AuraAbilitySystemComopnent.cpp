// Claude has demonstrated text editing capabilities in this file


#include "AbilitySystem/AuraAbilitySystemComopnent.h"


void UAuraAbilitySystemComopnent::InitAsc()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComopnent::OnGEApply);
}

void UAuraAbilitySystemComopnent::OnGEApply(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GESpec,
	FActiveGameplayEffectHandle AGEHandle)
{
	FGameplayTagContainer OutContainer;
	GESpec.GetAllAssetTags(OutContainer);
	
	OnGEApplySignature.Broadcast(OutContainer);
}
