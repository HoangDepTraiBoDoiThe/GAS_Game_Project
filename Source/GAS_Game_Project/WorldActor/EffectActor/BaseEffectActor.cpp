// Cu Nhat Hoang


#include "BaseEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"

ABaseEffectActor::ABaseEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(FName("Scene component"));
	SetRootComponent(SceneComponent);
}

void ABaseEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	if (!GetAbilitySystemComponent(OtherActor)) return;
	if (EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap) DoApplyGameplayEffect(OtherActor);
}

void ABaseEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent(OtherActor);
	if (!ASC) return;
	if (EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) DoApplyGameplayEffect(OtherActor);
	if (ActiveGameplayEffectHandles.Num() > 0 && EffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ASC->RemoveActiveGameplayEffect(*ActiveGameplayEffectHandles.Find(ASC), 1);
		ActiveGameplayEffectHandles.Remove(ASC);
	}
}

void ABaseEffectActor::DoApplyGameplayEffect(AActor* OtherActor)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent(OtherActor);
	if (!ASC) return;
	FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle Spec = ASC->MakeOutgoingSpec(GameplayEffectClass, EffectLevel, ContextHandle);
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = ASC->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());

	// What if the effect is infinite? And what if there are multiple game characters that overlap with this actor?
	// We need to store the handle of the active gameplay effect to remove it later.
	// Otherwise, only the last character that overlaps with this actor will have the effect removed.
	// I guess :D
	if (Spec.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite && EffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		ActiveGameplayEffectHandles.Add(ASC, ActiveGameplayEffectHandle);
}

UAbilitySystemComponent* ABaseEffectActor::GetAbilitySystemComponent(AActor* TheActor)
{
	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TheActor);
	return AbilitySystemComponent;
}


