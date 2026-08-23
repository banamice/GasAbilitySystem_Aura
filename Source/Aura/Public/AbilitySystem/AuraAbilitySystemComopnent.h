// 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"

#include "AuraAbilitySystemComopnent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGEApplySignature, const FGameplayTagContainer&/*Asset Tags*/);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AURA_API UAuraAbilitySystemComopnent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void InitAsc();
	FOnGEApplySignature OnGEApplySignature;
	
private:
	
	void OnGEApply( UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle AGEHandle);

};
