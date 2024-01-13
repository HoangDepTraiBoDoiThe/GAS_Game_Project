// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

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
	void SetupInputMode();
	virtual void SetupInputComponent() override;
	void Move(const FInputActionValue& Value);
	APlayerCharacter* GetPlayerCharacter();

	TObjectPtr<APlayerCharacter> PlayerCharacter;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> IMoveAction;
};
