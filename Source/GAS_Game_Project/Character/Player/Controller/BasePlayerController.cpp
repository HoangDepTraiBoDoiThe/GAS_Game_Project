// Cu Nhat Hoang


#include "BasePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SplineComponent.h"
#include "GAS_Game_Project/Character/Player/PlayerCharacter.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/GamplayTag/MyGameplayTags.h"
#include "GAS_Game_Project/InputSystem/MyEnhancedInputComponent.h"
#include "GAS_Game_Project/Interface/InteractableInterface.h"

ABasePlayerController::ABasePlayerController()
{
	bReplicates = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(FName("Spline component"));
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetupInputMode();
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());
	checkf(InputMappingContext, TEXT("DAWG! InputMappingContext is null"));
	if (Subsystem)
		Subsystem->AddMappingContext(InputMappingContext, 0);

	UMyEnhancedInputComponent* MyEnhancedInputComponent = Cast<UMyEnhancedInputComponent>(InputComponent);
	check(MyEnhancedInputComponent)
	MyEnhancedInputComponent->BindAction(IMoveAction, ETriggerEvent::Triggered, this, &ABasePlayerController::Move);
	MyEnhancedInputComponent->BindAbilityInputActions(InputConfig, this, &ThisClass::OnInputPress, &ThisClass::OnInputRelease, &ThisClass::OnInputHeld);
}

void ABasePlayerController::OnInputPress(FGameplayTag InputTag)
{
	if (MyGameplayTags::Get().Control_LMB.MatchesTagExact(InputTag))
	{
		bTargeting = CurrentUnderMouseTarget == nullptr;
		bShouldAutoRunning = false;
	}
}

void ABasePlayerController::OnInputHeld(FGameplayTag InputTag)
{
	GetASC()->AbilityInputTagHeld(InputTag);
	if (CurrentUnderMouseTarget)
		GetASC()->AbilityInputTagHeld(InputTag);
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();

		FHitResult HitResult;
		GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

		APawn* ControlledPawn = GetPawn();
		if (ControlledPawn && HitResult.bBlockingHit)
		{
			CacheDirection = HitResult.ImpactPoint;
			const FVector WorldDirection = (CacheDirection - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

void ABasePlayerController::OnInputRelease(FGameplayTag InputTag)
{
	GetASC()->AbilityInputTagReleased(InputTag);
}

UMyAbilitySystemComponent* ABasePlayerController::GetASC()
{
	if (!ASC) ASC = CastChecked<UMyAbilitySystemComponent>(GetPlayerCharacter()->GetAbilitySystemComponent());
	return ASC;
}

void ABasePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CursorTrace();
}

void ABasePlayerController::SetupInputMode()
{
	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	bShowMouseCursor = true;
	SetInputMode(InputModeGameAndUI);
}

void ABasePlayerController::Move(const FInputActionValue& Value)
{
	const FVector2d ScaleValue = Value.Get<FVector2d>();
	const FRotator rot = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(rot).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(rot).GetUnitAxis(EAxis::Y);
	GetPlayerCharacter()->AddMovementInput(ForwardDirection, ScaleValue.Y);
	GetPlayerCharacter()->AddMovementInput(RightDirection, ScaleValue.X);
}

void ABasePlayerController::CursorTrace()
{
	FHitResult CursorHitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHitResult);

	PrevUnderMouseTarget = CurrentUnderMouseTarget;
	CurrentUnderMouseTarget = Cast<IInteractableInterface>(CursorHitResult.GetActor());

	if (CurrentUnderMouseTarget != PrevUnderMouseTarget)
	{
		if (PrevUnderMouseTarget) PrevUnderMouseTarget->UnHighlightActor();
		if (CurrentUnderMouseTarget) CurrentUnderMouseTarget->HighlightActor();
	}
}

APlayerCharacter* ABasePlayerController::GetPlayerCharacter()
{
	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	}
	return PlayerCharacter;
}
