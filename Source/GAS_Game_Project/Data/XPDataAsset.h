// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "XPDataAsset.generated.h"

class UBaseGameplayAbility;
/**
 * 
 */
USTRUCT()
struct FXPInfoStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 XPRequirementForNextLevel{0};

	UPROPERTY(EditDefaultsOnly)
	int32 AbilityPoint{1};

	UPROPERTY(EditDefaultsOnly)
	int32 AttributePoint{1};

	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, TSubclassOf<UBaseGameplayAbility>> AbilityClasses;
};

UCLASS()
class GAS_GAME_PROJECT_API UXPDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	int32 GetLevelByXP(const int32 XP, const int32 CurrentLevel = 1);
	void GetRewards(int32& OutAttributePoint, int32& OutAbilityPoint, TMap<FGameplayTag, TSubclassOf<UBaseGameplayAbility>>& OutAbilityClasses, const int32 RewardAtLevel = 1);
	int32 GetXPRequirementForCurrentLevel(const int32 Level);

	// This Array's indexes will be using as Level. Ignore the first index as it will not be use.
	UPROPERTY(EditDefaultsOnly)
	TArray<FXPInfoStruct> XPInfos;
private:

	
};
