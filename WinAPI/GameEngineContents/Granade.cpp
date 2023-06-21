#include "Granade.h"
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

Granade::Granade()
{
}

Granade::~Granade()
{
}

void Granade::Start() 
{
	GranadeRenderer = CreateRenderer(RenderOrder::WeaponSFX);

	if (false == ResourcesManager::GetInst().IsLoadTexture("LGranade.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("LGranade.bmp"), 5, 4);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("RGranade.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("RGranade.bmp"), 5, 4);
	}

	GranadeRenderer->CreateAnimation("RGranadeFire", "RGranade.bmp", 0, 15, 0.5f, false);
	GranadeRenderer->CreateAnimation("RGranadeBound", "LGranade.bmp", 14, 7, 0.5f, false);

	GranadeRenderer->CreateAnimation("LGranadeFire", "LGranade.bmp", 0, 15, 0.5f, false);
	GranadeRenderer->CreateAnimation("LGranadeBound", "RGranade.bmp", 14, 7, 0.5f, false);
}
void Granade::Update(float _Delta)
{
}



//Gravity(_Delta);
//
//{
//	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
//
//	if (Color != RGB(255, 255, 255))
//	{
//		ChangeLowerState(PlayerLowerState::Idle);
//		return;
//	}
//}