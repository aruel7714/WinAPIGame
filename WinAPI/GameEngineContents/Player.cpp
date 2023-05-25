#include "Player.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::CameraFocus()
{
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
	// GetLevel()->GetMainCamera()->SetPos(GetPos() + float4(-WindowScale.hX(), -WindowScale.hY()));
	GetLevel()->GetMainCamera()->SetPos({ GetPos().X - WindowScale.hX(), GetPos().Y - WindowScale.hX() - 120 });
}


void Player::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Right_All_Idle_Test.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();
			
		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Lower_Idle.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Lower_Move.bmp"), 5, 3);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Upper_Idle.bmp"), 5, 1);

		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Player.bmp"), 5, 17);
		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Player.bmp"), 5, 17);
	}

	{
		MainRenderer = CreateRenderer(1);
		
		MainRenderer->CreateAnimation("Right_Lower_Idle", "Right_Lower_Idle.bmp", 0, 0, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Lower_Move", "Right_Lower_Move.bmp", 0, 10, 0.1f, true);
		
		MainRenderer->ChangeAnimation("Right_Lower_Idle");
		MainRenderer->SetRenderScaleToTexture();

	}
	
}

void Player::Update(float _Delta)
{
	//CameraFocus();
}

//void Player::Render()
//{
//
//}

void Player::Release()
{

}
