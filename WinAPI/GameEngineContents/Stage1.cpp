#include "Stage1.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "Player.h"
#include "BackGround.h"

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
}

void Stage1::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Mission1_Test.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Mission1.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Mission1_Debug_Test.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Mission1_Debug.bmp"));
	}

	//if (false == ResourcesManager::GetInst().IsLoadTexture("Mission1_SecondBackGround.bmp"))
	//{
	//	GameEnginePath FilePath;
	//	FilePath.SetCurrentPath();
	//	FilePath.MoveParentToExistsChild("ContentsResources");

	//	FilePath.MoveChild("ContentsResources\\Texture\\Map\\");
	//	ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Mission1_SecondBackGround.bmp"));
	//}

	BackGroundPtr = CreateActor<BackGround>();
	// BackGroundPtr->Init("Mission1.bmp", "Mission1_SecondBackGround.bmp");
	BackGroundPtr->Init("Mission1_Test.bmp", "Mission1_Debug_Test.bmp");
	//BackGroundPtr->Init("Mission1.bmp");
	// BackGroundPtr->SecondInit("Mission1_SecondBackGround.bmp");

	
	

	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("Mission1_Debug.bmp");
	int a = 0;

}

void Stage1::CameraFocus()
{
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
	BackGroundPtr->GetLevel()->GetMainCamera()->SetPos(BackGroundPtr->GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });
}


void Stage1::Update(float _Delta) 
{
	if (true == GameEngineInput::IsDown(VK_F1))
	{
		BackGroundPtr->SwitchRender();
	}
}
void Stage1::Release() {}

void Stage1::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	//LevelPlayer->SetGroundTexture("Mission1_Debug.bmp");
}

void Stage1::LevelEnd(GameEngineLevel* _NextLevel)
{

}