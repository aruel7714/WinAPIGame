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

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_All_Idle_Test.bmp"), 0, 0);

		//GameEngineWindowTexture* a = ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Right_All_Idle_Test.bmp"));

		int b = 0;
		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Player.bmp"), 5, 17);
		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Player.bmp"), 5, 17);
	}

	{
		MainRenderer = CreateRenderer(0);
		MainRenderer->SetRenderScale({ 100, 100 });
		
	}
	
}

void Player::Update(float _Delta)
{

}

//void Player::Render()
//{
//
//}

void Player::Release()
{

}
