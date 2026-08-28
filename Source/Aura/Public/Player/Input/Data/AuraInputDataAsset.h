// 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraInputDataAsset.generated.h"


class UInputAction;

USTRUCT(BlueprintType)
struct FAuraInputData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction = nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FGameplayTag InputTag;
};

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	const UInputAction* GetInputAction(const FGameplayTag& InputTag);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FAuraInputData> InputDataArray;
};
