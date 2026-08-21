// 


#include "Player//Input/AuraPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interactive/IHighLightInterface.h"

class UEnhancedInputLocalPlayerSubsystem;

void AAuraPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateUnderCursorHighLight();
}

void AAuraPlayerController::UpdateUnderCursorHighLight()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false,HitResult);
	if (!HitResult.bBlockingHit) return;
	
	CurrentCursorActor = Cast<IIHighLightInterface>(HitResult.GetActor());
	/*
	 * 几种情况 A 为上一次 B为这次
	 * 1.两次都是null 那么啥也不干
	 * 2.上一次是null 这一次不是 那么给这一次开
	 * 3.上一次不是null 这一次是null 那么给上一次关
	 * 4.上一次不是 这一次也不是 但是不同 那么关上一次 开这次
	 * 5.上一次不是 这一次也不是 但是相同 那么啥也不干
	 */
	if (LastCursorActor)
	{
		if (CurrentCursorActor)
		{
			if (CurrentCursorActor == LastCursorActor)
			{
				//5.啥也不干
			}else
			{
				//4.关上一次 开这次
				LastCursorActor->DisableHighLight();
				CurrentCursorActor->EnableHighLight();
			}
		}else
		{
			//3.给上一次关
			LastCursorActor->DisableHighLight();
		}
	}else
	{
		if (CurrentCursorActor)
		{
			//2.给这一次开
			CurrentCursorActor->EnableHighLight();
		}else
		{
			//1.啥也不干
		}
	}
	
	
	LastCursorActor = CurrentCursorActor;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	check(InputMappingContext);
	
	UEnhancedInputLocalPlayerSubsystem* LocalInputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(LocalInputSystem);
	LocalInputSystem->AddMappingContext(InputMappingContext, 0);
	
	bShowMouseCursor =	true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	check(MoveAction);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputData)
{
	FVector2D Data = InputData.Get<FVector2D>();
	
	FVector ForwardVector = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X);
	FVector RightVector = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y);

	if (APawn* LocalPawn = GetPawn<APawn>())
	{
		LocalPawn->AddMovementInput(ForwardVector, Data.Y);
		LocalPawn->AddMovementInput(RightVector, Data.X);
	}
}



