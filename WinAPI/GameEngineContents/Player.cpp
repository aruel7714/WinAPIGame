#include "Player.h"
#include "ContentsEnum.h"
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
#include <GameEngineCore/GameEngineCollision.h>

Player* Player::MainPlayer = nullptr;

Player::Player()
{
}

Player::~Player()
{
}

//void Player::CameraFocus()
//{
//	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
//	//GetLevel()->GetMainCamera()->SetPos(GetPos() + float4(-WindowScale.hX(), -WindowScale.hY()));
//	//GetLevel()->GetMainCamera()->SetPos({ GetPos().X - WindowScale.hX(), GetPos().Y - WindowScale.hY() - 240.0f });
//	//GetLevel()->GetMainCamera()->SetPos({0, 0});
//}

void Player::LevelStart()
{
	MainPlayer = this;
}

void Player::Start()
{
	// Lower는 무기 종류 신경안씀
	// Upper는 무기 종류 신경씀 -> Pistol, Rifle 둘 따로 해주거나 한파일에 둘다 넣어놔야함
	// 따로 하는게 낫겠지?

	if (false == ResourcesManager::GetInst().IsLoadTexture("Right_Lower.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();
			
		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Lower_Idle.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Lower.bmp"), 5, 5);
		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Lower_Move.bmp"), 5, 3);
		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Upper_Idle.bmp"), 5, 1);
		

		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Player.bmp"), 5, 17);
		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Player.bmp"), 5, 17);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Left_Lower.bmp"))
	{
		GameEnginePath FilePath;
		
		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Lower.bmp"), 5, 5);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Right_Death.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Death.bmp"), 5, 12);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Left_Death.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Death.bmp"), 5, 12);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Right_Pistol_All.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Pistol_All.bmp"), 5, 2);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Left_Pistol_All.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Pistol_All.bmp"), 5, 2);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Right_Pistol_Sit.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Pistol_Sit.bmp"), 5, 10);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Left_Pistol_Sit.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Pistol_Sit.bmp"), 5, 10);
	}



	if (false == ResourcesManager::GetInst().IsLoadTexture("Right_Pistol_Upper.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Pistol_Upper.bmp"), 5, 17);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Left_Pistol_Upper.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Pistol_Upper.bmp"), 5, 17);
	}
	
	if (false == ResourcesManager::GetInst().IsLoadTexture("Right_Rifle_Upper.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Rifle_Upper.bmp"), 5, 17);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Left_Rifle_Upper.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Rifle_Upper.bmp"), 5, 17);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Right_Rifle_All.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Rifle_All.bmp"), 5, 2);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Left_Rifle_All.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Rifle_All.bmp"), 5, 2);
	}

	{
		//LowerRenderer = CreateRenderer("Right_Lower.bmp", RenderOrder::PlayerLower);
		LowerRenderer = CreateRenderer(RenderOrder::PlayerLower);
		UpperRenderer = CreateRenderer("Right_Pistol_Upper.bmp", RenderOrder::PlayerUpper);
		//UpperRenderer = CreateRenderer(RenderOrder::PlayerUpper);
		//UpperRenderer = CreateRenderer("Left_Pistol_Upper.bmp", RenderOrder::PlayerUpper);
		// MainRenderer = CreateRenderer(1);

		
		
		//MainRenderer->CreateAnimation("Right_Lower_Idle", "Right_Lower_Idle.bmp", 0, 0, 0.1f, true);
		//MainRenderer->CreateAnimation("Right_Lower_Idle", "Right_Lower.bmp", 0, 0, 0.1f, true);
		
		//MainRenderer->CreateAnimation("Right_Lower_Move", "Right_Lower_Move.bmp", 0, 10, 0.1f, true);
		//MainRenderer->CreateAnimation("Right_Lower_Move", "Right_Lower.bmp", 1, 12, 0.1f, true);

		// MainRenderer->CreateAnimation("Right_Lower", "Right_Lower.bmp", 0, 18, 0.1f, true);
		// LowerRenderer->CreateAnimation("Right_Lower_Idle", "Right_Lower.bmp", 0, 0, 1.0f, true);
		LowerRenderer->CreateAnimation("Right_Lower_Idle", "Right_Lower.bmp", 0, 0, 0.1f, true);
		LowerRenderer->CreateAnimation("Right_Lower_Move", "Right_Lower.bmp", 1, 12, 0.04f, true);
		//LowerRenderer->CreateAnimation("Right_Lower_Move", "Right_Lower.bmp", 1, 12, 0.5f, true);
		LowerRenderer->CreateAnimation("Right_Lower_IdleJump", "Right_Lower.bmp", 13, 18, 0.1f, false);
		LowerRenderer->CreateAnimation("Right_Lower_MoveJump", "Right_Lower.bmp", 19, 24, 0.1f, false);

		LowerRenderer->CreateAnimation("Right_Pistol_Lower_MoveStop1", "Right_Pistol_All.bmp", 0, 3, 0.05f, false);
		LowerRenderer->CreateAnimation("Right_Pistol_Lower_MoveStop2", "Right_Pistol_All.bmp", 3, 0, 0.05f, false);
		LowerRenderer->CreateAnimation("Right_Pistol_Lower_SitDown", "Right_Pistol_All.bmp", 4, 6, 0.05f, false);
		LowerRenderer->CreateAnimation("Right_Pistol_Lower_SitUp", "Right_Pistol_All.bmp", 5, 4, 0.05f, false);
		LowerRenderer->CreateAnimation("Right_Pistol_Lower_SitIdle1", "Right_Pistol_Sit.bmp", 0, 3, 0.1f, false);
		LowerRenderer->CreateAnimation("Right_Pistol_Lower_SitIdle2", "Right_Pistol_Sit.bmp", 3, 1, 0.1f, false);
		LowerRenderer->CreateAnimation("Right_Pistol_Lower_SitMove", "Right_Pistol_Sit.bmp", 4, 10, 0.08f, true);
		LowerRenderer->CreateAnimation("Right_Pistol_Lower_SitFire", "Right_Pistol_Sit.bmp", 11, 20, 0.05f, false);
		LowerRenderer->CreateAnimation("Right_Pistol_Lower_SitFireIdle1", "Right_Pistol_Sit.bmp", 21, 24, 0.15f, false);
		LowerRenderer->CreateAnimation("Right_Pistol_Lower_SitFireIdle2", "Right_Pistol_Sit.bmp", 24, 22, 0.15f, false);
		LowerRenderer->CreateAnimation("Right_Pistol_Lower_SitGranade", "Right_Pistol_Sit.bmp", 25, 30, 0.05f, false);
		LowerRenderer->CreateAnimation("Right_Pistol_Lower_SitGranadeIdle1", "Right_Pistol_Sit.bmp", 31, 34, 0.1f, false);
		LowerRenderer->CreateAnimation("Right_Pistol_Lower_SitGranadeIdle2", "Right_Pistol_Sit.bmp", 34, 32, 0.1f, false);

		LowerRenderer->CreateAnimation("Right_Rifle_Lower_MoveStop1", "Right_Rifle_All.bmp", 0, 3, 0.05f, false);
		LowerRenderer->CreateAnimation("Right_Rifle_Lower_MoveStop2", "Right_Rifle_All.bmp", 3, 0, 0.05f, false);
		LowerRenderer->CreateAnimation("Right_Rifle_Lower_SitDown", "Right_Rifle_All.bmp", 4, 6, 0.05f, false);
		LowerRenderer->CreateAnimation("Right_Rifle_Lower_SitUp", "Right_Rifle_All.bmp", 5, 4, 0.05f, false);

		LowerRenderer->CreateAnimation("Right_Lower_RangeDeathJump", "Right_Death.bmp", 0, 9, 0.1f, false);
		LowerRenderer->CreateAnimation("Right_Lower_RangeDeathGround", "Right_Death.bmp", 9, 18, 0.1f, false);
		LowerRenderer->CreateAnimation("Right_Lower_MeleeDeath", "Right_Death.bmp", 19, 37, 0.05f, false);
		LowerRenderer->CreateAnimation("Right_Lower_SwordDeath", "Right_Death.bmp", 38, 56, 0.1f, false);

		LowerRenderer->CreateAnimation("Left_Lower_Idle", "Left_Lower.bmp", 0, 0, 0.1f, true);
		LowerRenderer->CreateAnimation("Left_Lower_Move", "Left_Lower.bmp", 1, 12, 0.04f, true);
		LowerRenderer->CreateAnimation("Left_Lower_IdleJump", "Left_Lower.bmp", 13, 18, 0.1f, false);
		LowerRenderer->CreateAnimation("Left_Lower_MoveJump", "Left_Lower.bmp", 19, 24, 0.1f, false);

		LowerRenderer->CreateAnimation("Left_Pistol_Lower_MoveStop1", "Left_Pistol_All.bmp", 0, 3, 0.05f, false);
		LowerRenderer->CreateAnimation("Left_Pistol_Lower_MoveStop2", "Left_Pistol_All.bmp", 3, 0, 0.05f, false);
		LowerRenderer->CreateAnimation("Left_Pistol_Lower_SitDown", "Left_Pistol_All.bmp", 4, 6, 0.05f, false);
		LowerRenderer->CreateAnimation("Left_Pistol_Lower_SitUp", "Left_Pistol_All.bmp", 5, 4, 0.05f, false);
		LowerRenderer->CreateAnimation("Left_Pistol_Lower_SitIdle1", "Left_Pistol_Sit.bmp", 0, 3, 0.1f, false);
		LowerRenderer->CreateAnimation("Left_Pistol_Lower_SitIdle2", "Left_Pistol_Sit.bmp", 3, 1, 0.1f, false);
		LowerRenderer->CreateAnimation("Left_Pistol_Lower_SitMove", "Left_Pistol_Sit.bmp", 4, 10, 0.08f, true);
		LowerRenderer->CreateAnimation("Left_Pistol_Lower_SitFire", "Left_Pistol_Sit.bmp", 11, 20, 0.05f, false);
		LowerRenderer->CreateAnimation("Left_Pistol_Lower_SitFireIdle1", "Left_Pistol_Sit.bmp", 21, 24, 0.15f, false);
		LowerRenderer->CreateAnimation("Left_Pistol_Lower_SitFireIdle2", "Left_Pistol_Sit.bmp", 24, 22, 0.15f, false);
		LowerRenderer->CreateAnimation("Left_Pistol_Lower_SitGranade", "Left_Pistol_Sit.bmp", 25, 30, 0.05f, false);
		LowerRenderer->CreateAnimation("Left_Pistol_Lower_SitGranadeIdle1", "Left_Pistol_Sit.bmp", 31, 34, 0.1f, false);
		LowerRenderer->CreateAnimation("Left_Pistol_Lower_SitGranadeIdle2", "Left_Pistol_Sit.bmp", 34, 32, 0.1f, false);

		LowerRenderer->CreateAnimation("Left_Rifle_Lower_MoveStop1", "Left_Rifle_All.bmp", 0, 3, 0.05f, false);
		LowerRenderer->CreateAnimation("Left_Rifle_Lower_MoveStop2", "Left_Rifle_All.bmp", 3, 0, 0.05f, false);
		LowerRenderer->CreateAnimation("Left_Rifle_Lower_SitDown", "Left_Rifle_All.bmp", 4, 6, 0.05f, false);
		LowerRenderer->CreateAnimation("Left_Rifle_Lower_SitUp", "Left_Rifle_All.bmp", 5, 4, 0.05f, false);

		LowerRenderer->CreateAnimation("Left_Lower_RangeDeathJump", "Left_Death.bmp", 0, 9, 0.1f, false);
		LowerRenderer->CreateAnimation("Left_Lower_RangeDeathGround", "Left_Death.bmp", 10, 18, 0.1f, false);
		LowerRenderer->CreateAnimation("Left_Lower_MeleeDeath", "Left_Death.bmp", 19, 37, 0.05f, false);
		LowerRenderer->CreateAnimation("Left_Lower_SwordDeath", "Left_Death.bmp", 38, 56, 0.1f, false);

		

		

		// RightUp
		// RightDia 필요
		UpperRenderer->CreateAnimation("Right_Pistol_Upper_Idle", "Right_Pistol_Upper.bmp", 0, 5, 0.1f, true);
		// UpperRenderer->CreateAnimation("Right_Pistol_Upper_Move", "Right_Pistol_Upper.bmp", 6, 17, 0.03f, true);
		UpperRenderer->CreateAnimation("Right_Pistol_Upper_Move", "Right_Pistol_Upper.bmp", 6, 17, 0.04f, true);
		UpperRenderer->CreateAnimation("Right_Pistol_Upper_IdleJump", "Right_Pistol_Upper.bmp", 18, 23, 0.1f, false);
		UpperRenderer->CreateAnimation("Right_Pistol_Upper_MoveJump", "Right_Pistol_Upper.bmp", 24, 29, 0.1f, false);
		UpperRenderer->CreateAnimation("Right_Pistol_Upper_Fire", "Right_Pistol_Upper.bmp", 30, 39, 0.05f, false);
		UpperRenderer->CreateAnimation("Right_Pistol_Upper_Granade", "Right_Pistol_Upper.bmp", 40, 45, 0.05f, false);
		UpperRenderer->CreateAnimation("Right_Pistol_Upper_LookUp", "Right_Pistol_Upper.bmp", 46, 47, 0.05f, false);
		UpperRenderer->CreateAnimation("Right_Pistol_Upper_LookDown", "Right_Pistol_Upper.bmp", 47, 46, 0.05f, false);
		UpperRenderer->CreateAnimation("RightUp_Pistol_Upper_Idle1", "Right_Pistol_Upper.bmp", 48, 51, 0.1f, false);
		UpperRenderer->CreateAnimation("RightUp_Pistol_Upper_Idle2", "Right_Pistol_Upper.bmp", 51, 49, 0.1f, false);
		UpperRenderer->CreateAnimation("RightUp_Pistol_Upper_Fire", "Right_Pistol_Upper.bmp", 52, 61, 0.05f, false);
		UpperRenderer->CreateAnimation("Right_Pistol_Upper_JumpLookDown", "Right_Pistol_Upper.bmp", 62, 64, 0.05f, false);
		UpperRenderer->CreateAnimation("Right_Pistol_Upper_JumpLookUp", "Right_Pistol_Upper.bmp", 64, 62, 0.05f, false);
		UpperRenderer->CreateAnimation("RightDown_Pistol_Upper_Idle", "Right_Pistol_Upper.bmp", 64, 64, 0.1f, false);
		UpperRenderer->CreateAnimation("RightDown_Pistol_Upper_Fire", "Right_Pistol_Upper.bmp", 65, 70, 0.05f, false);
		UpperRenderer->CreateAnimation("Right_Pistol_Upper_MeleeAtt1", "Right_Pistol_Upper.bmp", 71, 76, 0.01f, false);
		UpperRenderer->CreateAnimation("Right_Pistol_Upper_MeleeAtt1End", "Right_Pistol_Upper.bmp", 76, 76, 0.2f, false);
		UpperRenderer->CreateAnimation("Right_Pistol_Upper_MeleeAtt2", "Right_Pistol_Upper.bmp", 77, 82, 0.03f, false);

		UpperRenderer->CreateAnimation("Right_Pistol_Upper_FireStart", "Right_Pistol_Upper.bmp", 30, 30, 0.001f, false);

		UpperRenderer->CreateAnimation("Left_Pistol_Upper_Idle", "Left_Pistol_Upper.bmp", 0, 5, 0.1f, true);
		UpperRenderer->CreateAnimation("Left_Pistol_Upper_Move", "Left_Pistol_Upper.bmp", 6, 17, 0.04f, true);
		UpperRenderer->CreateAnimation("Left_Pistol_Upper_IdleJump", "Left_Pistol_Upper.bmp", 18, 23, 0.1f, false);
		UpperRenderer->CreateAnimation("Left_Pistol_Upper_MoveJump", "Left_Pistol_Upper.bmp", 24, 29, 0.1f, false);
		UpperRenderer->CreateAnimation("Left_Pistol_Upper_Fire", "Left_Pistol_Upper.bmp", 30, 39, 0.05f, false);
		UpperRenderer->CreateAnimation("Left_Pistol_Upper_Granade", "Left_Pistol_Upper.bmp", 40, 45, 0.05f, false);
		UpperRenderer->CreateAnimation("Left_Pistol_Upper_LookUp", "Left_Pistol_Upper.bmp", 46, 47, 0.05f, false);
		UpperRenderer->CreateAnimation("Left_Pistol_Upper_LookDown", "Left_Pistol_Upper.bmp", 47, 46, 0.05f, false);
		UpperRenderer->CreateAnimation("LeftUp_Pistol_Upper_Idle1", "Left_Pistol_Upper.bmp", 48, 51, 0.1f, true);
		UpperRenderer->CreateAnimation("LeftUp_Pistol_Upper_Idle2", "Left_Pistol_Upper.bmp", 51, 49, 0.1f, true);
		UpperRenderer->CreateAnimation("LeftUp_Pistol_Upper_Fire", "Left_Pistol_Upper.bmp", 52, 61, 0.05f, false);
		UpperRenderer->CreateAnimation("Left_Pistol_Upper_JumpLookDown", "Left_Pistol_Upper.bmp", 62, 64, 0.05f, false);
		UpperRenderer->CreateAnimation("Left_Pistol_Upper_JumpLookUp", "Left_Pistol_Upper.bmp", 64, 62, 0.05f, false);
		UpperRenderer->CreateAnimation("LeftDown_Pistol_Upper_Idle", "Left_Pistol_Upper.bmp", 64, 64, 0.1f, false);
		UpperRenderer->CreateAnimation("LeftDown_Pistol_Upper_Fire", "Left_Pistol_Upper.bmp", 65, 70, 0.05f, false);
		UpperRenderer->CreateAnimation("Left_Pistol_Upper_MeleeAtt1", "Left_Pistol_Upper.bmp", 71, 76, 0.01f, false);
		UpperRenderer->CreateAnimation("Left_Pistol_Upper_MeleeAtt1End", "Left_Pistol_Upper.bmp", 76, 76, 0.2f, false);
		UpperRenderer->CreateAnimation("Left_Pistol_Upper_MeleeAtt2", "Left_Pistol_Upper.bmp", 77, 82, 0.02f, false);

		UpperRenderer->CreateAnimation("Left_Pistol_Upper_FireStart", "Left_Pistol_Upper.bmp", 30, 30, 0.001f, false);
		
		UpperRenderer->CreateAnimation("Right_Rifle_Upper_Idle", "Right_Rifle_Upper.bmp", 0, 3, 1.0f, true);
		UpperRenderer->CreateAnimation("Right_Rifle_Upper_Move", "Right_Rifle_Upper.bmp", 4, 15, 1.0f, true);
		UpperRenderer->CreateAnimation("Right_Rifle_Upper_IdleJump", "Right_Rifle_Upper.bmp", 16, 21, 1.0f, false);
		UpperRenderer->CreateAnimation("Right_Rifle_Upper_MoveJump", "Right_Rifle_Upper.bmp", 22, 27, 1.0f, false);
		UpperRenderer->CreateAnimation("Right_Rifle_Upper_Fire", "Right_Rifle_Upper.bmp", 28, 31, 1.0f, false);
		UpperRenderer->CreateAnimation("Right_Rifle_Upper_Granade", "Right_Rifle_Upper.bmp", 32, 37, 1.0f, false);
		UpperRenderer->CreateAnimation("Right_Rifle_Upper_MeleeAtt1", "Right_Rifle_Upper.bmp", 38, 43, 1.0f, false);
		UpperRenderer->CreateAnimation("Right_Rifle_Upper_MeleeAtt2", "Right_Rifle_Upper.bmp", 44, 49, 1.0f, false);
		UpperRenderer->CreateAnimation("Right_Rifle_Upper_LookUp", "Right_Rifle_Upper.bmp", 50, 51, 1.0f, false);
		UpperRenderer->CreateAnimation("Right_Rifle_Upper_LookDown", "Right_Rifle_Upper.bmp", 51, 50, 1.0f, false);
		UpperRenderer->CreateAnimation("RightUp_Rifle_Upper_Idle1", "Right_Rifle_Upper.bmp", 52, 55, 1.0f, false);
		UpperRenderer->CreateAnimation("RightUp_Rifle_Upper_Idle2", "Right_Rifle_Upper.bmp", 54, 53, 1.0f, false);
		UpperRenderer->CreateAnimation("RightUp_Rifle_Upper_Fire", "Right_Rifle_Upper.bmp", 56, 59, 1.0f, false);
		UpperRenderer->CreateAnimation("RightUp_Rifle_Upper_FireEnd", "Right_Rifle_Upper.bmp", 60, 65, 1.0f, false);
		// 흩뿌리기
		//UpperRenderer->CreateAnimation("")
		UpperRenderer->CreateAnimation("Right_Rifle_Upper_JumpLookDown", "Right_Rifle_Upper.bmp", 70, 71, 1.0f, false);
		UpperRenderer->CreateAnimation("Right_Rifle_Upper_JumpLookUp", "Right_Rifle_Upper.bmp", 71, 70, 1.0f, false);
		UpperRenderer->CreateAnimation("RightDown_Rifle_Upper_Idle", "Right_Rifle_Upper.bmp", 72, 72, 1.0f, false);
		UpperRenderer->CreateAnimation("RightDown_Rifle_Upper_Fire", "Right_Rifle_Upper.bmp", 73, 76, 1.0f, false);
		// 아래로 흩뿌리기
		//UpperRenderer->CreateAnimation()

		UpperRenderer->CreateAnimation("Left_Rifle_Upper_Idle", "Left_Rifle_Upper.bmp", 0, 3, 1.0f, true);
		UpperRenderer->CreateAnimation("Left_Rifle_Upper_Move", "Left_Rifle_Upper.bmp", 4, 15, 1.0f, true);
		UpperRenderer->CreateAnimation("Left_Rifle_Upper_IdleJump", "Left_Rifle_Upper.bmp", 16, 21, 1.0f, false);
		UpperRenderer->CreateAnimation("Left_Rifle_Upper_MoveJump", "Left_Rifle_Upper.bmp", 22, 27, 1.0f, false);
		UpperRenderer->CreateAnimation("Left_Rifle_Upper_Fire", "Left_Rifle_Upper.bmp", 28, 31, 1.0f, false);
		UpperRenderer->CreateAnimation("Left_Rifle_Upper_Granade", "Left_Rifle_Upper.bmp", 32, 37, 1.0f, false);
		UpperRenderer->CreateAnimation("Left_Rifle_Upper_MeleeAtt1", "Left_Rifle_Upper.bmp", 38, 43, 1.0f, false);
		UpperRenderer->CreateAnimation("Left_Rifle_Upper_MeleeAtt2", "Left_Rifle_Upper.bmp", 44, 49, 1.0f, false);
		UpperRenderer->CreateAnimation("Left_Rifle_Upper_LookUp", "Left_Rifle_Upper.bmp", 50, 51, 1.0f, false);
		UpperRenderer->CreateAnimation("Left_Rifle_Upper_LookDown", "Left_Rifle_Upper.bmp", 51, 50, 1.0f, false);
		UpperRenderer->CreateAnimation("LeftUp_Rifle_Upper_Idle1", "Left_Rifle_Upper.bmp", 52, 55, 1.0f, false);
		UpperRenderer->CreateAnimation("LeftUp_Rifle_Upper_Idle2", "Left_Rifle_Upper.bmp", 54, 53, 1.0f, false);
		UpperRenderer->CreateAnimation("LeftUp_Rifle_Upper_Fire", "Left_Rifle_Upper.bmp", 56, 59, 1.0f, false);
		UpperRenderer->CreateAnimation("LeftUp_Rifle_Upper_FireEnd", "Left_Rifle_Upper.bmp", 60, 65, 1.0f, false);
		// 흩뿌리기
		//UpperRenderer->CreateAnimation("")
		UpperRenderer->CreateAnimation("Left_Rifle_Upper_JumpLookDown", "Left_Rifle_Upper.bmp", 70, 71, 1.0f, false);
		UpperRenderer->CreateAnimation("Left_Rifle_Upper_JumpLookUp", "Left_Rifle_Upper.bmp", 71, 70, 1.0f, false);
		UpperRenderer->CreateAnimation("LeftDown_Rifle_Upper_Idle", "Left_Rifle_Upper.bmp", 72, 72, 1.0f, false);
		UpperRenderer->CreateAnimation("LeftDown_Rifle_Upper_Fire", "Left_Rifle_Upper.bmp", 73, 76, 1.0f, false);
		// 아래로 흩뿌리기
		//UpperRenderer->CreateAnimation()


		// UpperRenderer->CreateAnimation("Right_Upper_Idle", "Right_Upper.bmp", 0, 3, 0.5f, true);
		// UpperRenderer->CreateAnimation("Right_Upper", "Right_Upper.bmp", )
		
		//MainRenderer->ChangeAnimation("Right_Lower_Idle");
		//MainRenderer->ChangeAnimation("Right_Lower");

		//LowerRenderer->ChangeAnimation("Right_Lower_Idle");
		//UpperRenderer->ChangeAnimation("Right_Upper_Idle");
		// MainRenderer->SetRenderScaleToTexture();

		// UpperRenderer->GetActor()->SetPos({ LowerRenderer->GetActor()->GetPos().X, LowerRenderer->GetActor()->GetPos().Y + 10.0f });
		LowerRenderer->GetActor()->SetPos({ 3000, 800 });

		
		// UpperRenderer->SetRenderPos({ 20, -60 });
		// 33px
		UpperRenderer->SetRenderPos( { 0, -92 } );
		
		//UpperRenderer->SetRenderPos()
		
		LowerRenderer->SetRenderScaleToTexture();
		
	}

	{
		BodyCollision = CreateCollision(CollisionOrder::PlayerCollision);
		
		BodyCollision->SetCollisionScale({ 80, 140 });
		BodyCollision->SetCollisionType(CollisionType::Rect);
		BodyCollision->SetCollisionPos({ 0, -70 });
	}

	{
		MeleeAttCollision = CreateCollision(CollisionOrder::PlayerMeleeCollision);

		MeleeAttCollision->SetCollisionScale({ 120, 140 });
		MeleeAttCollision->SetCollisionType(CollisionType::Rect);
		MeleeAttCollision->SetCollisionPos({ 20, -70 });
		
	}


	//WeaponName = "Pistol_";
	WeaponName = "Rifle_";

	//ChangeState(PlayerState::Idle);
	//ChangeState(PlayerState::Move);

	ChangeLowerState(PlayerLowerState::Idle);
	ChangeUpperState(PlayerUpperState::Idle);
	Dir = PlayerDir::Right;
	
	int a = 0;
}

void Player::Update(float _Delta)
{
	

	if (true == GameEngineInput::IsDown(VK_F2))
	{
		GameEngineLevel::CollisionDebugRenderSwitch();
	}



	CameraFocus();
	LowerRenderer->SetRenderScaleToTexture();
	StateLowerUpdate(_Delta);
	StateUpperUpdate(_Delta);
}

void Player::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	CollisionData Data;

	Data.Pos = ActorCameraPos();

	Data.Scale = { 5,5 };

	Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
}

void Player::Release()
{

}
/*
void Player::ChangeState(PlayerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Move:
			MoveStart();
			break;
		case PlayerState::Fire:
			FireStart();
			break;
		case PlayerState::IdleJump:
			IdleJumpStart();
			break;
		case PlayerState::MoveJump:
			MoveJumpStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);
	case PlayerState::Move:
		return MoveUpdate(_Delta);
	case PlayerState::Fire:
		return FireUpdate(_Delta);
	case PlayerState::IdleJump:
		return IdleJumpUpdate(_Delta);
	case PlayerState::MoveJump:
		return MoveJumpUpdate(_Delta);
	default:
		break;
	}
}
*/

void Player::ChangeLowerState(PlayerLowerState _LowerState)
{
	if (_LowerState != LowerState)
	{
		switch (_LowerState)
		{
		case PlayerLowerState::Idle:
			IdleLowerStart();
			break;
		case PlayerLowerState::Move:
			MoveLowerStart();
			break;
		case PlayerLowerState::IdleJump:
			IdleJumpLowerStart();
			break;
		case PlayerLowerState::MoveJump:
			MoveJumpLowerStart();
			break;
		case PlayerLowerState::MoveStop:
			MoveStopStart();
			break;
		case PlayerLowerState::SitDown:
			SitDownStart();
			break;
		case PlayerLowerState::SitUp:
			SitUpStart();
			break;
		case PlayerLowerState::SitIdle:
			SitIdleStart();
			break;
		case PlayerLowerState::SitMove:
			SitMoveStart();
			break;
		case PlayerLowerState::SitFire:
			SitFireStart();
			break;
		case PlayerLowerState::SitFireIdle:
			SitFireIdleStart();
			break;
		case PlayerLowerState::SitGranade:
			SitGranadeStart();
			break;
		case PlayerLowerState::SitGranadeIdle:
			SitGranadeIdleStart();
			break;
		case PlayerLowerState::RangeDeathJump:
			RangeDeathJumpStart();
			break;
		case PlayerLowerState::RangeDeathGround:
			RangeDeathGroundStart();
			break;
		case PlayerLowerState::MeleeDeath:
			MeleeDeathStart();
			break;
		case PlayerLowerState::SwordDeath:
			SwordDeathStart();
			break;
		default:
			break;
		}
	}
	LowerState = _LowerState;
}
void Player::StateLowerUpdate(float _Delta)
{
	switch (LowerState)
	{
	case PlayerLowerState::Idle:
		return IdleLowerUpdate(_Delta);
	case PlayerLowerState::Move:
		return MoveLowerUpdate(_Delta);
	case PlayerLowerState::IdleJump:
		return IdleJumpLowerUpdate(_Delta);
	case PlayerLowerState::MoveJump:
		return MoveJumpLowerUpdate(_Delta);
	case PlayerLowerState::MoveStop:
		return MoveStopUpdate(_Delta);
	case PlayerLowerState::SitDown:
		return SitDownUpdate(_Delta);
	case PlayerLowerState::SitUp:
		return SitUpUpdate(_Delta);
	case PlayerLowerState::SitIdle:
		return SitIdleUpdate(_Delta);
	case PlayerLowerState::SitMove:
		return SitMoveUpdate(_Delta);
	case PlayerLowerState::SitFire:
		return SitFireUpdate(_Delta);
	case PlayerLowerState::SitFireIdle:
		return SitFireIdleUpdate(_Delta);
	case PlayerLowerState::SitGranade:
		return SitGranadeUpdate(_Delta);
	case PlayerLowerState::SitGranadeIdle:
		return SitGranadeIdleUpdate(_Delta);
	case PlayerLowerState::RangeDeathJump:
		return RangeDeathJumpUpdate(_Delta);
	case PlayerLowerState::RangeDeathGround:
		return RangeDeathGroundUpdate(_Delta);
	case PlayerLowerState::MeleeDeath:
		return MeleeDeathUpdate(_Delta);
	case PlayerLowerState::SwordDeath:
		return SwordDeathUpdate(_Delta);
	default:
		break;
	}
}

void Player::ChangeUpperState(PlayerUpperState _UpperState)
{
	if (_UpperState != UpperState)
	{
		switch (_UpperState)
		{
		case PlayerUpperState::Idle:
			IdleUpperStart();
			break;
		case PlayerUpperState::Move:
			MoveUpperStart();
			break;
		case PlayerUpperState::IdleJump:
			IdleJumpUpperStart();
			break;
		case PlayerUpperState::MoveJump:
			MoveJumpUpperStart();
			break;
		case PlayerUpperState::Fire:
			FireStart();
			break;
		case PlayerUpperState::Granade:
			GranadeStart();
			break;
		case PlayerUpperState::LookUp:
			LookUpStart();
			break;
		case PlayerUpperState::UpIdle:
			UpIdleStart();
			break;
		case PlayerUpperState::LookDown:
			LookDownStart();
			break;
		case PlayerUpperState::JumpLookDown:
			JumpLookDownStart();
			break;
		case PlayerUpperState::DownIdle:
			DownIdleStart();
			break;
		case PlayerUpperState::JumpLookUp:
			JumpLookUpStart();
			break;
		case PlayerUpperState::MeleeAtt:
			MeleeAttStart();
			break;
		default:
			break;
		}
	}
	UpperState = _UpperState;
}
void Player::StateUpperUpdate(float _Delta)
{
	switch (UpperState)
	{
	case PlayerUpperState::Idle:
		return IdleUpperUpdate(_Delta);
	case PlayerUpperState::Move:
		return MoveUpperUpdate(_Delta);
	case PlayerUpperState::IdleJump:
		return IdleJumpUpperUpdate(_Delta);
	case PlayerUpperState::MoveJump:
		return MoveJumpUpperUpdate(_Delta);
	case PlayerUpperState::Fire:
		return FireUpdate(_Delta);
	case PlayerUpperState::Granade:
		return GranadeUpdate(_Delta);
	case PlayerUpperState::LookUp:
		return LookUpUpdate(_Delta);
	case PlayerUpperState::UpIdle:
		return UpIdleUpdate(_Delta);
	case PlayerUpperState::LookDown:
		return LookDownUpdate(_Delta);
	case PlayerUpperState::JumpLookDown:
		return JumpLookDownUpdate(_Delta);
	case PlayerUpperState::DownIdle:
		return DownIdleUpdate(_Delta);
	case PlayerUpperState::JumpLookUp:
		return JumpLookUpUpdate(_Delta);
	case PlayerUpperState::MeleeAtt:
		return MeleeAttUpdate(_Delta);
	default:
		break;
	}
}

void Player::DirCheck()
{
	if (true == GameEngineInput::IsFree(VK_LEFT) && true == GameEngineInput::IsFree(VK_RIGHT))
	{
		return;
	}

	// A가 눌렸을때 왼쪽을 바라보게
	// 왼쪽 방향키가 눌렸을때 왼쪽을 바라보게
	// if (true == GameEngineInput::IsDown('A') || true == GameEngineInput::IsFree('D'))
	if (true == GameEngineInput::IsDown(VK_LEFT) || true == GameEngineInput::IsFree(VK_RIGHT))
	{
		Dir = PlayerDir::Left;
		MeleeAttCollision->SetCollisionPos({ -20, -70 });
		//ChangeLowerAnimationState(CurState);
		return;
	}

	// D가 눌렸을때 오른쪽을 바라보게
	// 오른쪽 방향키가 눌렸을때 오른쪽을 바라보게
	// if (true == GameEngineInput::IsFree('A') || true == GameEngineInput::IsDown('D'))
	if(true == GameEngineInput::IsFree(VK_LEFT) || true == GameEngineInput::IsDown(VK_RIGHT))
	{
		Dir = PlayerDir::Right;
		MeleeAttCollision->SetCollisionPos({ 20, -70 });
		//ChangeAnimationState(CurState);
		return;
	}

	
}

void Player::ChangeAnimationState(const std::string & _State)
{
	std::string LowerAnimationName;
	std::string UpperAnimationName;

	switch (Dir)
	{
	case PlayerDir::Right:
		LowerAnimationName = "Right_Lower_";
		UpperAnimationName = "Right_Pistol_Upper_";
		break;
	case PlayerDir::Left:
		LowerAnimationName = "Left_Lower_";
		UpperAnimationName = "Left_Pistol_Upper_";
		break;
	default:
		break;
	}

	LowerAnimationName += _State;
	UpperAnimationName += _State;
	CurState = _State;

	//UpperRenderer->GetActor()->SetPos(LowerRenderer->GetActor()->GetPos());

	LowerRenderer->ChangeAnimation(LowerAnimationName);
	UpperRenderer->ChangeAnimation(UpperAnimationName);
}

void Player::ChangeLowerAnimationState(const std::string& _State, bool _IsWeapon, bool _IsForce)
{
	std::string LowerAnimationName;

	if (false == _IsWeapon)
	{
		switch (Dir)
		{
		case PlayerDir::Right:
			LowerAnimationName = "Right_Lower_";
			break;
		case PlayerDir::Left:
			LowerAnimationName = "Left_Lower_";
			break;
		default:
			break;
		}
		LowerAnimationName += _State;
	}
	else if (true == _IsWeapon)
	{
		switch (Dir)
		{
		case PlayerDir::Right:
			LowerAnimationName = "Right_";
			break;
		case PlayerDir::Left:
			LowerAnimationName = "Left_";
			break;
		default:
			break;
		}

		LowerAnimationName += WeaponName;

		LowerAnimationName += "Lower_";

		LowerAnimationName += _State;

		if (nullptr == LowerRenderer->FindAnimation(LowerAnimationName))
		{
			MsgBoxAssert(LowerAnimationName + "의 애니메이션이 없습니다");
		}

		//if (true == GameEngineInput::IsPress(VK_DOWN))
		//{
		//	std::string CheckAnimation = "";
		//	
		//	switch (Dir)
		//	{
		//	case PlayerDir::Right:
		//		LowerAnimationName = "RightSit_";
		//		break;
		//	case PlayerDir::Left:
		//		LowerAnimationName = "LeftSit_";
		//		break;
		//	default:
		//		break;
		//	}

		//	CheckAnimation += WeaponName;

		//	CheckAnimation += "Lower_";

		//	CheckAnimation += _State;

		//	if (nullptr != LowerRenderer->FindAnimation(CheckAnimation))
		//	{
		//		LowerAnimationName = CheckAnimation;
		//	}
		//}
	}
	
	LowerRenderer->ChangeAnimation(LowerAnimationName, 0, _IsForce);
}
void Player::ChangeUpperAnimationState(const std::string& _State, bool _IsForce)
{
	std::string UpperAnimationName;

	switch (Dir)
	{
	case PlayerDir::Right:
		UpperAnimationName = "Right_";
		break;
	case PlayerDir::Left:
		UpperAnimationName = "Left_";
		break;
	default:
		break;
	}

	UpperAnimationName += WeaponName;

	UpperAnimationName += "Upper_";

	UpperAnimationName += _State;


	if (true == GameEngineInput::IsPress(VK_UP))
	{
		std::string CheckAnimation = "";
		switch (Dir)
		{
		case PlayerDir::Right:
			CheckAnimation = "RightUp_";
			break;
		case PlayerDir::Left:
			CheckAnimation = "LeftUp_";
			break;
		default:
			break;
		}

		CheckAnimation += WeaponName;

		CheckAnimation += "Upper_";

		CheckAnimation += _State;

		if (nullptr != UpperRenderer->FindAnimation(CheckAnimation))
		{
			UpperAnimationName = CheckAnimation;
		}
	}

	if (true == GameEngineInput::IsPress(VK_DOWN))
	{
		std::string CheckAnimation = "";
		switch (Dir)
		{
		case PlayerDir::Right:
			CheckAnimation = "RightDown_";
			break;
		case PlayerDir::Left:
			CheckAnimation = "LeftDown_";
			break;
		default:
			break;
		}

		CheckAnimation += WeaponName;
		CheckAnimation += "Upper_";
		CheckAnimation += _State;

		if (nullptr != UpperRenderer->FindAnimation(CheckAnimation))
		{
			UpperAnimationName = CheckAnimation;
		}
	}

	UpperRenderer->ChangeAnimation(UpperAnimationName, 0, _IsForce);
}
