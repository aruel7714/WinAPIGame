#include "Bullet.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include "ContentsEnum.h"


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
	ResourcesManager::GetInst().FindTexture("PistolBullet.bmp");
	Renderer->SetTexture("PistolBullet.bmp");
	Renderer->SetRenderScaleToTexture();
}

void Bullet::Update(float _Delta)
{
	AddPos(Dir * _Delta * Speed);

	if (2.0f < GetLiveTime())
	{
		if (nullptr != Renderer)
		{
			Renderer->Death();
			Renderer = nullptr;
		}
	}
}
