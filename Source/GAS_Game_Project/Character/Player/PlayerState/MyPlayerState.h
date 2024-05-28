// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

class APlayerCharacter;
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
	FORCEINLINE int32 GetSpellPoint() const {return SpellPoint;}
	FORCEINLINE UBaseAttributeSet* GetAttributeSet() const {return AttributeSet;}
	FORCEINLINE UAttributeInfo* GetAttributeInfo () const {return AttributeInfo;}
	UXPDataAsset* GeXPDataAsset() const;
	APlayerCharacter* GetPlayerCharacter();
	void BroadCastCharacterExperience();
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_SpendAttributePoint(const FGameplayTag AttributeTag);
	UFUNCTION(Server, Reliable)
	void Server_UpgradeAbility(const FGameplayTag AbilityTag, const int32 PointToUpgrade);
	auto ChangeSpellPoint(const int32 AdditionSpellPoint) -> void;
	
#pragma region //Setter for server only
	void SetCharacterLevel(const int32 NewLevel);
	void RewardPlayer(int32 LevelIncoming);
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
	FOnIntPropertyChangeSignature OnSpellPointChangeDelegate;
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION()
	void RepNotify_CharacterXP(int32 OldXPValue);
	UFUNCTION()
	void RepNotify_CharacterLevel(int32 OldCharacterLevelValue);
	UFUNCTION()
	void RepNotify_AbilityPoint(int32 OldAbilityPointValue);
	UFUNCTION()
	void RepNotify_SpellPoint(int32 OldSpellPointValue);
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UBaseAttributeSet> AttributeSet;

	TObjectPtr<APlayerCharacter> PlayerCharacter;
	
	UPROPERTY(EditAnywhere)
	UAttributeInfo* AttributeInfo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing=RepNotify_CharacterLevel)
	int32 CharacterLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing=RepNotify_CharacterXP)
	int32 CharacterXP = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing=RepNotify_AbilityPoint)
	int32 AbilityPoint = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing=RepNotify_SpellPoint)
	int32 SpellPoint = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UXPDataAsset> XPDataAsset;

	
};

