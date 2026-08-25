// 


#include "AbilitySystem/MMC/MaxHealthMMC.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interactive/ICombatInterface.h"

UMaxHealthMMC::UMaxHealthMMC()
{
	
	Cap_Str.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	Cap_Str.bSnapshot = false;
	Cap_Str.AttributeToCapture = UAuraAttributeSet::GetStrAttribute();
	
	RelevantAttributesToCapture.Add(Cap_Str);
}

float UMaxHealthMMC::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	
	const FGameplayTagContainer* SouceTags =  Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TagretTags =  Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters Params;
	Params.SourceTags = SouceTags;
	Params.TargetTags = TagretTags;
	
	float Str = 0.f;
	
	GetCapturedAttributeMagnitude(Cap_Str,Spec,Params,Str);
	
	IICombatInterface* CombatInterface = Cast<IICombatInterface>(Spec.GetContext().GetSourceObject());
	check(CombatInterface)
	return 100 + Str * 5 + CombatInterface->GetPlayerLevel() * 10;
	
}
