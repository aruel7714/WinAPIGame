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

	if (false == ResourcesManager::GetInst().IsLoadTexture("Right_Pistol_Upper.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Pistol_Upper.bmp"), 5, 15);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Left_Pistol_Upper.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Pistol_Upper.bmp"), 5, 15);
	}

	//if (false == ResourcesManager::GetInst().IsLoadTexture("Right_Upper.bmp"))
	//{
	//	GameEnginePath FilePath;

	//	FilePath.SetCurrentPath();

	//	FilePath.MoveParentToExistsChild("ContentsResources");

	//	FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

	//	ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Upper.bmp"), 5, 6);
	//}

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
		LowerRenderer->CreateAnimation("Right_Lower_Move", "Right_Lower.bmp", 1, 12, 0.03f, true);
		//LowerRenderer->CreateAnimation("Right_Lower_Move", "Right_Lower.bmp", 1, 12, 0.5f, true);
		LowerRenderer->CreateAnimation("Right_Lower_IdleJump", "Right_Lower.bmp", 13, 18, 0.2f, false);
		LowerRenderer->CreateAnimation("Right_Lower_MoveJump", "Right_Lower.bmp", 19, 24, 0.2f, false);

		LowerRenderer->CreateAnimation("Left_Lower_Idle", "Left_Lower.bmp", 0, 0, 0.1f, true);
		LowerRenderer->CreateAnimation("Left_Lower_Move", "Left_Lower.bmp", 1, 12, 0.03f, true);
		LowerRenderer->CreateAnimation("Left_Lower_IdleJump", "Left_Lower.bmp", 13, 18, 0.2f, false);
		LowerRenderer->CreateAnimation("Left_Lower_MoveJump", "Left_Lower.bmp", 19, 24, 0.2f, false);

		UpperRenderer->CreateAnimation("Right_Pistol_Upper_Idle", "Right_Pistol_Upper.bmp", 0, 5, 0.1f, true);
		// UpperRenderer->CreateAnimation("Right_Pistol_Upper_Move", "Right_Pistol_Upper.bmp", 6, 17, 0.03f, true);
		UpperRenderer->CreateAnimation("Right_Pistol_Upper_Move", "Right_Pistol_Upper.bmp", 6, 17, 0.03f, true);
		UpperRenderer->CreateAnimation("Right_Pistol_Upper_IdleJump", "Right_Pistol_Upper.bmp", 18, 23, 0.2f, false);
		UpperRenderer->CreateAnimation("Right_Pistol_Upper_MoveJump", "Right_Pistol_Upper.bmp", 24, 29, 0.2f, false);
		UpperRenderer->CreateAnimation("Right_Pistol_Upper_Fire", "Right_Pistol_Upper.bmp", 30, 39, 0.05f, false);
		UpperRenderer->CreateAnimation("Right_Pistol_Upper_Granade", "Right_Pistol_Upper.bmp", 40, 45, 0.5f, false);

		UpperRenderer->CreateAnimation("Left_Pistol_Upper_Idle", "Left_Pistol_Upper.bmp", 0, 5, 0.1f, true);
		UpperRenderer->CreateAnimation("Left_Pistol_Upper_Move", "Left_Pistol_Upper.bmp", 6, 17, 0.03f, true);
		UpperRenderer->CreateAnimation("Left_Pistol_Upper_IdleJump", "Left_Pistol_Upper.bmp", 18, 23, 0.2f, false);
		UpperRenderer->CreateAnimation("Left_Pistol_Upper_MoveJump", "Left_Pistol_Upper.bmp", 24, 29, 0.2f, false);
		UpperRenderer->CreateAnimation("Left_Pistol_Upper_Fire", "Left_Pistol_Upper.bmp", 30, 39, 0.05f, false);
		UpperRenderer->CreateAnimation("Left_Pistol_Upper_Granade", "Left_Pistol_Upper.bmp", 40, 45, 0.5f, false);
		

		// UpperRenderer->CreateAnimation("Right_Upper_Idle", "Right_Upper.bmp", 0, 3, 0.5f, true);
		// UpperRenderer->CreateAnimation("Right_Upper", "Right_Upper.bmp", )
		
		//MainRenderer->ChangeAnimation("Right_Lower_Idle");
		//MainRenderer->ChangeAnimation("Right_Lower");

		//LowerRenderer->ChangeAnimation("Right_Lower_Idle");
		//UpperRenderer->ChangeAnimation("Right_Upper_Idle");
		// MainRenderer->SetRenderScaleToTexture();

		// UpperRenderer->GetActor()->SetPos({ LowerRenderer->GetActor()->GetPos().X, LowerRenderer->GetActor()->GetPos().Y + 10.0f });
		LowerRenderer->GetActor()->SetPos({ 3000, 400 });

		// UpperRenderer->SetRenderPos({ 20, -60 });
		// 33px
		UpperRenderer->SetRenderPos( { -40, -92 } );
		
		
	}
	{
	//	GameEngineRenderer* Ptr = CreateUIRenderer(300);
		
	}


	ChangeState(PlayerState::Idle);
	//ChangeState(PlayerState::Move);
	Dir = PlayerDir::Right;
	
	int a = 0;
}

void Player::Update(float _Delta)
{
	CameraFocus();

	StateUpdate(_Delta);
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
	case PlayerState::IdleJump:
		return IdleJumpUpdate(_Delta);
	case PlayerState::MoveJump:
		return MoveJumpUpdate(_Delta);
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
		ChangeAnimationState(CurState);
		return;
	}

	// D가 눌렸을때 오른쪽을 바라보게
	// 오른쪽 방향키가 눌렸을때 오른쪽을 바라보게
	// if (true == GameEngineInput::IsFree('A') || true == GameEngineInput::IsDown('D'))
	if(true == GameEngineInput::IsFree(VK_LEFT) || true == GameEngineInput::IsDown(VK_RIGHT))
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

	LowerRenderer->ChangeAnimation(LowerAnimationName);
	UpperRenderer->ChangeAnimation(UpperAnimationName);
}

void Player::ChangeLowerAnimationState(const std::string& _State)
{
	std::string LowerAnimationName;

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

	LowerRenderer->ChangeAnimation(LowerAnimationName);
}
void Player::ChangeUpperAnimationState(const std::string& _State)
{
	std::string UpperAnimationName;

	switch (Dir)
	{
	case PlayerDir::Right:
		UpperAnimationName = "Right_Pistol_Upper_";
		break;
	case PlayerDir::Left:
		UpperAnimationName = "Left_Pistol_Upper_";
		break;
	default:
		break;
	}

	UpperAnimationName += _State;

	UpperRenderer->ChangeAnimation(UpperAnimationName);
}
