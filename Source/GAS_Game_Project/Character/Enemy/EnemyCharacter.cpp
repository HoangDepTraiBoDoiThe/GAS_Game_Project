// Cu Nhat Hoang


#include "EnemyCharacter.h"

#include "Components/WidgetComponent.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"
#include "GAS_Game_Project/UserInterface/UserWidget/BaseUserWidget.h"


AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(FName("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(FName("Attribute Set"));
	HitPointBar = CreateDefaultSubobject<UWidgetComponent>("Hit point bar");
	HitPointBar->SetupAttachment(GetRootComponent());
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	Cast<UBaseUserWidget>(HitPointBar->GetWidget())->SetWidgetController(this);
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->BindGameplayAttrValChangeCallback();
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AbilitySystemComponent->OnNewAttributeValueChangeBroadcastToControllerDelegate.AddLambda(
			[this] (const FOnAttributeChangeData& NewAttributeData)
			{
				OnAttributeValuesSignature.Broadcast(NewAttributeData.NewValue, NewAttributeData.Attribute);
			}
		);
		InitAttributeValue();
		OnAttributeValuesSignature.Broadcast(UBaseAttributeSet::GetHitPointAttribute().GetNumericValue(AttributeSet), UBaseAttributeSet::GetHitPointAttribute());
		OnAttributeValuesSignature.Broadcast(UBaseAttributeSet::GetMaxHitPointAttribute().GetNumericValue(AttributeSet), UBaseAttributeSet::GetMaxHitPointAttribute());
	}
}

void AEnemyCharacter::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
}

void AEnemyCharacter::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
}
