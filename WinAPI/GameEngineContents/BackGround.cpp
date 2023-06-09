#include "BackGround.h"
#include "MetalSlugCore.h"
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

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
	ThirdRenderer = CreateRenderer(RenderOrder::ThirdBackGround);
	CloudRenderer = CreateRenderer(RenderOrder::CloudBackGround);
	ObjectRenderer = CreateRenderer(RenderOrder::Object2);
	DebugRenderer = CreateRenderer(RenderOrder::FirstBackGround);
	
	//{
	//	FirstCollision = CreateCollision(CollisionOrder::DebugCollision);
	//	FirstCollision->SetCollisionScale({ 300, 500 });
	//	FirstCollision->SetCollisionType(CollisionType::Rect);
	//	//FirstCollision->SetCollisionPos({ 500, 100 });
	//	FirstCollision->SetCollisionPos({ -3000, 200 });
	//}

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
	
	// stage1 ��ġ
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

	//MapTexture = ResourcesManager::GetInst().FindTexture(_FileName);

	// SetPos({ Scale.hX(), Scale.hY() - 124 });
	SetPos({ Scale.hX(), Scale.hY() });
	// SetRenderPos(GameEngineWindow::MainWindow.GetScale().Half())
//	DebugRenderer->SetRenderPos({ 0, 0 });
	
}

void BackGround::SecondInit(const std::string& _SecondFileName)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_SecondFileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\" + _SecondFileName);

		ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_SecondFileName);
	float4 Scale = Texture->GetScale();

	SecondRenderer->SetTexture(_SecondFileName);
	SecondRenderer->SetRenderScale(Scale);

	SetPos({ Scale.hX(), Scale.hY() });

}

void BackGround::ThirdInit(const std::string& _ThirdFileName)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_ThirdFileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\" + _ThirdFileName);

		ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_ThirdFileName);
	float4 Scale = Texture->GetScale();

	ThirdRenderer->SetTexture(_ThirdFileName);
	ThirdRenderer->SetRenderScale(Scale);

	SetPos({ Scale.hX(), Scale.hY() });
}

void BackGround::ObjectInit(const std::string& _ObjectFileName)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_ObjectFileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\" + _ObjectFileName);

		ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_ObjectFileName);
	float4 Scale = Texture->GetScale();

	ObjectRenderer->SetTexture(_ObjectFileName);
	ObjectRenderer->SetRenderScale(Scale);

	SetPos({ Scale.hX(), Scale.hY() });
}

void BackGround::CloudInit(const std::string& _CloudFileName)
{
	if (false == ResourcesManager::GetInst().IsLoadTexture(_CloudFileName))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\" + _CloudFileName);

		ResourcesManager::GetInst().TextureLoad(FilePath.GetStringPath());
	}

	GameEngineWindowTexture* Texture = ResourcesManager::GetInst().FindTexture(_CloudFileName);
	float4 Scale = Texture->GetScale();

	CloudRenderer->SetTexture(_CloudFileName);
	CloudRenderer->SetRenderScale(Scale);

	SetPos({ Scale.hX(), Scale.hY() });
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
		SecondRenderer->On();
		ThirdRenderer->On();
		ObjectRenderer->On();
		DebugRenderer->Off();
	}
	else
	{
		FirstRenderer->Off();
		SecondRenderer->Off();
		ThirdRenderer->Off();
		ObjectRenderer->Off();
		DebugRenderer->On();
	}
}