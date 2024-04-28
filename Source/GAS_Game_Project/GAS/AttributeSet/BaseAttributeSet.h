// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "BaseAttributeSet.generated.h"

/**
 * 
 */

USTRUCT()
struct FGameplayEffectPropertiesStruct
{
	GENERATED_BODY()
	
	UPROPERTY()
	FGameplayEffectContextHandle EffectContextHandle;
	UPROPERTY()
	TObjectPtr<AController> SourceActorController;
	UPROPERTY()
	TObjectPtr<AActor> SourceAvatarActor;
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceASC;

	UPROPERTY()
	TObjectPtr<AController> TargetActorController;
	UPROPERTY()
	TObjectPtr<AActor> TargetAvatarActor;
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetASC;
};

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

template<typename T>
using TStaticFunctionPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

UCLASS()
class GAS_GAME_PROJECT_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UBaseAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	FORCEINLINE TMap<FGameplayTag, TStaticFunctionPtr<FGameplayAttribute()>> GetAttributeTagMap() {return AttributeTagMap;}

	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Strength)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Intelligence);
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Vigor)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Resilience)

	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxHitPoint)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, HitPoint)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Mana)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxMana)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Armor)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, ArmorPenetration)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, BlockChance)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, CriticalHitChance)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, CriticalHitDamage)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, CriticalHitResistance)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, HealthRegeneration)
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, ManaRegeneration)
	
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, HitPointMeta)

	FGameplayEffectPropertiesStruct GameplayEffectPropertiesStruct;
	
protected:
#pragma region Primary attributes

	UPROPERTY(ReplicatedUsing = OnRep_Strength, BlueprintReadOnly, EditAnywhere)
	FGameplayAttributeData Strength;

	UPROPERTY(ReplicatedUsing = OnRep_Intelligence, EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Intelligence;

	UPROPERTY(ReplicatedUsing = OnRep_Vigor, EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Vigor;

	UPROPERTY(ReplicatedUsing = OnRep_Resilience, EditDefaultsOnly, BlueprintReadOnly)
	FGameplayAttributeData Resilience;

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligent) const;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	
#pragma endregion Primary attributes
	
#pragma region Secondary attributes
	UPROPERTY(ReplicatedUsing = OnRep_HitPoint, BlueprintReadOnly, Category = Attribute)
	FGameplayAttributeData HitPoint;
	
	UPROPERTY(ReplicatedUsing = OnRep_MaxHitPoint)
	FGameplayAttributeData MaxHitPoint;	

	UPROPERTY(ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;	

	UPROPERTY(ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	
	UPROPERTY(ReplicatedUsing = OnRep_Armor, EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Armor;

	UPROPERTY(ReplicatedUsing = OnRep_ArmorPenetration, EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData ArmorPenetration;

	UPROPERTY(ReplicatedUsing = OnRep_BlockChance, EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData BlockChance;

	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitChance, EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData CriticalHitChance;

	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitDamage, EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData CriticalHitDamage;

	UPROPERTY(ReplicatedUsing = OnRep_CriticalHitResistance, EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData CriticalHitResistance;

	UPROPERTY(ReplicatedUsing = OnRep_HealthRegeneration, EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData HealthRegeneration;

	UPROPERTY(ReplicatedUsing = OnRep_ManaRegeneration, EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData ManaRegeneration;
#pragma endregion

#pragma region Meta Attributes
	UPROPERTY(VisibleAnywhere, Category="Meta Attributes")
	FGameplayAttributeData HitPointMeta;
	
	UFUNCTION()
	void OnRep_HitPoint(const FGameplayAttributeData& OldHitPoint) const;
	UFUNCTION()
	void OnRep_MaxHitPoint(const FGameplayAttributeData& OldMaxHitPoint) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OlCriticalHitResistance) const;
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

protected:
	TMap<FGameplayTag, TStaticFunctionPtr<FGameplayAttribute()>> AttributeTagMap;

private:

};
