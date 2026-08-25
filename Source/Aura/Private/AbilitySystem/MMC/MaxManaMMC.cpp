// 


#include "AbilitySystem/MMC/MaxManaMMC.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interactive/ICombatInterface.h"

UMaxManaMMC::UMaxManaMMC()
{
	
	Cap_Int.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	Cap_Int.bSnapshot = false;
	Cap_Int.AttributeToCapture = UAuraAttributeSet::GetIntAttribute();
	
	RelevantAttributesToCapture.Add(Cap_Int);
}

float UMaxManaMMC::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	
	const FGameplayTagContainer* SouceTags =  Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TagretTags =  Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters Params;
	Params.SourceTags = SouceTags;
	Params.TargetTags = TagretTags;
	
	float Int = 0.f;
	
	GetCapturedAttributeMagnitude(Cap_Int,Spec,Params,Int);
	
	IICombatInterface* CombatInterface = Cast<IICombatInterface>(Spec.GetContext().GetSourceObject());
	check(CombatInterface)
	return 100 + Int * 5 + CombatInterface->GetPlayerLevel() * 10;
	
}

