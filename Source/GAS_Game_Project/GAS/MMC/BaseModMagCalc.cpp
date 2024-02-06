// Cu Nhat Hoang 


#include "BaseModMagCalc.h"

#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"
#include "GAS_Game_Project/Interface/CombatInterface.h"

float UBaseModMagCalc::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	float OUT_Mag;
	FAggregatorEvaluateParameters AggregatorEvaluateParameters;
	AggregatorEvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	AggregatorEvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	GetCapturedAttributeMagnitude(AttCapDef, Spec, AggregatorEvaluateParameters, OUT_Mag);

	checkf(Spec.GetEffectContext().GetSourceObject(), TEXT("GameplayEffect's Source object is null"))
	const float CharacterLevel = Cast<ICombatInterface>(Spec.GetEffectContext().GetSourceObject())->GetCharacterLevel();
	
	return BaseAttributeValue + (OUT_Mag * ScaleValuePerModMaCalc) + (CharacterLevel * ScaleValuePerCharacterLevel);
}
