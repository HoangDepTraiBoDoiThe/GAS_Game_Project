// Cu Nhat Hoang


#include "ExecCalc_Damage.h"

#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"
#include "GAS_Game_Project/GAS/GamplayTag/MyGameplayTags.h"
#include "GAS_Game_Project/Global/MyBlueprintFunctionLibrary.h"

struct MyDamageStatic
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resilience)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration)
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Fire)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Water)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Wind)

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> Tag2Resistance;
	
	MyDamageStatic()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Armor, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Resilience, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, ArmorPenetration, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, BlockChance, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, CriticalHitChance, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Resistance_Fire, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Resistance_Water, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Resistance_Wind, Source, false)

		Tag2Resistance.Add(MyGameplayTags::Get().DamageType_Elemental_Fire, Resistance_FireDef);
		Tag2Resistance.Add(MyGameplayTags::Get().DamageType_Elemental_Water, Resistance_WaterDef);
		Tag2Resistance.Add(MyGameplayTags::Get().DamageType_Elemental_Wind, Resistance_WindDef);
	}
};

static MyDamageStatic GetMyDamageStatic()
{
	static MyDamageStatic MyDS;
	return MyDS;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	MyGameplayTags::Get().InitNativeGameplayTags();
	RelevantAttributesToCapture.Add(GetMyDamageStatic().ArmorDef);
	RelevantAttributesToCapture.Add(GetMyDamageStatic().ResilienceDef);
	RelevantAttributesToCapture.Add(GetMyDamageStatic().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(GetMyDamageStatic().BlockChanceDef);
	RelevantAttributesToCapture.Add(GetMyDamageStatic().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(GetMyDamageStatic().Resistance_FireDef);
	RelevantAttributesToCapture.Add(GetMyDamageStatic().Resistance_WaterDef);
	RelevantAttributesToCapture.Add(GetMyDamageStatic().Resistance_WindDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	float Armor;
	float ArmorCoe;
	float ArmorPenetration;
	float BlockChance;
	float CriticalHitChance;
	float Resilience;
	AttemptCalculateCapturedAttributeMagnitude(ExecutionParams, GetMyDamageStatic().ArmorDef, Armor);
	AttemptCalculateCapturedAttributeMagnitude(ExecutionParams, GetMyDamageStatic().ArmorPenetrationDef, ArmorPenetration);
	AttemptCalculateCapturedAttributeMagnitude(ExecutionParams, GetMyDamageStatic().BlockChanceDef, BlockChance);
	AttemptCalculateCapturedAttributeMagnitude(ExecutionParams, GetMyDamageStatic().CriticalHitChanceDef, CriticalHitChance);
	AttemptCalculateCapturedAttributeMagnitude(ExecutionParams, GetMyDamageStatic().ResilienceDef, Resilience);
	GetCoeValue(ExecutionParams, "ArmorCoe", ArmorCoe);
	Armor = FMath::Max(0.f, Armor);
	ArmorPenetration = FMath::Max(0.f, ArmorPenetration);
	BlockChance = FMath::Max(0.f, BlockChance);
	CriticalHitChance = FMath::Max(0.f, CriticalHitChance);

	float Damage = 0;
	for (const auto& Pair : GetMyDamageStatic().Tag2Resistance)
	{
		const float DamageType = ExecutionParams.GetOwningSpec().GetSetByCallerMagnitude(Pair.Key, false);
		float ResistanceValue;
		AttemptCalculateCapturedAttributeMagnitude(ExecutionParams, Pair.Value, ResistanceValue);
		Damage += DamageType - ResistanceValue < 0 ? 0.f : DamageType - ResistanceValue;
	}

	const bool bBlockHit = FMath::RandRange(1, 100) <= BlockChance;
	const bool bCritHit = FMath::RandRange(1, 100) <= CriticalHitChance;
	const float DamageAfterCriticalHitChance = bCritHit ? Damage * 2 : Damage;
	const float DamageAfterBlockChange = bBlockHit ? DamageAfterCriticalHitChance / 2 : DamageAfterCriticalHitChance;
	const float ArmorBlockFragmentAfterArmorPenetration = Armor * ArmorCoe * ((100 - ArmorPenetration) / 100);
	const float FinDamage = DamageAfterBlockChange - ArmorBlockFragmentAfterArmorPenetration;

	UMyBlueprintFunctionLibrary::SetupMyGameplayEffectContext(ExecutionParams.GetOwningSpec().GetContext().Get(), bCritHit, bBlockHit);
	
	const FGameplayModifierEvaluatedData GameplayModifierEvaluatedData(UBaseAttributeSet::GetHitPointMetaAttribute(), EGameplayModOp::Additive, FinDamage);	
	OutExecutionOutput.AddOutputModifier(GameplayModifierEvaluatedData);
}

void UExecCalc_Damage::AttemptCalculateCapturedAttributeMagnitude(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	const FGameplayEffectAttributeCaptureDefinition& AttCapDef, float& Magnitude) const
{
	FAggregatorEvaluateParameters AggregatorEvaluateParameters;
	AggregatorEvaluateParameters.SourceTags = ExecutionParams.GetOwningSpec().CapturedSourceTags.GetAggregatedTags();
	AggregatorEvaluateParameters.TargetTags = ExecutionParams.GetOwningSpec().CapturedTargetTags.GetAggregatedTags();
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(AttCapDef, AggregatorEvaluateParameters, Magnitude);
}

void UExecCalc_Damage::GetCoeValue(const FGameplayEffectCustomExecutionParameters& ExecutionParams, const FName RowName, float& ArmorCoe) const
{
	UCurveTable* CoefficientCurveTable = UMyBlueprintFunctionLibrary::GetCoefficientCurveTable(ExecutionParams.GetTargetAbilitySystemComponent()->GetAvatarActor());
	const FRealCurve* ArmorCoeCurve = CoefficientCurveTable->FindCurve(RowName, "CoefficientCurveTable");
	ArmorCoe = ArmorCoeCurve->Eval(Cast<ABaseGameCharacter>(ExecutionParams.GetTargetAbilitySystemComponent()->GetAvatarActor())->GetCharacterLevel());
}
