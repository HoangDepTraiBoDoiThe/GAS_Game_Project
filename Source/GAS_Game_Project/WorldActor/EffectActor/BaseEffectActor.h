// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "BaseEffectActor.generated.h"

class UMyAbilitySystemComponent;
struct FActiveGameplayEffectHandle;
class UGameplayEffect;
class USphereComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	ApplyOnBeginOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};
UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	RemoveOnBeginOverlap,
	RemoveOnEndOverlap,
	DoNotRemove
};
UCLASS()
class GAS_GAME_PROJECT_API ABaseEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseEffectActor();

protected:
	virtual void BeginPlay() override;
	void DoApplyGameplayEffect(AActor* OtherActor);
	UFUNCTION(BlueprintCallable)
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	static UAbilitySystemComponent* GetAbilitySystemComponent(AActor* TheActor);

	UPROPERTY(EditAnywhere, Category=Policy)
	EEffectApplicationPolicy EffectApplicationPolicy = EEffectApplicationPolicy::ApplyOnBeginOverlap;
	UPROPERTY(EditAnywhere, Category=Policy)
	EEffectRemovalPolicy EffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	TMap<UAbilitySystemComponent*, FActiveGameplayEffectHandle> ActiveGameplayEffectHandles;
	
	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(EditAnywhere, Category = "Gameplay ability system")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;
	UPROPERTY(EditAnywhere, Category = "Gameplay ability system")
	int32 EffectLevel = 1;
};
