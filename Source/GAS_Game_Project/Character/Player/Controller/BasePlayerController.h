// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

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

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputDataAsset> InputConfig;
	
	TObjectPtr<APlayerCharacter> PlayerCharacter;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IMoveAction;

	IInteractableInterface* CurrentUnderMouseTarget = nullptr;
	IInteractableInterface* PrevUnderMouseTarget;
};
