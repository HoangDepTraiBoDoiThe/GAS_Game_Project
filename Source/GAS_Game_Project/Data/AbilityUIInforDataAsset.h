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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 LevelRequireToUnlock = 1;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> AbilityClass;
	
	bool operator==(const FAbilityUIInfoStruct& other) const {
		return InputTag == other.InputTag &&
			   AbilityTag == other.AbilityTag &&
			   AbilityAvailabilityStatus == other.AbilityAvailabilityStatus &&
			   AbilityIcon == other.AbilityIcon &&
			   AbilityBackground == other.AbilityBackground &&
			   LevelRequireToUnlock == other.LevelRequireToUnlock &&
			   AbilityClass == other.AbilityClass;
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
	void ChangeAbilityStatus(const FGameplayTag& AbilityToChange_Tag, const FGameplayTag& StatusTag);
	void ChangeAbilityInputTag(const FGameplayTag& AbilityToChange_Tag, const FGameplayTag& InputTag, const bool bShouldNotifyIfNotFound);
	void MakeAbilitiesUnlockableOnLeveling(const int32 CharacterLevel, TArray<FAbilityUIInfoStruct>& OUTAbilityUIInfos);
	int32 GetAbilityLevelRequirement(const FGameplayTag& AbilityTag);
	TSubclassOf<UGameplayAbility> GetAbilityClass(const FGameplayTag& AbilityTag);
};
