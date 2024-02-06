// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "BaseModMagCalc.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API UBaseModMagCalc : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

protected:
	FGameplayEffectAttributeCaptureDefinition AttCapDef;

	/**The init value of this attribute without any mod.*/
	UPROPERTY(EditAnywhere)
	float BaseAttributeValue {0};
	UPROPERTY(EditAnywhere)
	float ScaleValuePerModMaCalc {1};
	UPROPERTY(EditAnywhere)
	float ScaleValuePerCharacterLevel {1};
	UPROPERTY(EditAnywhere)
	bool bShouldSnapShot {false};
};
