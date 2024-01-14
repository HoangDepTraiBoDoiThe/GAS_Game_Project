// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "BaseAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GAS_GAME_PROJECT_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_HitPoint, BlueprintReadOnly, VisibleAnywhere)
	FGameplayAttributeData HitPoint;
	ATTRIBUTE_ACCESSORS(ThisClass, HitPoint)

	UPROPERTY(Replicated, ReplicatedUsing = OnRep_MaxHitPoint, BlueprintReadOnly, VisibleAnywhere)
	FGameplayAttributeData MaxHitPoint;
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHitPoint);

	UPROPERTY(Replicated, ReplicatedUsing = OnRep_MaxHitPoint, BlueprintReadOnly, VisibleAnywhere)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(ThisClass, Mana)
	
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_MaxHitPoint, BlueprintReadOnly, VisibleAnywhere)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(ThisClass, MaxMana)
	
private:
	UFUNCTION()
	void OnRep_HitPoint(const FGameplayAttributeData& LastVal) const;
	UFUNCTION()
	void OnRep_MaxHitPoint(const FGameplayAttributeData& LastVal) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& LastVal) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& LastVal) const;
};
