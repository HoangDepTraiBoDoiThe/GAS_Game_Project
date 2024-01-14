// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEffectActor.generated.h"

class UGameplayEffect;
class USphereComponent;

UCLASS()
class GAS_GAME_PROJECT_API ABaseEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseEffectActor();

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<UStaticMeshComponent> Mesh;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(EditAnywhere, Category = "Gameplay ability system")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;
	UPROPERTY(EditAnywhere, Category = "Gameplay ability system")
	int32 EffectLevel = 1;
};
