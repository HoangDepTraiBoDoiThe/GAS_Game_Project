// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */
class GAS_GAME_PROJECT_API MyGameplayTags
{
public:
 static const MyGameplayTags& Get() {return GameplayTags;}
 static void InitNativeGameplayTags ();

 /*
 *	Vital attributes
 */
 FGameplayTag Attribute_Vital_HitPoint;
 FGameplayTag Attribute_Vital_Mana;

 /*
  *	Primary attributes
  */
 FGameplayTag Attribute_Primary_Intelligence;
 FGameplayTag Attribute_Primary_Strength;
 FGameplayTag Attribute_Primary_Vigor;
 FGameplayTag Attribute_Primary_Resilience;
	
 /*
  *	Secondary attributes
  */
 FGameplayTag Attribute_Secondary_Armor;
 FGameplayTag Attribute_Secondary_ArmorPenetration;
 FGameplayTag Attribute_Secondary_BlockChance;
 FGameplayTag Attribute_Secondary_CriticalHitChance;
 FGameplayTag Attribute_Secondary_CriticalHitDamage;
 FGameplayTag Attribute_Secondary_CriticalHitResistance;
 FGameplayTag Attribute_Secondary_HealthRegeneration;
 FGameplayTag Attribute_Secondary_ManaRegeneration;
 FGameplayTag Attribute_Secondary_MaxHitPoint;
 FGameplayTag Attribute_Secondary_MaxMana;

 /*
  * Input Tags 
  */
 FGameplayTag Control_Movement;
 FGameplayTag Control_LMB;
 FGameplayTag Control_RMB;
 FGameplayTag Test_Ability_1;
 
protected:

private:
 static MyGameplayTags GameplayTags;
 
}
;
