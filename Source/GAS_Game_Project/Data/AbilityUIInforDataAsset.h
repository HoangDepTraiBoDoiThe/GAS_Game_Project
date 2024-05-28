// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataAsset.h"
#include "GAS_Game_Project/GAS/GamplayTag/MyGameplayTags.h"
#include "AbilityUIInforDataAsset.generated.h"

class UGameplayAbility;
/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct FAbilityUIInfoStruct
{
	GENERATED_BODY()
	FAbilityUIInfoStruct() {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag = FGameplayTag();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag = FGameplayTag();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityAvailabilityStatus = MyGameplayTags::Get().Ability_Availability_NotUnlockable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture> AbilityIcon = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> AbilityBackground = nullptr;
	
	bool operator==(const FAbilityUIInfoStruct& other) const {
		return InputTag == other.InputTag &&
			   AbilityTag == other.AbilityTag &&
			   AbilityAvailabilityStatus == other.AbilityAvailabilityStatus &&
			   AbilityIcon == other.AbilityIcon &&
			   AbilityBackground == other.AbilityBackground;
	}
};

UCLASS()
class GAS_GAME_PROJECT_API UAbilityUIInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FAbilityUIInfoStruct> AbilityUIInfoStructs;

	FAbilityUIInfoStruct GetAbilityUIInfoStructByInputTag(const FGameplayTag& InputTag, bool bShouldNotifyIfNotFound = false);
	FAbilityUIInfoStruct GetAbilityUIInfoStructByAbilityTag(const FGameplayTag& AbilityTag, bool bShouldNotifyIfNotFound = false);
	void ChangeAbilityStatus(const FGameplayTag& AbilityToChange_Tag, const FGameplayTag& StatusTag);
	void ChangeAbilityInputTag(const FGameplayTag& AbilityToChange_Tag, const FGameplayTag& InputTag, const bool bShouldNotifyIfNotFound);
};
