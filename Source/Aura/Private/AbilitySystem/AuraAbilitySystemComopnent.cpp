// Claude has demonstrated text editing capabilities in this file


#include "AbilitySystem/AuraAbilitySystemComopnent.h"

#include "AbilitySystem/Ability/AuraGameplayAbilityBase.h"


void UAuraAbilitySystemComopnent::InitAsc()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComopnent::Client_OnGEApply);
}

void UAuraAbilitySystemComopnent::GiveCharacterAbility(const TArray<TSubclassOf<UGameplayAbility>>& GameplayAbilityClass)
{
	for (auto& GA : GameplayAbilityClass)
	{
		FGameplayAbilitySpec GASpec = FGameplayAbilitySpec(GA);
		UAuraGameplayAbilityBase* Ability = Cast<UAuraGameplayAbilityBase>(GASpec.Ability);
		if (Ability)
		{
			GASpec.GetDynamicSpecSourceTags().AddTag(Ability->InputTag);
		}
		GiveAbility(GASpec);
	}
}

void UAuraAbilitySystemComopnent::OnAbilityInputHold(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	for (auto& Ability : GetActivatableAbilities())
	{
		if (Ability.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(Ability);
			if (!Ability.IsActive())
			{
				TryActivateAbility(Ability.Handle);
			}
		}
	}
}

void UAuraAbilitySystemComopnent::OnAbilityInputRelease(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	for (auto& Ability : GetActivatableAbilities())
	{
		if (Ability.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(Ability);
		}
	}
}



void UAuraAbilitySystemComopnent::Client_OnGEApply_Implementation(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GESpec,
                                                    FActiveGameplayEffectHandle AGEHandle)
{
	FGameplayTagContainer OutContainer;
	GESpec.GetAllAssetTags(OutContainer);
	
	OnGEApplySignature.Broadcast(OutContainer);
}
