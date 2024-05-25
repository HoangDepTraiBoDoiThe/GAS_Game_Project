// Cu Nhat Hoang


#include "EnemyCharacter.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "Controller/MyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS_Game_Project/GAS/MyAbilitySystemComponent.h"
#include "GAS_Game_Project/GAS/AttributeSet/BaseAttributeSet.h"
#include "GAS_Game_Project/GAS/GamplayTag/MyGameplayTags.h"
#include "GAS_Game_Project/Global/MyBlueprintFunctionLibrary.h"
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
	GetCharacterMovement()->MaxWalkSpeed = InitialWalkSpeed;
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		UMyBlueprintFunctionLibrary::InitAttributeValue(this, this);
		UMyBlueprintFunctionLibrary::AddAbilities(GetAbilitySystemComponent(), this);
	}

	Cast<UBaseUserWidget>(HitPointBar->GetWidget())->SetWidgetController(this);
	AbilitySystemComponent->BindGameplayAttrValChangeCallback();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	BindBroadCastToWidgetOnAttChange();
	InitBroadCastVitalAttValue();

	AbilitySystemComponent->RegisterGameplayTagEvent(MyGameplayTags::Get().Effects_OnHitReact, EGameplayTagEventType::NewOrRemoved)
		.AddUObject(this, &AEnemyCharacter::OnEventGameplayTagChange);
}

void AEnemyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
void AEnemyCharacter::OnEventGameplayTagChange(const FGameplayTag Tag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : InitialWalkSpeed;
	if(GetAIController()->GetBlackboardComponent())
		GetAIController()->GetBlackboardComponent()->SetValueAsBool(FName("IsHitReacting"), bHitReacting);
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	SetupAIBehavior();
}

void AEnemyCharacter::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
}

void AEnemyCharacter::SetupAIBehavior()
{
	GetAIController()->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->GetBlackboardAsset());
	GetAIController()->RunBehaviorTree(BehaviorTree);
	GetAIController()->GetBlackboardComponent()->SetValueAsBool(FName("IsRangeClass"), GetCharacterClass() != ECharacterClass::ECC_Warrior);
}

void AEnemyCharacter::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
}

UAnimMontage* AEnemyCharacter::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void AEnemyCharacter::SetCurTarget_Implementation(AActor* Actor)
{
	CurTarget = Actor;
}

AActor* AEnemyCharacter::GetCurTarget_Implementation()
{
	return CurTarget;
}

AMyAIController* AEnemyCharacter::GetAIController()
{
	if (!AIController) AIController = Cast<AMyAIController>(GetController());
	return AIController;
}

void AEnemyCharacter::Die()
{
	Cast<AMyAIController>(GetController())->GetBlackboardComponent()->SetValueAsBool(FName("IsDeath"), true);
	Cast<AMyAIController>(GetController())->GetBehaviorTreeComponent()->StopLogic(FString("Actor is death"));
	Super::Die();
}

void AEnemyCharacter::BindBroadCastToWidgetOnAttChange() const
{
	AbilitySystemComponent->OnNewAttributeValueChangeBroadcastToControllerDelegate.AddLambda(
		[this](const FOnAttributeChangeData& NewAttributeData)
		{
			OnAttributeValuesSignature.Broadcast(NewAttributeData.NewValue, NewAttributeData.Attribute);
		}
	);
}

void AEnemyCharacter::InitBroadCastVitalAttValue() const
{
	OnAttributeValuesSignature.Broadcast(UBaseAttributeSet::GetHitPointAttribute().GetNumericValue(AttributeSet),
								 UBaseAttributeSet::GetHitPointAttribute());
	OnAttributeValuesSignature.Broadcast(UBaseAttributeSet::GetMaxHitPointAttribute().GetNumericValue(AttributeSet),
										 UBaseAttributeSet::GetMaxHitPointAttribute());
}
