#include "DebugCollision.h"
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"

DebugCollision::DebugCollision()
{
}

DebugCollision::~DebugCollision()
{
}

void DebugCollision::Start()
{
	{
		FocusCollision = CreateCollision(CollisionOrder::DebugCollision);

		FocusCollision->SetCollisionScale({ 20, 1000 });
		FocusCollision->SetCollisionType(CollisionType::Rect);
		
	}
}