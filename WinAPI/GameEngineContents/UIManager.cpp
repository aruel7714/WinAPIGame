#include "UIManager.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>

UIManager* UIManager::UI = nullptr;

UIManager::UIManager()
{
	UI = this;
}

UIManager::~UIManager()
{
}

void UIManager::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("PlayerStatusUI.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("PlayerStatusUI.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("PlayerGaugeUI.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("PlayerGaugeUI.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Score.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Score.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Time.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\UI\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Time.bmp"));
	}

	{
		GameEngineRenderer* Status = CreateUIRenderer("PlayerStatusUI.bmp", RenderOrder::UI);
		Status->SetRenderPos({ 416, 54 });
		Status->SetTexture("PlayerStatusUI.bmp");
		Status->SetRenderScaleToTexture();
	}

	{
		GameEngineRenderer* Gauge = CreateUIRenderer("PlayerGaugeUI.bmp", RenderOrder::UI);
		Gauge->SetRenderPos({ 160, 68 });
		Gauge->SetTexture("PlayerGaugeUI.bmp");
		Gauge->SetRenderScaleToTexture();
	}

	{
		GameEngineRenderer* Score = CreateUIRenderer("Score.bmp", RenderOrder::UI);
		Score->SetRenderPos({ 270, 36 });
		Score->SetTexture("Score.bmp");
		Score->SetRenderScaleToTexture();
	}

	{
		GameEngineRenderer* Score = CreateUIRenderer("Time.bmp", RenderOrder::UI);
		Score->SetRenderPos({ 608, 52 });
		Score->SetTexture("Time.bmp");
		Score->SetRenderScaleToTexture();
	}
}