// Cu Nhat Hoang


#include "BaseGameCharacter.h"

// Sets default values
ABaseGameCharacter::ABaseGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

