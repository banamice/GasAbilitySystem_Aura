// 

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "AuraItemBase.generated.h"

class UGameplayEffect;
class USphereComponent;
class UStaticMeshComponent;

UENUM()
enum class EAuraGETime : uint8
{
	EBeginOverlap,
	EEndOverlap,
	ENone
};

//一个GE的应用时机和取消时机
USTRUCT(BlueprintType)
struct FGEOPTime
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayEffect> GameplayEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAuraGETime ApplyTIME = EAuraGETime::ENone;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAuraGETime RemoveTime = EAuraGETime::ENone;
};

UCLASS()
class AURA_API AAuraItemBase : public AActor
{
	GENERATED_BODY()

public:
	AAuraItemBase();

protected:
	virtual void BeginPlay() override;
	
	
	UFUNCTION(BlueprintCallable)
	void ApplyGE( AActor*  TargetActor,const FGEOPTime& GEOPTime);
	
	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* TargetActor);
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
private:
	UPROPERTY(EditDefaultsOnly,Category="Effect")
	TArray<FGEOPTime> GEOPTimeArray;
	
	UPROPERTY()
	TMap<FActiveGameplayEffectHandle,AActor*> RemoveOnEndOverlap;
	
	UPROPERTY(EditAnywhere,Category="Effect")
	float EffectLevel = 1.f;
	

};
