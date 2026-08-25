// 


#include "Character/Aura/AuraChracter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComopnent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/PlayerState/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"


class UEnhancedInputLocalPlayerSubsystem;
class AAuraPlayerState;

AAuraChracter::AAuraChracter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->TargetArmLength = 600.f;
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->SetupAttachment(GetRootComponent());
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
	
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

UAbilitySystemComponent* AAuraChracter::GetAbilitySystemComponent() const
{
	
	return Super::GetAbilitySystemComponent();
	
}

UAttributeSet* AAuraChracter::GetAttributeSet() const
{
	return Super::GetAttributeSet();
}

void AAuraChracter::BeginPlay()
{
	Super::BeginPlay();
	
}



void AAuraChracter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	OnASCReady();
	
}

void AAuraChracter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	OnASCReady();
	
}

uint32 AAuraChracter::GetPlayerLevel() const
{
	AAuraPlayerState * AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetLevel();
}

void AAuraChracter::OnASCReady()
{
	InitializeASCActorInfo();
	if (UAuraAbilitySystemComopnent* ASC = Cast<UAuraAbilitySystemComopnent>(GetAbilitySystemComponent()))
	{
		ASC->InitAsc();
	}
	InitAS();
}

void AAuraChracter::InitializeASCActorInfo()
{
	AAuraPlayerState * AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);

	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState,this);
	
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();

	//这样会导致其他的玩家的ps复制过来的时候都会去初始化一下本地玩家的hud  需要判断一下是不是本地玩家再操作
	if (IsLocallyControlled())
	{
		if(APlayerController* PlayerController  =GetWorld()->GetFirstPlayerController() )
		{
			if(AAuraHUD* HUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
			{
				HUD->InitializeOverlayWidget(AuraPlayerState,PlayerController,AbilitySystemComponent,AttributeSet);
			}
		}
	}
	
}


