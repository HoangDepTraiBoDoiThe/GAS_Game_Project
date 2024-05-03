// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class UWidgetComponent;
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

	UFUNCTION(Client, Unreliable)
	void Client_ShowDamageText(float DamageTextValue, AActor* Target, bool bCritHit, bool bBlockedHit);

	
protected:
	virtual void BeginPlay() override;
	void AutoRun();
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	void SetupInputMode();
	void Move(const FInputActionValue& Value);
	void CursorTrace();

	APlayerCharacter* GetPlayerCharacter();
	void OnInputPress(FGameplayTag InputTag);
	void ActivateHoldingRun();
	void OnInputHeld(FGameplayTag InputTag);
	void ActivateAutoRun();
	void OnInputRelease(FGameplayTag InputTag);
	FORCEINLINE void OnLeftShiftPressed() {bLeftShiftPressing = true;}
	FORCEINLINE void OnLeftShiftReleased() {bLeftShiftPressing = false;}
	FHitResult TakeHitResultUnderCursor(ECollisionChannel Channel, bool bTraceComplex) const;

	UMyAbilitySystemComponent* GetASC();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidgetComponent> DamageWidgetComponentClass;
	
	bool bLeftShiftPressing = false;
	USplineComponent* SplineComponent;

	UMyAbilitySystemComponent* ASC;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputDataAsset> InputConfig;
	
	TObjectPtr<APlayerCharacter> PlayerCharacter;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ILeftShift;
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
	FVector CacheDestination = FVector::ZeroVector;
};
