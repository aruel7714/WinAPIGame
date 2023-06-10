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
	//SecondRenderer = CreateRenderer(RenderOrder::SecondBackGround);
	DebugRenderer = CreateRenderer(RenderOrder::FirstBackGround);

	FirstRenderer->On();
	//SecondRenderer->On();
	DebugRenderer->Off();
}
void BackGround::Update(float _Delta) {}

void BackGround::Release() {}

void BackGround::Init(const std::string& _FileName)
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
	
	// stage1 À§Ä¡
	// SetPos({ Scale.hX(), Scale.hY() - 120});
}

void BackGround::Init(const std::string& _FileName, const std::string& _DebugFileName)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_FileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\" + _FileName);

		ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}
	/*if (false == ResourcesManager::GetInst().IsLoadTexture(_DebugFileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\" + _DebugFileName);

		ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}*/

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
	float4 Scale = Texture->GetScale();

	FirstRenderer->SetTexture(_FileName);
	FirstRenderer->SetRenderScale(Scale);

	DebugRenderer->SetTexture(_DebugFileName);
	DebugRenderer->SetRenderScale(Scale);

	// SetPos({ Scale.hX(), Scale.hY() - 124 });
	SetPos({ Scale.hX(), Scale.hY() });
//	DebugRenderer->SetRenderPos({ 0, 0 });
	
}

//void BackGround::InitDebug(const std::string& _DebugFileName)
//{
//	if (false == ResourcesManager::GetInst().IsLoadTexture(_DebugFileName))
//	{
//		GameEnginePath FilePath;
//		FilePath.SetCurrentPath();
//		FilePath.MoveParentToExistsChild("ContentsResources");
//		FilePath.MoveChild("ContentsResources\\Texture\\Map\\" + _DebugFileName);
//	}
//	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_DebugFileName);
//	float4 Scale = Texture->GetScale();
//	DebugRenderer->SetTexture(_DebugFileName);
//	DebugRenderer->SetRenderScale(Scale);
//	
//}

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

//void BackGround::Init(const std::string& _FileName, const std::string& _SecondFileName)
//{
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
//	if (false == ResourcesManager::GetInst().IsLoadTexture(_SecondFileName))
//	{
//		GameEnginePath FilePath;
//		FilePath.SetCurrentPath();
//		FilePath.MoveParentToExistsChild("ContentsResources");
//		FilePath.MoveChild("ContentsResources\\Texture\\Map\\" + _SecondFileName);
//
//		GameEngineWindowTexture* Text = ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
//	}
//
//	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_FileName);
//	float4 Scale = Texture->GetScale();
//	FirstRenderer->SetTexture(_FileName);
//	FirstRenderer->SetRenderScale(Scale);
//
//	FirstRenderer->GetActor()->SetPos({ Scale.hX(), Scale.hY() });
//
//	Texture = ResourcesManager::GetInst().FindTexture(_SecondFileName);
//	Scale = Texture->GetScale();
//	SecondRenderer->SetTexture(_SecondFileName);
//	SecondRenderer->SetRenderScale(Scale);
//
//	//SetPos({ Scale.hX(), Scale.hY() });
//	
//	SecondRenderer->SetRenderPos({ 0, 0 });
//	
//}



void BackGround::SwitchRender()
{
	SwitchRenderValue = !SwitchRenderValue;

	if (true == SwitchRenderValue)
	{
		FirstRenderer->On();
		//SecondRenderer->On();
		DebugRenderer->Off();
	}
	else
	{
		FirstRenderer->Off();
		//SecondRenderer->Off();
		DebugRenderer->On();
	}
}