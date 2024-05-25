// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

class UXPDataAsset;
class UAttributeInfo;
class UBaseAttributeSet;
class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnIntPropertyChangeSignature, const int32)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnIntPropertyChangeTwoParamSignature, const int32, const int32 OldXP)

UCLASS()
class GAS_GAME_PROJECT_API AMyPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMyPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	FORCEINLINE int32 GetCharacterLevel() const {return CharacterLevel;}
	FORCEINLINE int32 GetCharacterXP() const {return CharacterXP;}
	FORCEINLINE int32 GetAbilityPoint() const {return AbilityPoint;}
	FORCEINLINE UBaseAttributeSet* GetAttributeSet() const {return AttributeSet;}
	FORCEINLINE UAttributeInfo* GetAttributeInfo () const {return AttributeInfo;}
	UXPDataAsset* GeXPDataAsset() const;
	void BroadCastCharacterExperience();

#pragma region //Setter for server only
	void SetCharacterLevel(const int32 NewLevel);
	void SetCharacterXP(const int32 NewXP);
	void CharacterXPIncreasement(const int32 AdditionXP);
	void CharacterLevelChange(const int32 AdditionLevel);
	void LevelUpIfPossible(int32 IncomingXP);
	// Either increase or decrease it.
	void ChangeAttributePoint(const int32 AdditionAbilityPoint);

#pragma endregion
		
	FOnIntPropertyChangeTwoParamSignature OnXPChangeDelegate;
	FOnIntPropertyChangeSignature OnCharacterLevelChangeDelegate;
	FOnIntPropertyChangeSignature OnAttributePointChangeDelegate;
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION()
	void RepNotify_CharacterXP(int32 OldXPValue);
	UFUNCTION()
	void RepNotify_CharacterLevel(int32 OldCharacterLevelValue);
	UFUNCTION()
	void RepNotify_AbilityPoint(int32 OldAbilityPointValue);
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UBaseAttributeSet> AttributeSet;
	
	UPROPERTY(EditAnywhere)
	UAttributeInfo* AttributeInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing=RepNotify_CharacterLevel)
	int32 CharacterLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing=RepNotify_CharacterXP)
	int32 CharacterXP = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing=RepNotify_AbilityPoint)
	int32 AbilityPoint = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UXPDataAsset> XPDataAsset;

	
};

