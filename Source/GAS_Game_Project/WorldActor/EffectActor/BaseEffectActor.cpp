// Cu Nhat Hoang


#include "BaseEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilityBlueprint.h"
#include "Components/SphereComponent.h"
#include "GAS_Game_Project/Character/BaseGameCharacter.h"
#include "GAS_Game_Project/Character/Player/PlayerCharacter.h"
#include "GAS_Game_Project/Character/Player/PlayerState/MyPlayerState.h"
#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"

ABaseEffectActor::ABaseEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	SetRootComponent(Mesh);
	SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("Sphere component"));
	SphereComponent->SetupAttachment(GetRootComponent());
}

void ABaseEffectActor::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);
}

void ABaseEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	UAbilitySystemComponent* AbilitySystemComponent =
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (AbilitySystemComponent)
	{
		FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
		ContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle Spec = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, EffectLevel, ContextHandle);
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
	}
}

void ABaseEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}


