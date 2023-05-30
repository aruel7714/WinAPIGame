#include "BackGround.h"
#include "MetalSlugCore.h"
#include "ContentsEnum.h"
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
	FirstRenderer = CreateRenderer(RenderOrder::FirstBackGround);
	SecondRenderer = CreateRenderer(RenderOrder::SecondBackGround);
	DebugRenderer = CreateRenderer(RenderOrder::FirstBackGround);

	FirstRenderer->On();
	SecondRenderer->On();
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
	float4 Scale = Texture->GetScale();
	FirstRenderer->SetTexture(_FileName);
	FirstRenderer->SetRenderScale(Scale);
	
	SetPos({ Scale.hX(), Scale.hY() });
	// 카메라를 옮길것.
	
	// stage1 위치
	// SetPos({ Scale.hX(), Scale.hY() - 120});
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

void BackGround::SecondInit(const std::string& _FileName)
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
	float4 Scale = Texture->GetScale();
	SecondRenderer->SetTexture(_FileName);
	SecondRenderer->SetRenderScale(Scale);

	//SetPos({ Scale.hX(), Scale.hY() });
	
	SetPos(FirstRenderer->GetActor()->GetPos());
	
}



void BackGround::SwitchRender()
{
	SwitchRenderValue = !SwitchRenderValue;

	if (true == SwitchRenderValue)
	{
		FirstRenderer->On();
		DebugRenderer->Off();
	}
	else
	{
		FirstRenderer->Off();
		DebugRenderer->On();
	}
}