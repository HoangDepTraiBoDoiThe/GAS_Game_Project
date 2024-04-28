// Cu Nhat Hoang


#include "BasePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Components/CapsuleComponent.h"
#include "Components/SplineComponent.h"
#include "GAS_Game_Project/Character/Player/PlayerCharacter.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/GamplayTag/MyGameplayTags.h"
#include "GAS_Game_Project/InputSystem/MyEnhancedInputComponent.h"
#include "GAS_Game_Project/Interface/DamageTextWidgetComponent.h"
#include "GAS_Game_Project/Interface/InteractableInterface.h"

class UDamageTextWidgetComponent;

ABasePlayerController::ABasePlayerController()
{
	bReplicates = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(FName("Spline component"));
}

void ABasePlayerController::Client_ShowDamageText_Implementation(float DamageTextValue, AActor* Target)
{
	UDamageTextWidgetComponent* DamageTextWidgetComponent = NewObject<UDamageTextWidgetComponent>(Target, DamageWidgetComponentClass);
	DamageTextWidgetComponent->RegisterComponent();
	DamageTextWidgetComponent->AttachToComponent(Cast<ABaseGameCharacter>(Target)->GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	DamageTextWidgetComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetupInputMode();
}

void ABasePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CursorTrace();
	AutoRun();
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
	MyEnhancedInputComponent->BindAction(ILeftShift, ETriggerEvent::Started, this, &ABasePlayerController::OnLeftShiftPressed);
	MyEnhancedInputComponent->BindAction(ILeftShift, ETriggerEvent::Completed, this, &ABasePlayerController::OnLeftShiftReleased);
}

void ABasePlayerController::OnInputPress(FGameplayTag InputTag)
{
	if (MyGameplayTags::Get().Control_RMB.MatchesTagExact(InputTag))
	{
		bTargeting = CurrentUnderMouseTarget != nullptr;
		bShouldAutoRunning = false;
	}
}

void ABasePlayerController::OnInputHeld(FGameplayTag InputTag)
{
	if (!MyGameplayTags::Get().Control_RMB.MatchesTagExact(InputTag)) GetASC()->AbilityInputTagHeld(InputTag);
	else if (bTargeting || bLeftShiftPressing) GetASC()->AbilityInputTagHeld(InputTag);
	else ActivateHoldingRun();
}

void ABasePlayerController::OnInputRelease(FGameplayTag InputTag)
{
	if (!MyGameplayTags::Get().Control_RMB.MatchesTagExact(InputTag)) GetASC()->AbilityInputTagReleased(InputTag);
	else if (FollowTime <= ShortPressThreshold && !bLeftShiftPressing && !bTargeting) ActivateAutoRun();
	FollowTime = 0.f;
	bTargeting = false;
}

UMyAbilitySystemComponent* ABasePlayerController::GetASC()
{
	if (!ASC) ASC = CastChecked<UMyAbilitySystemComponent>(GetPlayerCharacter()->GetAbilitySystemComponent());
	return ASC;
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

void ABasePlayerController::ActivateHoldingRun()
{
	FollowTime += GetWorld()->GetDeltaSeconds();
	const FHitResult HitResult = TakeHitResultUnderCursor(ECC_Visibility, false);

	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn && HitResult.bBlockingHit)
	{
		CacheDestination = HitResult.ImpactPoint;
		const FVector WorldDirection = (CacheDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection);
	}
}

void ABasePlayerController::ActivateAutoRun()
{
	const FHitResult HitResult = TakeHitResultUnderCursor(ECC_Visibility, false);
	const APawn* ControlledPawn = GetPawn();
	if (ControlledPawn && HitResult.bBlockingHit)
	{
		if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(GetWorld(), ControlledPawn->GetActorLocation(), CacheDestination))
		{
			if (NavPath->PathPoints.Num() == 0) return; 
			CacheDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
			bShouldAutoRunning = true;
			SplineComponent->ClearSplinePoints();
			SplineComponent->SetSplinePoints(NavPath->PathPoints, ESplineCoordinateSpace::World);
		}
	}
}

void ABasePlayerController::AutoRun()
{
	if (!bShouldAutoRunning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = SplineComponent->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = SplineComponent->FindDirectionClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);
		const float DistanceToDestination = FMath::Abs((CacheDestination - LocationOnSpline).Length());
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bShouldAutoRunning = false;
		}
	}
}

void ABasePlayerController::CursorTrace()
{
	const FHitResult CursorHitResult = TakeHitResultUnderCursor(ECC_Visibility, false);

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

FHitResult ABasePlayerController::TakeHitResultUnderCursor(ECollisionChannel Channel, bool bTraceComplex) const
{
	FHitResult HitResult;
	GetHitResultUnderCursor(Channel, bTraceComplex, HitResult);
	return HitResult;
}
