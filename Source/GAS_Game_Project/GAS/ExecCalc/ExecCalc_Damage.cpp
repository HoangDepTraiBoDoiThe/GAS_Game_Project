// Cu Nhat Hoang


#include "ExecCalc_Damage.h"

#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"
#include "GAS_Game_Project/GAS/GamplayTag/MyGameplayTags.h"
#include "GAS_Game_Project/Global/MyBlueprintFunctionLibrary.h"

struct MyDamageStatic
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration)
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance)
	
	MyDamageStatic()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Armor, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, ArmorPenetration, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, BlockChance, Target, false)
	}
};

static MyDamageStatic GetMyDamageStatic()
{
	static MyDamageStatic MyDS;
	return MyDS;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(GetMyDamageStatic().ArmorDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	float Armor;
	float ArmorPenetration;
	float BlockChance;
	AttemptCalculateCapturedAttributeMagnitude(ExecutionParams, GetMyDamageStatic().ArmorDef, Armor);
	AttemptCalculateCapturedAttributeMagnitude(ExecutionParams, GetMyDamageStatic().ArmorPenetrationDef, ArmorPenetration);
	AttemptCalculateCapturedAttributeMagnitude(ExecutionParams, GetMyDamageStatic().ArmorPenetrationDef, BlockChance);
	BlockChance = FMath::Max(0.f, Armor);
	BlockChance = FMath::Max(0.f, ArmorPenetration);
	BlockChance = FMath::Max(0.f, BlockChance);

	float Damage = ExecutionParams.GetOwningSpec().GetSetByCallerMagnitude(MyGameplayTags::Get().Attribute_Meta_HitPoint);

	float ArmorCoe;
	GetCoeValue(ExecutionParams, "ArmorCoe", ArmorCoe);

	const bool bBlockDamageChance = FMath::RandRange(1, 100) <= BlockChance;
	const float DamageAfterBlockChange = bBlockDamageChance ? Damage / 2 : Damage;
	const float ArmorBlockFragmentAfterArmorPenetration = Armor * ArmorCoe * ((100 - ArmorPenetration) / 100);
	const float FinDamage = DamageAfterBlockChange - ArmorBlockFragmentAfterArmorPenetration;

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
