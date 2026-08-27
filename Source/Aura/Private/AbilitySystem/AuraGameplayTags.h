#pragma once
#include "GameplayTagContainer.h"


struct AuraTags
{
public:
	static AuraTags& Get(){ return Instance;}
	static void Init();
	
	/*
	 * PrimaryAttribute
	 */
	FGameplayTag Attributes_Primary_Str;
	FGameplayTag Attributes_Primary_Int;
	FGameplayTag Attributes_Primary_Luck;
	FGameplayTag Attributes_Primary_Def;
	/*
	 * EndPrimaryAttribute
	 */

	/*
	 * Vital Attribute
	 */
	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_Mana;
	/*
	 * End Vital Attribute
	 */

	/*
	 * SecondaryAttribute
	 */
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_PhysicalDamage;
	FGameplayTag Attributes_Secondary_MagicDamage;
	FGameplayTag Attributes_Secondary_CriticalChance;
	FGameplayTag Attributes_Secondary_CriticalDamage;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_BlockChance;
	/*
	 * EndSecondaryAttribute
	 */
private:
	static AuraTags Instance;
};
