#include "Bullet.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include "Player.h"


Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
	Renderer = CreateRenderer(RenderOrder::WeaponSFX);
	if (false == ResourcesManager::GetInst().IsLoadTexture("PistolBullet.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\SFX\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("PistolBullet.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("PistolBulletUpDown.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\SFX\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("PistolBulletUpDown.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("WeaponExplosion.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\SFX\\");
		
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("WeaponExplosion.bmp"), 5, 2);
	}

	Renderer->CreateAnimation("BulletExplosion", "WeaponExplosion.bmp", 0, 9, 0.01f, false);
	
	SetDirTexture();

	/*ResourcesManager::GetInst().FindTexture("PistolBullet.bmp");
	Renderer->SetTexture("PistolBullet.bmp");*/
	Renderer->SetRenderScaleToTexture();


	{
		BulletCollision = CreateCollision(CollisionOrder::BulletCollision);

		BulletCollision->SetCollisionScale({ 15, 15 });
		BulletCollision->SetCollisionType(CollisionType::Rect);

	}
}

void Bullet::Update(float _Delta)
{
	AddPos(Dir * _Delta * Speed);

	

	std::vector<GameEngineCollision*> _Collision;
	if (true == BulletCollision->Collision(CollisionOrder::EnemyCollision, _Collision
		, CollisionType::Rect
		, CollisionType::Rect
	))
	{
		for (size_t i = 0; i < _Collision.size(); i++)
		{
			GameEngineCollision* Collision = _Collision[i];

			GameEngineActor* Actor = Collision->GetActor();

			
		}
		Renderer->Off();
		//BulletCollision->Off();
	}

	if (0.3f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Renderer->Off();
			BulletCollision->Off();
		}
	}
}

void Bullet::SetDirTexture()
{
	if (Player::BulletDir == PlayerBulletDir::Left ||
		Player::BulletDir == PlayerBulletDir::Right)
	{
		ResourcesManager::GetInst().FindTexture("PistolBullet.bmp");
		Renderer->SetTexture("PistolBullet.bmp");
	}
	else if (Player::BulletDir == PlayerBulletDir::LeftUp ||
		Player::BulletDir == PlayerBulletDir::RightUp ||
		Player::BulletDir == PlayerBulletDir::LeftDown ||
		Player::BulletDir == PlayerBulletDir::RightDown)
	{
		ResourcesManager::GetInst().FindTexture("PistolBulletUpDown.bmp");
		Renderer->SetTexture("PistolBulletUpDown.bmp");
	}
}