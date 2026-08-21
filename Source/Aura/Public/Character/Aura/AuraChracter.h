// 

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraChracter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class AURA_API AAuraChracter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraChracter();

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	
};
