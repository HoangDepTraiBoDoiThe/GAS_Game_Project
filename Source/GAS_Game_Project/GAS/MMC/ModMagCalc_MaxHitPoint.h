// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "ModMagCalc_MaxHitPoint.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API UModMagCalc_MaxHitPoint : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UModMagCalc_MaxHitPoint();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

protected:
	// Important: Remember to set this
	UPROPERTY(VisibleAnywhere)
	FGameplayAttribute AttributeToCapture;
	FGameplayEffectAttributeCaptureDefinition AttCapDef;

	/**The init value of this attribute without any mod.*/
	UPROPERTY(EditAnywhere)
	float BaseAttributeValue = 100;
	UPROPERTY(EditAnywhere)
	float ScaleValuePerModMaCalc = 1;
	UPROPERTY(EditAnywhere)
	float ScaleValuePerCharacterLevel = 1;
	UPROPERTY(VisibleAnywhere)
	bool bShouldSnapShot {false};
};
