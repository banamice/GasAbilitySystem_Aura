// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraItemBase.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class AURA_API AAuraItemBase : public AActor
{
	GENERATED_BODY()

public:
	AAuraItemBase();

protected:
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

};
