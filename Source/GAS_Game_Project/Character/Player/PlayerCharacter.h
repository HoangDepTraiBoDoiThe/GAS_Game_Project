// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "GAS_Game_Project/Character/BaseGameCharacter.h"
#include "GAS_Game_Project/Interface/PlayerInterface.h"
#include "PlayerState/MyPlayerState.h"
#include "PlayerCharacter.generated.h"

class UAbilityUIInfoDataAsset;
class UAttributeInfo;
class AMyPlayerState;
class ABasePlayerController;
class AMyHUD;
/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API APlayerCharacter : public ABaseGameCharacter, public IPlayerInterface
{
	GENERATED_BODY()

public:
	FORCEINLINE UDataTable* GetUIWidgetDataTable() const { return UIDataTable; }
	FORCEINLINE virtual UAbilityUIInfoDataAsset* GetAbilityUIInfoDataAsset() override {return AbilityUIInfoDataAsset;}
	int32 GetCharacterLevel() const override;
	virtual int32 GetCharacterXP() override;
	virtual int32 GetAttributePoint() override;
	virtual void Die() override;

	AMyPlayerState* GetMyPlayerState();
	
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

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AMyPlayerState> MyPlayerState;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> UIDataTable;
		
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAbilityUIInfoDataAsset> AbilityUIInfoDataAsset;
	
};
