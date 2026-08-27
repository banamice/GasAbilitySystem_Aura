// 


#include "AbilitySystem/DataAsset/AuraAttributeDataAsset.h"

FAuraAttributeData UAuraAttributeDataAsset::GetAttributeData(FGameplayTag AttributeTag)
{
	for (auto& Data : AttributeDataList)
	{
		if (Data.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Data;
		}
	}
	
	return FAuraAttributeData() ;
}
