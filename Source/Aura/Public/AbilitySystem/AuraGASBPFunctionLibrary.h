// 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraGASBPFunctionLibrary.generated.h"

class UAuraWidgetControllerBase;
/**
 * 
 */
UCLASS()
class AURA_API UAuraGASBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable,BlueprintPure,Category = "WidgetController")
	static UAuraWidgetControllerBase* GetOverlayWidgetController(const UObject* WorldContextObject);
	UFUNCTION(BlueprintCallable,BlueprintPure,Category = "WidgetController")
	static UAuraWidgetControllerBase* GetAttributeWidgetController(const UObject* WorldContextObject);
	
};

