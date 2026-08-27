// 

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetControllerBase.h"
#include "AuraAttributeMenuController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeMenuValueChangeSignature,const FAuraAttributeData ,AuraAttributeData);


class UAuraAttributeDataAsset;
/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class AURA_API UAuraAttributeMenuController : public UAuraWidgetControllerBase
{
	GENERATED_BODY()
	
public:
	virtual void BroadCastInitValue() override;
	virtual void BindDelegateForModel() override;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeMenuValueChangeSignature OnAttributeMenuValueChange;
	
private:
	UPROPERTY(EditDefaultsOnly,Category="Attribute")
	TObjectPtr<UAuraAttributeDataAsset> AttributeDataAsset;
};
