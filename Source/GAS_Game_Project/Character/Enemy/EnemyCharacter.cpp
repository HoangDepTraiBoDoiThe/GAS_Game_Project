// Cu Nhat Hoang


#include "EnemyCharacter.h"

void AEnemyCharacter::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
}

void AEnemyCharacter::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
}
