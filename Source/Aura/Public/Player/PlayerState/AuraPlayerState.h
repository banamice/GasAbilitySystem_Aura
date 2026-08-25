// 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAuraAttributeSet;
class UAuraAbilitySystemComopnent;
class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AAuraPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override; 
	virtual UAttributeSet* GetAttributeSet() const; 
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
private:
	UPROPERTY(ReplicatedUsing=OnRep_Level,EditAnywhere,Category="Course|Attribute")
	uint32 Level = 1;
	
	UFUNCTION()
	void OnRep_Level();

	
	
	
	
	
	
	
	
public:
	uint32 GetLevel() const
	{
		return Level;
	}

	void SetLevel(const uint32 InLevel)
	{
		Level = InLevel;
		//TODO:广播委托变化
	}
};
