// 

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetControllerBase.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AuraOverlayController.generated.h"


class UAuraUserWdigetBase;
USTRUCT(BlueprintType)
struct FMessageDataTable : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Message")
	FGameplayTag MessageTag;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Message")
	FText Message;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Message")
	TSubclassOf<UAuraUserWdigetBase> Widget;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Message")
	TObjectPtr<UTexture2D> Icon;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageGEApplySignature, const FMessageDataTable&, MessagRow);



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
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxManaChanged;
	UPROPERTY(BlueprintAssignable)
	FOnMessageGEApplySignature OnMessageGEApply;
	/*end Delegate for widget*/
	
	/*start delegate for model*/
	virtual void BindDelegateForModel();
	

	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Message")
	TObjectPtr<UDataTable> MessageDataTable;
	/*end delegate for model*/
	
	template<class T>
	static T* GetDataRow(FGameplayTag Tag,UDataTable* Table);
};

template <class T>
T* UAuraOverlayController::GetDataRow(FGameplayTag Tag, UDataTable* Table)
{
	return Table->FindRow<T>(Tag.GetTagName(),FString());
}
