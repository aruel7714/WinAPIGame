#include "BackGround.h"
#include "MetalSlugCore.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>

#pragma comment(lib, "msimg32.lib")

BackGround::BackGround()
{
}

BackGround::~BackGround()
{
}

void BackGround::Start()
{
	Renderer = CreateRenderer(0);

	DebugRenderer = CreateRenderer(0);

	Renderer->On();
	DebugRenderer->Off();
}
void BackGround::Update(float _Delta) {}

void BackGround::Release() {}

void BackGround::Init(const std::string& _FileName)
{
	FileName = _FileName;

	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\" + _FileName);

		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}
	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	float4 Scale = Texture->GetScale() * 3;
	Renderer->SetTexture(_FileName);
	Renderer->SetRenderScale(Scale);
	// SetPos({ Scale.hX(), Scale.hY() });
	SetPos({ Scale.hX(), Scale.hY() - 120});
}

//void BackGround::Init(const std::string& _FileName, const std::string& _DebugFileName)
//{
//	FileName = _FileName;
//
//	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
//	{
//		GameEnginePath FilePath;
//		FilePath.SetCurrentPath();
//		FilePath.MoveParentToExistsChild("ContentsResources");
//		FilePath.MoveChild("ContentsResources\\Texture\\Map\\" + _FileName);
//
//		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
//	}
//	
//	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
//	float4 Scale = Texture->GetScale();
//	Renderer->SetTexture(_FileName);
//	Renderer->SetRenderScale(Scale);
//	DebugRenderer->SetTexture(_DebugFileName);
//	DebugRenderer->SetRenderScale(Scale);
//	SetPos({ Scale.hX(), Scale.hY() });
//}

void BackGround::SwitchRender()
{
	SwitchRenderValue = !SwitchRenderValue;

	if (true == SwitchRenderValue)
	{
		Renderer->On();
		DebugRenderer->Off();
	}
	else
	{
		Renderer->Off();
		DebugRenderer->On();
	}
}