// 


#include "Character/AuraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComopnent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Player/Input/AuraPlayerController.h"
#include "Player/PlayerState/AuraPlayerState.h"


AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AAuraCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}



void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::OnASCReady()
{
}

void AAuraCharacterBase::ApplyGEToSelf(const TSubclassOf<UGameplayEffect>& GEClass, float Level)
{
	check(GetAbilitySystemComponent())
	check(GetAttributeSet())
	check(GEClass)
	
	FGameplayEffectContextHandle Context =  GetAbilitySystemComponent()->MakeEffectContext();
	Context.AddSourceObject(this);
	FGameplayEffectSpecHandle Spec = GetAbilitySystemComponent()->MakeOutgoingSpec(GEClass,Level,Context);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*Spec.Data,GetAbilitySystemComponent());
}

void AAuraCharacterBase::InitAS()
{
	ApplyGEToSelf(PrimaryASInitial,1.f);
	ApplyGEToSelf(SecondaryASInitial,1.f);
	ApplyGEToSelf(VitalASInitial,1.f);
}




