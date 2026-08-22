// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class IIHighLightInterface;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	
	virtual  void Tick(float DeltaSeconds) override;
	
protected:
	virtual  void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	void Move(const FInputActionValue& InputData);
	
	TObjectPtr<IIHighLightInterface> LastCursorActor = nullptr;
	TObjectPtr<IIHighLightInterface> CurrentCursorActor = nullptr;
	
	void UpdateUnderCursorHighLight();
	
	
};
