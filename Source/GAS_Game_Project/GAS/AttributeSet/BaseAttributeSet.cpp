// Cu Nhat Hoang


#include "BaseAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UBaseAttributeSet::UBaseAttributeSet()
{
	InitHitPoint(50.f);
	InitMaxHitPoint(100.f);
	InitMana(50.f);
	InitMaxMana(100.f);
}

void UBaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, HitPoint, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHitPoint, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Mana, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxMana, COND_None, REPNOTIFY_Always)
}

void UBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHitPointAttribute()) NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHitPoint());
	else if (Attribute == GetManaAttribute()) NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	GameplayEffectPropertiesStruct.EffectHandle = Data.EvaluatedData.Handle;
	if (GameplayEffectPropertiesStruct.EffectHandle.IsValid())
		GameplayEffectPropertiesStruct.SourceASC = GameplayEffectPropertiesStruct.EffectHandle.GetOwningAbilitySystemComponent();

	if (GameplayEffectPropertiesStruct.SourceASC)
		GameplayEffectPropertiesStruct.SourceAvatarActor = GameplayEffectPropertiesStruct.SourceASC->GetAvatarActor();

	if (GameplayEffectPropertiesStruct.SourceAvatarActor)
		GameplayEffectPropertiesStruct.SourceActorController = GameplayEffectPropertiesStruct.SourceASC->AbilityActorInfo->AvatarActor->GetInstigatorController();

	GameplayEffectPropertiesStruct.TargetASC = Data.Target;
	if (GameplayEffectPropertiesStruct.TargetASC)
	{
		GameplayEffectPropertiesStruct.TargetAvatarActor = GameplayEffectPropertiesStruct.TargetASC->GetAvatarActor();
		GameplayEffectPropertiesStruct.TargetActorController = GameplayEffectPropertiesStruct.TargetASC->GetAvatarActor()->GetInstigatorController();
		if (!GameplayEffectPropertiesStruct.TargetActorController)
			UE_LOG(LogTemp, Warning, TEXT("GameplayEffectPropertiesStruct.TargetActorController is null"))
	}
}

void UBaseAttributeSet::OnRep_HitPoint(const FGameplayAttributeData& LastVal) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, HitPoint, LastVal)
}

void UBaseAttributeSet::OnRep_MaxHitPoint(const FGameplayAttributeData& LastVal) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHitPoint, LastVal)
}

void UBaseAttributeSet::OnRep_Mana(const FGameplayAttributeData& LastVal) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Mana, LastVal)
}

void UBaseAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& LastVal) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxMana, LastVal)
}
