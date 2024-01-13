// Cu Nhat Hoang


#include "BasePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GAS_Game_Project/Character/Player/PlayerCharacter.h"

ABasePlayerController::ABasePlayerController()
{
	bReplicates = true;
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputMappingContext, TEXT("DAWG! InputMappingContext is null"));
	if (Subsystem)
		Subsystem->AddMappingContext(InputMappingContext, 0);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(IMoveAction, ETriggerEvent::Triggered, this, &ABasePlayerController::Move);
	}

	SetupInputMode();
}

void ABasePlayerController::SetupInputMode()
{
	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputModeGameAndUI);
}

void ABasePlayerController::Move(const FInputActionValue& Value)
{
	FVector2d ScaleValue = Value.Get<FVector2d>();
	const FRotator rot = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(rot).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(rot).GetUnitAxis(EAxis::Y);
	GetPlayerCharacter()->AddMovementInput(ForwardDirection, ScaleValue.Y);
	GetPlayerCharacter()->AddMovementInput(RightDirection, ScaleValue.X);
}

APlayerCharacter* ABasePlayerController::GetPlayerCharacter()
{
	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	}
	return PlayerCharacter;
}
