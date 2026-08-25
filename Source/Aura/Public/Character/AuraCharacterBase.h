// 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interactive/ICombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayEffect;
class UAuraAttributeSet;
class UAuraAbilitySystemComopnent;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface,public IICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const; 
	

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	virtual void OnASCReady();
	
	void ApplyGEToSelf(const TSubclassOf<UGameplayEffect>& GEClass,float Level);

	void InitAS();
private:
	UPROPERTY(EditDefaultsOnly,Category="Course|Attribute")
	TSubclassOf<UGameplayEffect> PrimaryASInitial;
	UPROPERTY(EditDefaultsOnly,Category="Course|Attribute")
	TSubclassOf<UGameplayEffect> SecondaryASInitial;
	UPROPERTY(EditDefaultsOnly,Category="Course|Attribute")
	TSubclassOf<UGameplayEffect> VitalASInitial;
};
