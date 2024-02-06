// Cu Nhat Hoang


#include "ModMagCalc_MaxHitPoint.h"

#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"
#include "GAS_Game_Project/Interface/CombatInterface.h"

UModMagCalc_MaxHitPoint::UModMagCalc_MaxHitPoint()
{
	AttributeToCapture = UBaseAttributeSet::GetVigorAttribute();

	AttCapDef.bSnapshot = bShouldSnapShot;
	AttCapDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	AttCapDef.AttributeToCapture = AttributeToCapture;
	RelevantAttributesToCapture.Add(AttCapDef);
}

float UModMagCalc_MaxHitPoint::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	float OUT_Mag;
	FAggregatorEvaluateParameters AggregatorEvaluateParameters;
	AggregatorEvaluateParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	AggregatorEvaluateParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	GetCapturedAttributeMagnitude(AttCapDef, Spec, AggregatorEvaluateParameters, OUT_Mag);

	checkf(Spec.GetEffectContext().GetSourceObject(), TEXT("GameplayEffect's Source object is null"))
	checkf(Spec.Def, TEXT("GameplayEffect's is null"))
	ICombatInterface* Character = Cast<ICombatInterface>(Spec.GetEffectContext().GetSourceObject());
	checkf(Character, TEXT("GameplayEffect's is null"))
	const float CharacterLevel = Character->GetCharacterLevel();
	
	return BaseAttributeValue + (OUT_Mag * ScaleValuePerModMaCalc) + (CharacterLevel * ScaleValuePerCharacterLevel);
}
