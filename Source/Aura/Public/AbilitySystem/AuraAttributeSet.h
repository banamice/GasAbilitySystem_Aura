// 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

#include "AuraAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	UAbilitySystemComponent* TargetASC;
	UPROPERTY()
	AActor* TargetAvatarActor;
	UPROPERTY()
	ACharacter* TargetAvatarCharacter;
	UPROPERTY()
	APlayerController* TargetController;
	
	UPROPERTY()
	UAbilitySystemComponent* SourceASC;
	UPROPERTY()
	AActor* SourceAvatarActor;
	UPROPERTY()
	ACharacter* SourceAvatarCharacter;
	UPROPERTY()
	APlayerController* SourceController;
	
	FGameplayEffectContextHandle EffectContext;
	
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	
	/*
	 * SecondaryAttribute
	 */
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, PhysicalDamage)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MagicDamage)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalChance)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalDamage)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance)
	/*
	 * EndSecondaryAttribute
	 */
	
	/*
	 * Vital Attribute
	 */
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)
	/*
	 * End Vital Attribute
	 */
	
	/*
	 * PrimaryAttribute
	 */
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Str)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Int)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Luck)
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Def)
	/*
	 * EndPrimaryAttribute
	 */
	
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
protected:
	
private:
	
	/*
	 * PrimaryAttribute
	 */
	UPROPERTY(ReplicatedUsing=OnRep_Str)
	FGameplayAttributeData Str;
	UPROPERTY(ReplicatedUsing=OnRep_Int)
	FGameplayAttributeData Int;
	UPROPERTY(ReplicatedUsing=OnRep_Luck)
	FGameplayAttributeData Luck;
	UPROPERTY(ReplicatedUsing=OnRep_Def)
	FGameplayAttributeData Def;
	
	UFUNCTION()
	void OnRep_Str(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_Int(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_Luck(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_Def(const FGameplayAttributeData& OldValue) const;
	
	/*
	 * EndPrimaryAttribute
	 */
	
	/*
	 * Vital Attribute
	 */
	UPROPERTY(ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	UPROPERTY(ReplicatedUsing=OnRep_Mana)
	FGameplayAttributeData Mana;

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue) const;

	/*
	 * End Vital Attribute
	 */
	
	/*
	 * SecondaryAttribute
	 */
	UPROPERTY(ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	UPROPERTY(ReplicatedUsing=OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	UPROPERTY(ReplicatedUsing=OnRep_PhysicalDamage)
	FGameplayAttributeData PhysicalDamage;
	UPROPERTY(ReplicatedUsing=OnRep_MagicDamage)
	FGameplayAttributeData MagicDamage;
	UPROPERTY(ReplicatedUsing=OnRep_CriticalChance)
	FGameplayAttributeData CriticalChance;
	UPROPERTY(ReplicatedUsing=OnRep_CriticalDamage)
	FGameplayAttributeData CriticalDamage;
	UPROPERTY(ReplicatedUsing=OnRep_HealthRegeneration)
	FGameplayAttributeData HealthRegeneration;
	UPROPERTY(ReplicatedUsing=OnRep_ManaRegeneration)
	FGameplayAttributeData ManaRegeneration;
	UPROPERTY(ReplicatedUsing=OnRep_BlockChance)
	FGameplayAttributeData BlockChance;
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_PhysicalDamage(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_MagicDamage(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_CriticalChance(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_CriticalDamage(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldValue) const;
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldValue) const;
	/*
	 * EndSecondaryAttribute
	 */
	
	void SetFEffectProperties(FEffectProperties& EffectProperties,const FGameplayEffectModCallbackData& Data);

	void ClampValue(const struct FGameplayEffectModCallbackData& Data);
};
