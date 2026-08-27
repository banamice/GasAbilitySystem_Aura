// 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AuraAttributeDataAsset.generated.h"


USTRUCT(BlueprintType)
struct FAuraAttributeData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FGameplayTag AttributeTag;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FText AttributeName;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FText AttributeDescription;
	UPROPERTY(BlueprintReadOnly)
	float DefaultValue;
};
/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	FAuraAttributeData GetAttributeData(FGameplayTag AttributeTag);
	
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FAuraAttributeData> AttributeDataList;
};
