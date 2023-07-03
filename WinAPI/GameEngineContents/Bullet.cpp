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

	if (false == ResourcesManager::GetInst().IsLoadTexture("HeavyMachineGunRight.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\SFX\\HeavyMachineGunSFX\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HeavyMachineGunRight.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("HeavyMachineGunLeft.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\SFX\\HeavyMachineGunSFX\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HeavyMachineGunLeft.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("HeavyMachineGunRightUp30.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\SFX\\HeavyMachineGunSFX\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HeavyMachineGunRightUp30.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("HeavyMachineGunRightUp45.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\SFX\\HeavyMachineGunSFX\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HeavyMachineGunRightUp45.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("HeavyMachineGunRightUp60.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\SFX\\HeavyMachineGunSFX\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HeavyMachineGunRightUp60.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("HeavyMachineGunRightUp90.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\SFX\\HeavyMachineGunSFX\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HeavyMachineGunRightUp90.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("HeavyMachineGunLeftUp90.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\SFX\\HeavyMachineGunSFX\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HeavyMachineGunLeftUp90.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("HeavyMachineGunRightDown90.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\SFX\\HeavyMachineGunSFX\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HeavyMachineGunRightDown90.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("HeavyMachineGunLeftDown90.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\SFX\\HeavyMachineGunSFX\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HeavyMachineGunLeftDown90.bmp"));
	}

	Renderer->CreateAnimation("BulletExplosion", "WeaponExplosion.bmp", 0, 9, 0.01f, false);
	
	if (Player::WeaponName == "Pistol_")
	{
		SetPistolDirTexture();
	}
	else if (Player::WeaponName == "Rifle_")
	{
		SetRifleDirTexture();
	}

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

void Bullet::SetPistolDirTexture()
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

void Bullet::SetRifleDirTexture()
{
	if (Player::RifleDir == PlayerRifleBulletDir::Right)
	{
		ResourcesManager::GetInst().FindTexture("HeavyMachineGunRight.bmp");
		Renderer->SetTexture("HeavyMachineGunRight.bmp");
	}
	else if (Player::RifleDir == PlayerRifleBulletDir::Left)
	{
		ResourcesManager::GetInst().FindTexture("HeavyMachineGunLeft.bmp");
		Renderer->SetTexture("HeavyMachineGunLeft.bmp");
	}
	else if (Player::RifleDir == PlayerRifleBulletDir::RightUp30)
	{
		ResourcesManager::GetInst().FindTexture("HeavyMachineGunRightUp30.bmp");
		Renderer->SetTexture("HeavyMachineGunRightUp30.bmp");
	}
	else if (Player::RifleDir == PlayerRifleBulletDir::RightUp45)
	{
		ResourcesManager::GetInst().FindTexture("HeavyMachineGunRightUp45.bmp");
		Renderer->SetTexture("HeavyMachineGunRightUp45.bmp");
	}
	else if (Player::RifleDir == PlayerRifleBulletDir::RightUp60)
	{
		ResourcesManager::GetInst().FindTexture("HeavyMachineGunRightUp60.bmp");
		Renderer->SetTexture("HeavyMachineGunRightUp60.bmp");
	}
	else if (Player::RifleDir == PlayerRifleBulletDir::RightUp90)
	{
		ResourcesManager::GetInst().FindTexture("HeavyMachineGunRightUp90.bmp");
		Renderer->SetTexture("HeavyMachineGunRightUp90.bmp");
	}
	else if (Player::RifleDir == PlayerRifleBulletDir::LeftUp90)
	{
		ResourcesManager::GetInst().FindTexture("HeavyMachineGunLeftUp90.bmp");
		Renderer->SetTexture("HeavyMachineGunLeftUP90.bmp");
	}
	else if (Player::RifleDir == PlayerRifleBulletDir::RightDown90)
	{
		ResourcesManager::GetInst().FindTexture("HeavyMachineGunRightDown90.bmp");
		Renderer->SetTexture("HeavyMachineGunRightUp90.bmp");
	}
	else if (Player::RifleDir == PlayerRifleBulletDir::LeftDown90)
	{
		ResourcesManager::GetInst().FindTexture("HeavyMachineGunLeftDown90.bmp");
		Renderer->SetTexture("HeavyMachineGunLeftUP90.bmp");
	}
}