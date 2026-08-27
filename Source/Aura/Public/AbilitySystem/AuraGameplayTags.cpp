#include "AbilitySystem/AuraGameplayTags.h"

#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

void AuraTags::Init()
{
	/*
	 * PrimaryAttribute
	 */
	Get().Attributes_Primary_Str = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Str"), FString("Str"));
	Get().Attributes_Primary_Int = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Int"), FString("Int"));
	Get().Attributes_Primary_Luck = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Luck"), FString("Luck"));
	Get().Attributes_Primary_Def = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Def"), FString("Def"));
	/*
	 * EndPrimaryAttribute
	 */

	/*
	 * Vital Attribute
	 */
	Get().Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"), FString("Health"));
	Get().Attributes_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"), FString("Mana"));
	/*
	 * End Vital Attribute
	 */

	/*
	 * SecondaryAttribute
	 */
	Get().Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("MaxHealth"));
	Get().Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), FString("MaxMana"));
	Get().Attributes_Secondary_PhysicalDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.PhysicalDamage"),FString("PhysicalDamage"));
	Get().Attributes_Secondary_MagicDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MagicDamage"), FString("MagicDamage"));
	Get().Attributes_Secondary_CriticalChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalChance"), FString("CriticalChance"));
	Get().Attributes_Secondary_CriticalDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalDamage"), FString("CriticalDamage"));
	Get().Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"), FString("HealthRegeneration"));
	Get().Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"), FString("ManaRegeneration"));
	Get().Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"), FString("BlockChance"));
	/*
	 * EndSecondaryAttribute
	 */
}

AuraTags AuraTags::Instance;
