// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "XPDataAsset.generated.h"

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
	
};

UCLASS()
class GAS_GAME_PROJECT_API UXPDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	int32 GetLevelByXP(const int32 XP, const int32 CurrentLevel = 1);

	// This Array's indexes will be using as Level. Ignore the first index as it will not be use.
	UPROPERTY(EditDefaultsOnly)
	TArray<FXPInfoStruct> XPInfos;
private:

	
};
