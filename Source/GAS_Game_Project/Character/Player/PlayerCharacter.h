// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GAS_Game_Project/Character/BaseGameCharacter.h"
#include "PlayerCharacter.generated.h"

class AMyPlayerState;
class ABasePlayerController;
class AMyHUD;
/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API APlayerCharacter : public ABaseGameCharacter
{
	GENERATED_BODY()

public:

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_Controller() override;

	void InitAbilityActorInfo();
	bool IsHudValid();
	bool IsPlayerControllerValid();
	bool IsPlayerStateValid();

	UPROPERTY()
	TObjectPtr<AMyHUD> HUD;

	UPROPERTY()
	TObjectPtr<ABasePlayerController> PlayerController;

	UPROPERTY()
	TObjectPtr<AMyPlayerState> MyPlayerState;
	
};
