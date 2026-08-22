// 


#include "Actor/Item/AuraItemBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"


AAuraItemBase::AAuraItemBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneComponent"));
}

void AAuraItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraItemBase::ApplyGE( AActor* TargetActor, const FGEOPTime& GEOPTime)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (! ASC) return;
	
 	check(GEOPTime.GameplayEffectClass);
	
	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	
	FGameplayEffectSpecHandle Spec =  ASC->MakeOutgoingSpec(GEOPTime.GameplayEffectClass,EffectLevel,ContextHandle);
	
	FActiveGameplayEffectHandle ActiveHandle  =  ASC->ApplyGameplayEffectSpecToSelf(*Spec.Data);
	//通过spec查看是否是inifity的并且需要在离开时结束
	if (Spec.Data->Def->DurationPolicy == EGameplayEffectDurationType::Infinite && GEOPTime.RemoveTime == EAuraGETime::EEndOverlap)
	{
		//以ActiveHandle为key actor为value存下来这个需要移除的GE
		RemoveOnEndOverlap.Add(ActiveHandle,TargetActor);
	}
}

void AAuraItemBase::OnBeginOverlap(AActor* TargetActor)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (! ASC) return;
	
	for (auto & GE : GEOPTimeArray)
	{
		if (GE.ApplyTIME == EAuraGETime::EBeginOverlap)
		{
			ApplyGE(TargetActor,GE);
		}
	}
}

void AAuraItemBase::OnEndOverlap(AActor* TargetActor)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (! ASC) return;
	
	for (auto & GE : GEOPTimeArray)
	{
		if (GE.ApplyTIME == EAuraGETime::EEndOverlap)
		{
			ApplyGE(TargetActor,GE);
		}
	}
	
	TArray<FActiveGameplayEffectHandle> GEToRemove;
	for (auto& GE:RemoveOnEndOverlap)
	{
		if (!IsValid(GE.Value))
		{
			//说明这个Actor已经无效了  比如说可能在范围内但是被销毁了。我也不要一直存着
			GEToRemove.Add(GE.Key);
			continue;
		}
		
		if (GE.Value == TargetActor)
		{
			GEToRemove.Add(GE.Key);
			ASC->RemoveActiveGameplayEffect(GE.Key,1.f);
		}
	}
	for (auto&GE:GEToRemove)
	{
		RemoveOnEndOverlap.Remove(GE);
	}
}




