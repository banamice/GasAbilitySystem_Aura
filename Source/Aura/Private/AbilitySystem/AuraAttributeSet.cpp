// 


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(0.f);
	InitMaxHealth(100.f);
	InitMana(0.f);
	InitMaxMana(100.f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FEffectProperties EffectProperties;
	SetFEffectProperties(EffectProperties,Data);
	
	ClampValue(Data);
}

void UAuraAttributeSet::ClampValue(const struct FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}



void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldValue);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldValue);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldValue);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldValue);
}

void UAuraAttributeSet::SetFEffectProperties(FEffectProperties& EffectProperties, const FGameplayEffectModCallbackData& Data)
{
	EffectProperties.TargetASC = &Data.Target;
	if (IsValid(EffectProperties.TargetASC) && EffectProperties.TargetASC->AbilityActorInfo.IsValid() && EffectProperties.TargetASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.TargetAvatarActor = Data.Target.GetAvatarActor();
	}
	if (IsValid(EffectProperties.TargetAvatarActor))
	{
		EffectProperties.TargetAvatarCharacter = Cast<ACharacter>(EffectProperties.TargetAvatarActor);
	}
	if (IsValid(EffectProperties.TargetAvatarCharacter))
	{
		EffectProperties.TargetController = Cast<APlayerController>(EffectProperties.TargetAvatarCharacter->GetController());
	}
	
	EffectProperties.EffectContext = Data.EffectSpec.GetContext();
	
	EffectProperties.SourceASC = EffectProperties.EffectContext.GetOriginalInstigatorAbilitySystemComponent();
	if (EffectProperties.SourceASC && EffectProperties.SourceASC->AbilityActorInfo.IsValid() && EffectProperties.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.SourceAvatarActor = EffectProperties.SourceASC->AbilityActorInfo->AvatarActor.Get();
	}
	if (IsValid(EffectProperties.SourceAvatarActor))
	{
		EffectProperties.SourceAvatarCharacter = Cast<ACharacter>(EffectProperties.SourceAvatarActor);
	}
	if (IsValid(EffectProperties.SourceAvatarCharacter))
	{
		EffectProperties.SourceController = Cast<APlayerController>(EffectProperties.SourceAvatarCharacter->GetController());
	}
	
}


