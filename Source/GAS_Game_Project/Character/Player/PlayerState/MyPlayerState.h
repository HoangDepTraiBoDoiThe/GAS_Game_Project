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
	FORCEINLINE UBaseAttributeSet* GetAttributeSet() const {return AttributeSet;}

	FORCEINLINE UAttributeInfo* GetAttributeInfo () const {return AttributeInfo;}
	UXPDataAsset* GeXPDataAsset() const;

	// For server only
	FORCEINLINE void SetCharacterLevel(const int32 NewLevel);
	// For server only
	FORCEINLINE void SetCharacterXP(const int32 NewXP);
	// For server only
	FORCEINLINE void CharacterXPIncreasement(const int32 AdditionXP);
	// For server only
	FORCEINLINE void CharacterLevelIncreasement();
	// For server only
	void LevelUpIfPossible(int32 XP);
	
	FOnIntPropertyChangeTwoParamSignature OnXPChangeDelegate;
	FOnIntPropertyChangeSignature OnCharacterLevelChangeDelegate;
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION()
	void RepNotify_CharacterXP(int32 OldXPValue);
	UFUNCTION()
	void RepNotify_CharacterLevel(int32 OldCharacterLevelValue);
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UBaseAttributeSet> AttributeSet;
	
	UPROPERTY(EditAnywhere)
	UAttributeInfo* AttributeInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing=RepNotify_CharacterLevel)
	int32 CharacterLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing=RepNotify_CharacterXP)
	int32 CharacterXP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UXPDataAsset> XPDataAsset;

	
};

