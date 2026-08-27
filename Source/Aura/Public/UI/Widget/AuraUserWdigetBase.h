// 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWdigetBase.generated.h"

class UAuraWidgetControllerBase;
/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class AURA_API UAuraUserWdigetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* NewWidgetController);
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> AuraWidgetController;
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();
	
};
