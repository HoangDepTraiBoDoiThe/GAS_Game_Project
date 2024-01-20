// Cu Nhat Hoang


#include "MyAbilitySystemComponent.h"

#include "GAS_Game_Project/UserInterface/Controller/OverlayWidgetController.h"

void UMyAbilitySystemComponent::InitOwnerAndAvatarActor(AActor* NewOwnerActor, AActor* NewAvatarActor)
{
	SetOwnerActor(NewOwnerActor);
	SetAvatarActor(NewAvatarActor);
}

void UMyAbilitySystemComponent::BindCallBackToDependencies()
{
	TArray<FGameplayAttribute> AllAttributes;
	GetAllAttributes(AllAttributes);

	for (const FGameplayAttribute& Attribute : AllAttributes)
	{
		GetGameplayAttributeValueChangeDelegate(Attribute).AddLambda(
			[this, Attribute] (const FOnAttributeChangeData& NewAttributeData)
			{
				OnNewAttributeValueChangeToControllerDelegate.Broadcast(NewAttributeData);
			});
	}
}
