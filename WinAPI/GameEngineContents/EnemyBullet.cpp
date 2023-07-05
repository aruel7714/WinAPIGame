#include "EnemyBullet.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "ContentsEnum.h"
#include "Player.h"
#include "GlobalValue.h"

EnemyBullet::EnemyBullet()
{
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Start()
{
	Renderer = CreateRenderer(RenderOrder::EnemyAttack);

	if (false == ResourcesManager::GetInst().IsLoadTexture("EnemyBullet.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("EnemyBullet.bmp"));
	}

	ResourcesManager::GetInst().FindTexture("EnemyBullet.bmp");
	Renderer->SetTexture("EnemyBullet.bmp");

	Renderer->SetRenderScaleToTexture();

	{
		BulletCollision = CreateCollision(CollisionOrder::EnemyBulletCollision);

		BulletCollision->SetCollisionScale({ 15, 15 });
		BulletCollision->SetCollisionType(CollisionType::Rect);
	}
}

void EnemyBullet::Update(float _Delta)
{
	AddPos(Dir * _Delta * Speed);

	std::vector<GameEngineCollision*> _Collision;
	if (true == BulletCollision->Collision(CollisionOrder::PlayerCollision, _Collision
		, CollisionType::Rect
		, CollisionType::Rect
	))
	{
		for (size_t i = 0; i < _Collision.size(); i++)
		{
			GameEngineCollision* Collision = _Collision[i];

			GameEngineActor* Actor = Collision->GetActor();

			
		}
		Player::GetMainPlayer()->ChangeLowerState(PlayerLowerState::RangeDeathJump);
		Renderer->Off();
		BulletCollision->Off();
	}

	if (GetLevel()->GetMainCamera()->GetPos().Y > Renderer->GetActor()->GetPos().Y ||
		GetLevel()->GetMainCamera()->GetPos().X + GlobalValue::WinScale.X < Renderer->GetActor()->GetPos().X ||
		GetLevel()->GetMainCamera()->GetPos().X > Renderer->GetActor()->GetPos().X)
	{
		Renderer->Off();
		BulletCollision->Off();
	}
}