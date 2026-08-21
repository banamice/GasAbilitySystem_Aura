// 

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interactive/IHighLightInterface.h"
#include "EnemyBase.generated.h"

UCLASS()
class AURA_API AEnemyBase : public AAuraCharacterBase,public IIHighLightInterface
{
	GENERATED_BODY()

public:
	AEnemyBase();
	virtual void EnableHighLight() override;
	virtual void DisableHighLight() override;

protected:
	virtual void BeginPlay() override;
};
