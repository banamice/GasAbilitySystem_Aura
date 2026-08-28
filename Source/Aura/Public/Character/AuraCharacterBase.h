// 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interactive/ICombatInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayAbility;
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
	virtual FVector GetProjectileSpawnLocation() const override;
	

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> WeaponMesh = nullptr;
	UPROPERTY(EditDefaultsOnly,Category="Course|Projectile")
	FName ProjectileSocketName = "TipSocket";
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
	virtual void OnASCReady();
	
	void ApplyGEToSelf(const TSubclassOf<UGameplayEffect>& GEClass,float Level);

	void InitAS();
	
	void GiveCharacterAbility();
private:
	UPROPERTY(EditDefaultsOnly,Category="Course|Attribute")
	TSubclassOf<UGameplayEffect> PrimaryASInitial;
	UPROPERTY(EditDefaultsOnly,Category="Course|Attribute")
	TSubclassOf<UGameplayEffect> SecondaryASInitial;
	UPROPERTY(EditDefaultsOnly,Category="Course|Attribute")
	TSubclassOf<UGameplayEffect> VitalASInitial;
	
	UPROPERTY(EditDefaultsOnly,Category="Course|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> SetUpAbility;
};
 
