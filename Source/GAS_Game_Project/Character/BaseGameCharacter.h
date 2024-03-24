// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
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
	virtual float GetCharacterLevel() override;
	FORCEINLINE UBaseAttributeSet* GetAttributeSet() const {return AttributeSet;}

protected:
	virtual void BeginPlay() override;
	virtual void InitAttributeValue();
	void Cus_ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClassToApply) const;
	void ActiveAbilities();

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UGameplayAbility>> AbilitiesToActive;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> DefaultVitalAttributesClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributesClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributesClass;

	UPROPERTY(EditAnywhere)
	float CharacterLevel = 1;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMyAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBaseAttributeSet> AttributeSet;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> Weapon;

private:

	
};
