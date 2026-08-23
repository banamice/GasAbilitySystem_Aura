// 


#include "Character/Enemy/EnemyBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComopnent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Aura/Aura.h"


// Sets default values
AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
	
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComopnent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	OnASCReady();
	
}

void AEnemyBase::OnASCReady()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	if (UAuraAbilitySystemComopnent* ASC = Cast<UAuraAbilitySystemComopnent>(GetAbilitySystemComponent()))
	{
		ASC->InitAsc();
	}
}

void AEnemyBase::EnableHighLight()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(OUTLINE_COLOR_RED);
	WeaponMesh->SetRenderCustomDepth(true);
	WeaponMesh->SetCustomDepthStencilValue(OUTLINE_COLOR_RED);
}

void AEnemyBase::DisableHighLight()
{
	GetMesh()->SetRenderCustomDepth(false);
	WeaponMesh->SetRenderCustomDepth(false);
}




