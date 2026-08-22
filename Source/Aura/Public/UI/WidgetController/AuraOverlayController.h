// 

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetControllerBase.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AuraOverlayController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);


/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class AURA_API UAuraOverlayController : public UAuraWidgetControllerBase
{
	GENERATED_BODY()
	
public:
	/* start Delegate for widget*/
	virtual void BroadCastInitValue();
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FOnManaChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable)
	FOnMaxManaChangedSignature OnMaxManaChanged;
	/*end Delegate for widget*/
	
	/*start delegate for model*/
	virtual void BindDelegateForModel();
	
	void OnModelHealthChanged(const FOnAttributeChangeData& Data);
	void OnModelMaxHealthChanged(const FOnAttributeChangeData& Data);
	void OnModelManaChanged(const FOnAttributeChangeData& Data);
	void OnModelMaxManaChanged(const FOnAttributeChangeData& Data);
	/*end delegate for model*/
};
