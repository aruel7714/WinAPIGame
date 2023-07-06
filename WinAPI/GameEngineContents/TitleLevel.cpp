#include "TitleLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCore.h>

#include "TitleBackGround.h"

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

	if (nullptr == GameEngineSound::FindSound("titleSound.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("titleSound.wav"));
	}

	BackGroundPtr = CreateActor<TitleBackGround>();
	BackGroundPtr->Init("TitleScreen.bmp");
	
	GameEngineSound::SetGlobalVolume(0.5f);
	
}

void TitleLevel::Update(float _DeltaTime)
{
	

	if (true == GameEngineInput::IsDown('1'))
	{
		// GameEngineCore::ChangeLevel("CharacterSelectLevel");
		GameEngineCore::ChangeLevel("Stage1");
	}
}
void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineSound::SoundPlay("titleSound.wav");
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}