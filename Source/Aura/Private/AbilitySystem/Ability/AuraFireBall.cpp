// 


#include "AbilitySystem/Ability/AuraFireBall.h"

#include "Actor/Projectile/AuraProjectile.h"
#include "Interactive/ICombatInterface.h"

void UAuraFireBall::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (!HasAuthority(&ActivationInfo) ) return;
	
	IICombatInterface* CombatInterface = Cast<IICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		FTransform SpawnTransform  ;
		SpawnTransform.SetLocation(CombatInterface->GetProjectileSpawnLocation());
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn,
			ESpawnActorScaleMethod::MultiplyWithRoot);	
		
		Projectile->FinishSpawning(SpawnTransform);
	}

	
}
