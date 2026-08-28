// 

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayAbilityBase.h"
#include "AuraFireBall.generated.h"

class AAuraProjectile;
/**
 * 
 */
UCLASS()
class AURA_API UAuraFireBall : public UAuraGameplayAbilityBase
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;


private:
	UPROPERTY(EditDefaultsOnly,Category="Aura|Projectile")
	TSubclassOf<AAuraProjectile> ProjectileClass;
};
