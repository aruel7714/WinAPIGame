#include "PlayerUpperRender.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>

PlayerUpperRender::PlayerUpperRender()
{
}

PlayerUpperRender::~PlayerUpperRender()
{
}

void PlayerUpperRender::SetUpperRenderer()
{
	/*if (false == ResourcesManager::GetInst().IsLoadTexture("Right_Upper.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Upper.bmp"), 5, 6);
	}

	UpperRenderer = CreateRenderer("Right_Upper.bmp", RenderOrder::PlayerUpper);*/
}
