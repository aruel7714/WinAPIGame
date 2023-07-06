#include "TitleBackGround.h"
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

TitleBackGround::TitleBackGround()
{
}

TitleBackGround::~TitleBackGround()
{
}

void TitleBackGround::Start()
{
	FirstRenderer = CreateRenderer(RenderOrder::FirstBackGround);
}

void TitleBackGround::Init(const std::string& _FileName)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\" + _FileName);

		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	float4 Scale = Texture->GetScale();
	FirstRenderer->SetTexture(_FileName);
	FirstRenderer->SetRenderScale(Scale);

	SetPos({ Scale.hX(), Scale.hY() });

}