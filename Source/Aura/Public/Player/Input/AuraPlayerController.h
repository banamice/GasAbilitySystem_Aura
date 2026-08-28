// 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class USplineComponent;
class UAuraAbilitySystemComopnent;
class UAuraInputDataAsset;
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
	AAuraPlayerController();
	virtual  void Tick(float DeltaSeconds) override;
	
protected:
	virtual  void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;
	
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction> MoveAction = nullptr;
	
	void Move(const FInputActionValue& InputData);
	
	// UE interfaces are not UObject instances; keep non-owning interface pointers here.
	IIHighLightInterface* LastCursorActor = nullptr;
	IIHighLightInterface* CurrentCursorActor = nullptr;
	
	void UpdateUnderCursorHighLight();
	
	
	void AbilityPressed(FGameplayTag InputTag);
	void AbilityReleased(FGameplayTag InputTag);
	void AbilityHold(FGameplayTag InputTag);
	
	
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UAuraInputDataAsset> InputDataAsset = nullptr;
	
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComopnent> ASC;
	TObjectPtr<UAuraAbilitySystemComopnent>GetAsc() ;
	
	/*
	 * Click to Move
	 */
	FHitResult HitResult;
	float ClickTime = 0.0f;
	UPROPERTY(EditAnywhere,Category = "Aura|Click to Move")
	float ShortClickThreshold = 0.2f;
	UPROPERTY(EditAnywhere,Category = "Aura|Click to Move")
	float TargetOffset = 100.0f;
	FVector ClickPosition = FVector::ZeroVector;
	bool bIsAutoRunning = false;
	UPROPERTY()
	TObjectPtr<USplineComponent> Spline;
	
	void SetMoveCursor();
	void OnMoveClickRelease();
	void SetAutoRunning();
	void EndMoveCursor();
	void AutoMove();
	
	
	/*
	 * End Click to Move
	 */
	
};