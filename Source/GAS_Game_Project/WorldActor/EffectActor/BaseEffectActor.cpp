// Cu Nhat Hoang


#include "BaseEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilityBlueprint.h"
#include "Components/SphereComponent.h"
#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"

ABaseEffectActor::ABaseEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

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
		FGameplayEffectContext* Context;
		const FGameplayEffectContextHandle ContextHandle = FGameplayEffectContextHandle(Context);
		const FGameplayEffectSpecHandle GameplayEffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, EffectLevel, ContextHandle);
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());

	}
}

void ABaseEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}


