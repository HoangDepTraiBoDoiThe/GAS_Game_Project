// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseGameCharacter.generated.h"

UCLASS()
class GAS_GAME_PROJECT_API ABaseGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseGameCharacter();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> Weapon;

private:

	
};
