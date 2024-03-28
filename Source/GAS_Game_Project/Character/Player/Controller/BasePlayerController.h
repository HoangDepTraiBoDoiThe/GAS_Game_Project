// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class USplineComponent;
class UMyAbilitySystemComponent;
class UInputDataAsset;
class IInteractableInterface;
class APlayerCharacter;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	void SetupInputMode();
	void Move(const FInputActionValue& Value);
	void CursorTrace();

	APlayerCharacter* GetPlayerCharacter();
	void OnInputPress(FGameplayTag InputTag);
	void OnInputHeld(FGameplayTag InputTag);
	void OnInputRelease(FGameplayTag InputTag);

	UMyAbilitySystemComponent* GetASC();

	USplineComponent* SplineComponent;

	UMyAbilitySystemComponent* ASC;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputDataAsset> InputConfig;
	
	TObjectPtr<APlayerCharacter> PlayerCharacter;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IMoveAction;

	IInteractableInterface* CurrentUnderMouseTarget = nullptr;
	IInteractableInterface* PrevUnderMouseTarget;

	UPROPERTY(EditAnywhere)
	float AutoRunAcceptanceRadius = 50.f;
	float ShortPressThreshold = 0.5f;
	float FollowTime = 0.f;
	bool bShouldAutoRunning = false;
	bool bTargeting = false;
	FVector CacheDirection = FVector::ZeroVector;
};
