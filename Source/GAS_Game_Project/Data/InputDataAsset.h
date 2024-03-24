// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InputDataAsset.generated.h"

struct FGameplayTag;
class UInputAction;

USTRUCT(BlueprintType)
struct FGASInputActions
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};
/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API UInputDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UInputAction* FindAbilityInputActionByTag(const FGameplayTag&, bool bShouldLog);
	
	UPROPERTY(EditAnywhere)
	TArray<FGASInputActions> AbilityInputActions;
	
};
