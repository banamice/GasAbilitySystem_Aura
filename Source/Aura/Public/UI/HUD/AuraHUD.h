// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/AuraAttributeMenuController.h"
#include "AuraHUD.generated.h"

class UAttributeSet;
struct FWidgetControllerParams;
class UAbilitySystemComponent;
class UAuraAttributeSet;
class UAuraWidgetControllerBase;
class UAuraUserWdigetBase;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:
	void InitializeOverlayWidget( APlayerState* PS,  APlayerController* PC,
		 UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
	UFUNCTION(BlueprintCallable)
	UAuraWidgetControllerBase* GetOverlayWidgetController(const FWidgetControllerParams& Params);
	UFUNCTION(BlueprintCallable)
	UAuraWidgetControllerBase* GetAttributeWidgetController(const FWidgetControllerParams& Params);
	
	
protected:
	virtual  void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<UAuraUserWdigetBase> PlayerOverlay;
	
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<UAuraWidgetControllerBase> OverlayWidgetController;
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<UAuraAttributeMenuController> AttributeWidgetController;
	
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI",meta=(AllowPrivateAccess="true"))
	TSubclassOf<UAuraWidgetControllerBase> OverlayWidgetControllerClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI",meta=(AllowPrivateAccess="true"))
	TSubclassOf<UAuraUserWdigetBase> PlayerOverlayClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI",meta=(AllowPrivateAccess="true"))
	TSubclassOf<UAuraWidgetControllerBase> AttributeWidgetControllerClass;
};
