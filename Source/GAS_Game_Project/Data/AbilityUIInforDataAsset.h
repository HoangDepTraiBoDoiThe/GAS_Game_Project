// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilityUIInforDataAsset.generated.h"

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
	TObjectPtr<UTexture> AbilityIcon = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> AbilityBackground = nullptr;
};

UCLASS()
class GAS_GAME_PROJECT_API UAbilityUIInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FAbilityUIInfoStruct> AbilityUIInfoStructs;
};
