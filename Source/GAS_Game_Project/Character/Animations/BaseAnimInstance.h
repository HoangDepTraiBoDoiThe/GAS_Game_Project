// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

class APlayerCharacter;
/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UBaseAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;	

	ACharacter* GetCharacter();

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACharacter> Character;
	
	UPROPERTY(BlueprintReadOnly)
	float MovementSpeed;
	
};
