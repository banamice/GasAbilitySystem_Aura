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
	
	
	//~begin IIHighLightInterface
	virtual void EnableHighLight() override;
	virtual void DisableHighLight() override;
	//~end IIHighLightInterface
	
	//begin IICombatInterface
	virtual uint32 GetPlayerLevel() const override;
	//~end IICombatInterface

protected:
	virtual void BeginPlay() override;
	virtual void OnASCReady() override;
	
	UPROPERTY(EditDefaultsOnly,Category= "Course|Attribute")
	uint32 Level = 1;
};
