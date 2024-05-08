// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GAS_Game_Project/Character/BaseGameCharacter.h"
#include "GAS_Game_Project/Interface/InteractableInterface.h"
#include "GAS_Game_Project/UserInterface/Controller/OverlayWidgetController.h"
#include "EnemyCharacter.generated.h"

class AMyAIController;
class UBehaviorTree;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API AEnemyCharacter : public ABaseGameCharacter, public IInteractableInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void Die() override;

	virtual void SetCurTarget_Implementation(AActor* Actor) override;
	virtual AActor* GetCurTarget_Implementation() override;
	
protected:
	virtual void Multicast_Death_Implementation() override;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> HitPointBar;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(BlueprintAssignable)
	FOnGameplayAttributeValuesSignature OnAttributeValuesSignature;

	UPROPERTY(EditAnywhere)
	float InitialWalkSpeed = 420.f;

	UPROPERTY(BlueprintReadOnly)
	AActor* CurTarget;
	
	void BindBroadCastToWidgetOnAttChange() const;
	void InitBroadCastVitalAttValue() const;
	void OnEventGameplayTagChange(const FGameplayTag, int32);

	virtual void PossessedBy(AController* NewController) override;
};
