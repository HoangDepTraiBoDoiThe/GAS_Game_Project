// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "BaseGameplayAbility.h"
#include "SummonGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API USummonGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	TArray<FVector> CalculateMinionSpawnLocation();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MinRadius = 200;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxRadius = 500;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnWidthThreadHold = 90;
};
