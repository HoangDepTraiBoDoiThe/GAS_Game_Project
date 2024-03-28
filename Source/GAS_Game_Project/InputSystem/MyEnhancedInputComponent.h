// Cu Nhat Hoang

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GAS_Game_Project/Data/InputDataAsset.h"
#include "MyEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_PROJECT_API UMyEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityInputActions(const UInputDataAsset* InputDataAsset, UserClass* Object, PressedFuncType PressedFunc,
	                             ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UMyEnhancedInputComponent::BindAbilityInputActions(const UInputDataAsset* InputDataAsset, UserClass* Object,
                                                        PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc,
                                                        HeldFuncType HeldFunc)
{
	checkf(InputDataAsset, TEXT("InputDataAsset is null"));
	for (const auto& [InputAction, InputTag] : InputDataAsset->AbilityInputActions)
	{
		if (!InputAction || !InputTag.IsValid()) continue;
		if (PressedFunc) BindAction(InputAction, ETriggerEvent::Started, Object, InputTag);
		if (ReleasedFunc) BindAction(InputAction, ETriggerEvent::Completed, Object, InputTag);
		if (HeldFunc) BindAction(InputAction, ETriggerEvent::Triggered, Object, InputTag);
	}
}
