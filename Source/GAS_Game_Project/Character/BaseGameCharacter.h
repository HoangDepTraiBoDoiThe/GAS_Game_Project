// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GAS_Game_Project/Data/CharacterClassInfoDataAsset.h"
#include "GAS_Game_Project/Interface/CombatInterface.h"
#include "BaseGameCharacter.generated.h"

class UGameplayEffect;
class UMyAbilitySystemComponent;
class UBaseAttributeSet;
class UAttributeSet;
class UAbilitySystemComponent;
class UGameplayAbility;

UCLASS()
class GAS_GAME_PROJECT_API ABaseGameCharacter : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	ABaseGameCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual int32 GetCharacterLevel() const override;
	FORCEINLINE UBaseAttributeSet* GetAttributeSet() const {return AttributeSet;}
	UFUNCTION(BlueprintCallable)
	virtual FVector WeaponLocation_Implementation() override;
	FORCEINLINE ECharacterClass GetCharacterClass() const {return CharacterClass;}
	void ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClassToApply) const;
	FORCEINLINE ECharacterClass GetCharacterClass() {return CharacterClass;}
	virtual int32 GetMinionMinionCount_Implementation() override;
	virtual int32 GetMinionThreadHold_Implementation() override;
	virtual void IncreaseMinionMinionCount_Implementation(int32 Val) override;
	
protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	virtual void InitAttributeValue();
	virtual AActor* GetWeapon() override;
	virtual void Die() override;
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_Death();

	UPROPERTY(BlueprintReadOnly)
	int32 MinionCount = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MinionThreadHold;
	
	UPROPERTY(EditAnywhere)
	FName WeaponSocketName;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayAbility> EventReceiver;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UBaseGameplayAbility>> StartupAbilities;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> DefaultVitalAttributesClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributesClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributesClass;

	UPROPERTY(EditAnywhere)
	ECharacterClass CharacterClass = ECharacterClass::ECC_None;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMyAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBaseAttributeSet> AttributeSet;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bHitReacting;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> DeathMontage;
	
private:

	
};
