// Cu Nhat Hoang


#include "BaseProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraEmitter.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GAS_Game_Project/GAS_Game_Project.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"

ABaseProjectile::ABaseProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(FName("Sphere component"));
	SetRootComponent(SphereComponent);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	
	ProjectileMovementComponent->InitialSpeed = 1300.f;
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_PROJECTILE, ECR_Block);

}

void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<APawn>(OtherActor) == GetInstigator()) return;
	bIsOverlappedOnClient = true;
	if (DestroyFX) UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DestroyFX, GetActorLocation());
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			checkf(ProjectileEffectSpecHandle.IsValid(), TEXT("My Message | ABaseProjectile | CRITICAL | Projectile's EffectSpecHandle is not constructed"))
			TargetASC->ApplyGameplayEffectSpecToSelf(*ProjectileEffectSpecHandle.Data.Get());
		}
		Destroy();
	}
}

void ABaseProjectile::Destroyed()
{
	if (!bIsOverlappedOnClient)
	{
		if (DestroyFX) UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DestroyFX, GetActorLocation());
	}
	Super::Destroyed();
}

