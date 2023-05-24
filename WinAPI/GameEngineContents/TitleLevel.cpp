#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCore.h>

#include "BackGround.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("TitleScreen.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\TitleScreen\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("TitleScreen.bmp"));
	}

	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("TitleScreen.bmp");
}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown('1'))
	{
		// GameEngineCore::ChangeLevel("CharacterSelectLevel");
		GameEngineCore::ChangeLevel("Stage1");
	}
}
