// 


#include "Player/Input/AuraPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interactive/IHighLightInterface.h"
#include "Player/Input/AuraEnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComopnent.h"
#include "AbilitySystem/AuraGameplayTags.h"
#include "Components/SplineComponent.h"

class UEnhancedInputLocalPlayerSubsystem;

AAuraPlayerController::AAuraPlayerController()
{
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AAuraPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateUnderCursorHighLight();
	AutoMove();
}
void AAuraPlayerController::AutoMove()
{
	if (bIsAutoRunning)
	{
		//找到最近的spline点
		FVector ClosestSplinePoint = Spline->FindLocationClosestToWorldLocation(GetPawn()->GetActorLocation(),ESplineCoordinateSpace::World);
		//找到最近的点的切线
		FVector Direction = Spline->FindDirectionClosestToWorldLocation(ClosestSplinePoint,ESplineCoordinateSpace::World);
		//朝着切线移动
		GetPawn()->AddMovementInput(Direction,1.f);
		
		const float Distance =FVector::Dist2D(
		ClickPosition,
		GetPawn()->GetActorLocation());
		if (Distance < TargetOffset)
		{
			//到达·
			bIsAutoRunning = false;
		}
	}
}

void AAuraPlayerController::UpdateUnderCursorHighLight()
{
	GetHitResultUnderCursor(ECC_Visibility, false,HitResult);
	CurrentCursorActor = HitResult.bBlockingHit
		? Cast<IIHighLightInterface>(HitResult.GetActor())
		: nullptr;
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
	
	UEnhancedInputLocalPlayerSubsystem* LocalInputSystem = GetLocalPlayer()
		? ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())
		: nullptr;
	if (LocalInputSystem && InputMappingContext)
	{
		LocalInputSystem->AddMappingContext(InputMappingContext, 0);
	}
	
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
	
	UAuraEnhancedInputComponent* AuraInputComponent = Cast<UAuraEnhancedInputComponent>(InputComponent);
	if (!IsValid(AuraInputComponent) || !IsValid(MoveAction))
	{
		return;
	}
	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);

	AuraInputComponent->BindAbilityInput(
			InputDataAsset,
			this,
			&ThisClass::AbilityPressed,
			&ThisClass::AbilityReleased,
			&ThisClass::AbilityHold);
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

void AAuraPlayerController::AbilityPressed(FGameplayTag InputTag)
{
	
	
}

void AAuraPlayerController::AbilityReleased(FGameplayTag InputTag)
{
	if (!GetAsc()) return;
	if (!InputTag.MatchesTagExact(AuraTags::Get().InputTag_RMB))
	{
		GetAsc()->OnAbilityInputRelease(InputTag);
	}else
	{
		if (CurrentCursorActor)
		{
			//事发结束
			GetAsc()->OnAbilityInputRelease(InputTag);
		}else
		{
			//右键寻路
			OnMoveClickRelease();
		}
	}
}

void AAuraPlayerController::AbilityHold(FGameplayTag InputTag)
{
	if (!GetAsc()) return;
	if (!InputTag.MatchesTagExact(AuraTags::Get().InputTag_RMB))
	{
		GetAsc()->OnAbilityInputHold(InputTag);
	}else
	{
		if (CurrentCursorActor)
		{
			//右键施法
			GetAsc()->OnAbilityInputHold(InputTag);
		}else
		{
			//右键寻路
			SetMoveCursor();
		}
	}
	
}

void AAuraPlayerController::SetMoveCursor()
{
	ClickTime+=GetWorld()->GetDeltaSeconds();
	if (ClickTime < ShortClickThreshold) return;
	
	bIsAutoRunning = false;
	
	//每帧跟随鼠标移动
	if (!HitResult.bBlockingHit) return;
	
	FVector TargetVector = (HitResult.ImpactPoint - GetPawn()->GetActorLocation()).GetSafeNormal();
	GetPawn()->AddMovementInput(TargetVector, 1.f);
}


void AAuraPlayerController::OnMoveClickRelease()
{
	if (ClickTime < ShortClickThreshold)
	{
		//短按，应该在这里设置自动寻路
		SetAutoRunning();
	}
	//结束
	EndMoveCursor();
}

void AAuraPlayerController::SetAutoRunning()
{
	if (!HitResult.bBlockingHit) return;
	//如果是击中了敌人都走不到这里来。不用检测
	
	const  UNavigationPath* Navi = UNavigationSystemV1::FindPathToLocationSynchronously(
		this,
		GetPawn()->GetActorLocation(),
		HitResult.ImpactPoint);
	
	if (Navi)
	{
		Spline->ClearSplinePoints();
		for (auto Point:Navi->PathPoints)
		{
			Spline->AddSplinePoint(Point,ESplineCoordinateSpace::World);
		}
		if (Navi->PathPoints.Num() == 0)
		{
			ClickPosition = GetPawn()->GetActorLocation();
		}else
		{
			ClickPosition = Navi->PathPoints[Navi->PathPoints.Num()-1];
		}
	}
	
	bIsAutoRunning = true;
}

void AAuraPlayerController::EndMoveCursor()
{
	ClickTime = 0;
}




TObjectPtr<UAuraAbilitySystemComopnent> AAuraPlayerController::GetAsc() 
{
	if (!IsValid(ASC))
	{
		ASC = Cast<UAuraAbilitySystemComopnent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
		return ASC;
	}
	else
	{
		return ASC;
	}
}


