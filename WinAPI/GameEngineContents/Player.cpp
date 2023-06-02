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

Player* Player::MainPlayer = nullptr;

Player::Player()
{
}

Player::~Player()
{
}

void Player::CameraFocus()
{
	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
	//GetLevel()->GetMainCamera()->SetPos(GetPos() + float4(-WindowScale.hX(), -WindowScale.hY()));
	//GetLevel()->GetMainCamera()->SetPos({ GetPos().X - WindowScale.hX(), GetPos().Y - WindowScale.hY() - 240.0f });
	//GetLevel()->GetMainCamera()->SetPos({0, 0});
}

void Player::LevelStart()
{
	MainPlayer = this;
}

void Player::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Right_Lower.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();
			
		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Lower_Idle.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Lower.bmp"), 5, 4);
		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Lower_Move.bmp"), 5, 3);
		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Upper_Idle.bmp"), 5, 1);
		

		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Player.bmp"), 5, 17);
		//ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Player.bmp"), 5, 17);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Right_Upper.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Upper.bmp"), 5, 6);
	}

	{
		LowerRenderer = CreateRenderer("Right_Lower.bmp", RenderOrder::PlayerLower);
		UpperRenderer = CreateRenderer("Right_Upper.bmp", RenderOrder::PlayerUpper);
		// MainRenderer = CreateRenderer(1);

		
		
		//MainRenderer->CreateAnimation("Right_Lower_Idle", "Right_Lower_Idle.bmp", 0, 0, 0.1f, true);
		//MainRenderer->CreateAnimation("Right_Lower_Idle", "Right_Lower.bmp", 0, 0, 0.1f, true);
		
		//MainRenderer->CreateAnimation("Right_Lower_Move", "Right_Lower_Move.bmp", 0, 10, 0.1f, true);
		//MainRenderer->CreateAnimation("Right_Lower_Move", "Right_Lower.bmp", 1, 12, 0.1f, true);

		// MainRenderer->CreateAnimation("Right_Lower", "Right_Lower.bmp", 0, 18, 0.1f, true);
		// LowerRenderer->CreateAnimation("Right_Lower_Idle", "Right_Lower.bmp", 0, 0, 1.0f, true);
		LowerRenderer->CreateAnimation("Right_Lower_Idle", "Right_Lower.bmp", 0, 0, 0.5f, true);
		LowerRenderer->CreateAnimation("Right_Lower_Move", "Right_Lower.bmp", 1, 12, 0.5f, true);
		LowerRenderer->CreateAnimation("Right_Lower_IdleJump", "Right_Lower.bmp", 13, 18, 0.5f, true);

		UpperRenderer->CreateAnimation("Right_Upper_Idle", "Right_Upper.bmp", 0, 3, 0.5f, true);
		UpperRenderer->CreateAnimation("Right_Upper_Move", "Right_Upper.bmp", 3, 15, 0.5f, true);
		UpperRenderer->CreateAnimation("Right_Upper_IdleJump", "Right_Upper.bmp", 16, 21, 0.5f, true);
		UpperRenderer->CreateAnimation("Right_Upper_MoveJump", "Right_Upper.bmp", 22, 27, 0.5f, true);
		// UpperRenderer->CreateAnimation("Right_Upper", "Right_Upper.bmp", )
		
		//MainRenderer->ChangeAnimation("Right_Lower_Idle");
		//MainRenderer->ChangeAnimation("Right_Lower");

		//LowerRenderer->ChangeAnimation("Right_Lower_Idle");
		//UpperRenderer->ChangeAnimation("Right_Upper_Idle");
		// MainRenderer->SetRenderScaleToTexture();

		// UpperRenderer->GetActor()->SetPos({ LowerRenderer->GetActor()->GetPos().X, LowerRenderer->GetActor()->GetPos().Y + 10.0f });
		LowerRenderer->GetActor()->SetPos({ 25, 25 });

		UpperRenderer->SetRenderPos({ 5, -20 });
		

		
		
	}
	{
	//	GameEngineRenderer* Ptr = CreateUIRenderer(300);
		
	}


	ChangeState(PlayerState::Idle);
	//ChangeState(PlayerState::Move);
	Dir = PlayerDir::Right;
	
}

void Player::Update(float _Delta)
{
	//CameraFocus();

	StateUpdate(_Delta);
}

//void Player::Render()
//{
//
//}

void Player::Release()
{

}

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
	default:
		break;
	}
}

void Player::DirCheck()
{
	if (true == GameEngineInput::IsFree('A') && true == GameEngineInput::IsFree('D'))
	{
		return;
	}

	// A가 눌렸을때 왼쪽을 바라보게
	if (true == GameEngineInput::IsDown('A') || true == GameEngineInput::IsFree('D'))
	{
		Dir = PlayerDir::Left;
		ChangeAnimationState(CurState);
		return;
	}

	// D가 눌렸을때 오른쪽을 바라보게
	if (true == GameEngineInput::IsFree('A') || true == GameEngineInput::IsDown('D'))
	{
		Dir = PlayerDir::Right;
		ChangeAnimationState(CurState);
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
		UpperAnimationName = "Right_Upper_";
		break;
	case PlayerDir::Left:
		LowerAnimationName = "Left_Lower_";
		UpperAnimationName = "Left_Upper_";
		break;
	default:
		break;
	}

	LowerAnimationName += _State;
	UpperAnimationName += _State;
	CurState = _State;

	LowerRenderer->ChangeAnimation(LowerAnimationName);
	UpperRenderer->ChangeAnimation(UpperAnimationName);
}

void Player::Gravity(float _Delta)
{
	if (false == IsGravity)
	{
		return;
	}

	GravityVector += float4::DOWN * GravityPower * _Delta;

	AddPos(GravityVector);
}
