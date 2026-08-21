// 


#include "Character/Enemy/EnemyBase.h"

#include "Aura/Aura.h"


// Sets default values
AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
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

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}


