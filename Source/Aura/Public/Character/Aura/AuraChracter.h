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
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const; 
	
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnRep_PlayerState() override;
	//begin IICombatInterface
	virtual uint32 GetPlayerLevel() const override;
	virtual FVector GetProjectileSpawnLocation() const override;
	//~end IICombatInterface

protected:
	virtual void BeginPlay() override;
	virtual void OnASCReady() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	void InitializeASCActorInfo();
	
};
