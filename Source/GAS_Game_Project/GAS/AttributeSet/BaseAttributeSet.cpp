// Cu Nhat Hoang


#include "BaseAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "GAS_Game_Project/Character/Player/Controller/BasePlayerController.h"
#include "GAS_Game_Project/GAS/GamplayTag/MyGameplayTags.h"
#include "GAS_Game_Project/Interface/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

UBaseAttributeSet::UBaseAttributeSet()
{
	AttributeTagMap.Add(MyGameplayTags::Get().Attribute_Primary_Strength, GetStrengthAttribute);
	AttributeTagMap.Add(MyGameplayTags::Get().Attribute_Primary_Intelligence, GetIntelligenceAttribute);
	AttributeTagMap.Add(MyGameplayTags::Get().Attribute_Primary_Vigor, GetVigorAttribute);
	AttributeTagMap.Add(MyGameplayTags::Get().Attribute_Primary_Resilience, GetResilienceAttribute);
	AttributeTagMap.Add(MyGameplayTags::Get().Attribute_Secondary_Armor, GetArmorAttribute);
	AttributeTagMap.Add(MyGameplayTags::Get().Attribute_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
	AttributeTagMap.Add(MyGameplayTags::Get().Attribute_Secondary_BlockChance, GetBlockChanceAttribute);
	AttributeTagMap.Add(MyGameplayTags::Get().Attribute_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
	AttributeTagMap.Add(MyGameplayTags::Get().Attribute_Secondary_ManaRegeneration, GetManaAttribute);
	AttributeTagMap.Add(MyGameplayTags::Get().Attribute_Secondary_MaxMana, GetMaxManaAttribute);
	AttributeTagMap.Add(MyGameplayTags::Get().Attribute_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute);
	AttributeTagMap.Add(MyGameplayTags::Get().Attribute_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute);
	AttributeTagMap.Add(MyGameplayTags::Get().Attribute_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute);
	AttributeTagMap.Add(MyGameplayTags::Get().Attribute_Secondary_MaxHitPoint, GetMaxHitPointAttribute);
}

void UBaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, HitPoint, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHitPoint, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Mana, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxMana, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Strength, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Intelligence, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Vigor, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Resilience, COND_None, REPNOTIFY_Always)
}

void UBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHitPointAttribute()) NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHitPoint());
	else if (Attribute == GetManaAttribute()) NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	GameplayEffectPropertiesStruct.EffectContextHandle = Data.EffectSpec.GetEffectContext();
	if (GameplayEffectPropertiesStruct.EffectContextHandle.IsValid())
		GameplayEffectPropertiesStruct.SourceASC = GameplayEffectPropertiesStruct.EffectContextHandle.
			GetInstigatorAbilitySystemComponent();

	if (GameplayEffectPropertiesStruct.SourceASC)
		GameplayEffectPropertiesStruct.SourceAvatarActor = GameplayEffectPropertiesStruct.SourceASC->GetAvatarActor();

	if (GameplayEffectPropertiesStruct.SourceAvatarActor)
		GameplayEffectPropertiesStruct.SourceActorController = GameplayEffectPropertiesStruct.SourceASC->
			AbilityActorInfo->AvatarActor->GetInstigatorController();

	GameplayEffectPropertiesStruct.TargetASC = Data.Target;
	if (GameplayEffectPropertiesStruct.TargetASC)
	{
		GameplayEffectPropertiesStruct.TargetAvatarActor = GameplayEffectPropertiesStruct.TargetASC->GetAvatarActor();
		GameplayEffectPropertiesStruct.TargetActorController = GameplayEffectPropertiesStruct.TargetASC->
			GetAvatarActor()->GetInstigatorController();
		if (!GameplayEffectPropertiesStruct.TargetActorController)
			UE_LOG(LogTemp, Warning, TEXT("GameplayEffectPropertiesStruct.TargetActorController is null"))
	}

	if (Data.EvaluatedData.Attribute == GetHitPointMetaAttribute())
	{
		const float CacheDamage = GetHitPointMeta();
		SetHitPointMeta(0.f);
		UE_LOG(LogTemp, Warning, TEXT("CacheDamage: %f"), CacheDamage)

		if (CacheDamage > 0.f)
		{
			UE_LOG(LogTemp, Warning, TEXT("CacheDamage: %f"), CacheDamage)
			SetHitPoint(FMath::Clamp(GetHitPoint() - CacheDamage, 0.f, GetMaxHitPoint()));
			if (GetHitPoint() > 0.f)
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(MyGameplayTags::Get().Effects_OnHitReact);
				GetOwningAbilitySystemComponent()->TryActivateAbilitiesByTag(TagContainer);
			}
			else
			{
				Cast<ICombatInterface>(GetOwningAbilitySystemComponent()->GetAvatarActor())->Die();
			}
		}
		if (ABasePlayerController* PC = Cast<ABasePlayerController>(
			UGameplayStatics::GetPlayerController(GameplayEffectPropertiesStruct.SourceAvatarActor, 0)))
		{
			PC->Client_ShowDamageText(CacheDamage, GameplayEffectPropertiesStruct.TargetAvatarActor);
		}
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	if (Data.EvaluatedData.Attribute == GetHitPointAttribute())
		SetHitPoint(FMath::Clamp(GetHitPoint(), 0.f, GetMaxHitPoint()));
}

void UBaseAttributeSet::OnRep_HitPoint(const FGameplayAttributeData& LastVal) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, HitPoint, LastVal)
}

void UBaseAttributeSet::OnRep_MaxHitPoint(const FGameplayAttributeData& LastVal) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHitPoint, LastVal)
}

void UBaseAttributeSet::OnRep_Mana(const FGameplayAttributeData& LastVal) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Mana, LastVal)
}

void UBaseAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& LastVal) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxMana, LastVal)
}

#pragma region Primary attributes
void UBaseAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Strength, OldStrength)
}

void UBaseAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligent) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Intelligence, OldIntelligent)
}

void UBaseAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Vigor, OldVigor)
}

void UBaseAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Resilience, OldResilience)
}
#pragma endregion Primary attributes

#pragma region Secondary attributes
void UBaseAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Armor, OldArmor)
}

void UBaseAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, ArmorPenetration, OldArmorPenetration)
}

void UBaseAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, BlockChance, OldBlockChance)
}

void UBaseAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, CriticalHitChance, OldCriticalHitChance)
}

void UBaseAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, CriticalHitDamage, OldCriticalHitDamage)
}

void UBaseAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OlCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, CriticalHitResistance, OlCriticalHitResistance)
}

void UBaseAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, HealthRegeneration, OldHealthRegeneration)
}

void UBaseAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, ManaRegeneration, OldManaRegeneration)
}
#pragma endregion Secondary attributes
