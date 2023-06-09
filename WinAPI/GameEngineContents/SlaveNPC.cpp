#include "SlaveNPC.h"
#include <list>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnum.h"
#include "Player.h"
#include "HeavyMachineGun.h"


std::list<SlaveNPC*> SlaveNPC::AllSlave;

SlaveNPC::SlaveNPC()
{
	AllSlave.push_back(this);
}

SlaveNPC::~SlaveNPC()
{
}

void SlaveNPC::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Left_Slave.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\NPC\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Slave.bmp"), 5, 11);
	}
	if (false == ResourcesManager::GetInst().IsLoadTexture("Right_Slave.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\NPC\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_Slave.bmp"), 5, 11);
	}

	if (nullptr == GameEngineSound::FindSound("thankyouSound.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("thankyouSound.wav"));
	}

	{
		SlaveRenderer = CreateRenderer(RenderOrder::NPC);

		SlaveRenderer->CreateAnimation("Left_Slave_CatchOn1", "Left_Slave.bmp", 0, 4, 0.08f, false);
		SlaveRenderer->CreateAnimation("Left_Slave_CatchOn2", "Left_Slave.bmp", 3, 1, 0.08f, false);
		SlaveRenderer->CreateAnimation("Left_Slave_CatchOff", "Left_Slave.bmp", 5, 8, 0.08f, false);
		SlaveRenderer->CreateAnimation("Left_Slave_Move", "Left_Slave.bmp", 9, 20, 0.1f, true);
		SlaveRenderer->CreateAnimation("Left_Slave_Gift", "Left_Slave.bmp", 21, 31, 0.1f, false);
		SlaveRenderer->CreateAnimation("Left_Slave_Greet", "Left_Slave.bmp", 32, 45, 0.08f, false);
		SlaveRenderer->CreateAnimation("Left_Slave_Run", "Left_Slave.bmp", 46, 53, 0.08f, true);

		SlaveRenderer->CreateAnimation("Right_Slave_CatchOn", "Right_Slave.bmp", 0, 4, 1.0f, true);
		SlaveRenderer->CreateAnimation("Right_Slave_CatchOff", "Right_Slave.bmp", 5, 8, 1.0f, true);
		SlaveRenderer->CreateAnimation("Right_Slave_Move", "Right_Slave.bmp", 9, 20, 0.1f, true);
		SlaveRenderer->CreateAnimation("Right_Slave_Gift", "Right_Slave.bmp", 21, 31, 1.0f, true);
		SlaveRenderer->CreateAnimation("Right_Slave_Greet", "Right_Slave.bmp", 32, 45, 1.0f, true);
		SlaveRenderer->CreateAnimation("Right_Slave_Run", "Right_Slave.bmp", 46, 53, 1.0f, true);
	}

	{
		SlaveCatchOnCollision = CreateCollision(CollisionOrder::EnemyCollision);

		SlaveCatchOnCollision->SetCollisionScale({ 80, 110 });
		SlaveCatchOnCollision->SetCollisionType(CollisionType::Rect);
		SlaveCatchOnCollision->SetCollisionPos({ 0, -55 });
	}

	{
		SlaveCatchOffCollision = CreateCollision(CollisionOrder::NPCCollision);

		SlaveCatchOffCollision->SetCollisionScale({ 80, 110 });
		SlaveCatchOffCollision->SetCollisionType(CollisionType::Rect);
		SlaveCatchOffCollision->SetCollisionPos({ 0, -55 });
	}

	ChangeState(SlaveState::CatchOn);
	
	SlaveCatchOffCollision->Off();
}

void SlaveNPC::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void SlaveNPC::SetDir(SlaveDir _Dir)
{
	Dir = _Dir;
}

void SlaveNPC::ChangeState(SlaveState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case SlaveState::CatchOn:
			CatchOnStart();
			break;
		case SlaveState::CatchOff:
			CatchOffStart();
			break;
		case SlaveState::Move:
			MoveStart();
			break;
		case SlaveState::Gift:
			GiftStart();
			break;
		case SlaveState::Greet:
			GreetStart();
			break;
		case SlaveState::Run:
			RunStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void SlaveNPC::StateUpdate(float _Delta)
{
	switch (State)
	{
	case SlaveState::CatchOn:
		return CatchOnUpdate(_Delta);
	case SlaveState::CatchOff:
		return CatchOffUpdate(_Delta);
	case SlaveState::Move:
		return MoveUpdate(_Delta);
	case SlaveState::Gift:
		return GiftUpdate(_Delta);
	case SlaveState::Greet:
		return GreetUpdate(_Delta);
	case SlaveState::Run:
		return RunUpdate(_Delta);
	default:
		break;
	}
}

void SlaveNPC::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName;

	switch (Dir)
	{
	case SlaveDir::Left:
		AnimationName = "Left_Slave_";
		break;
	case SlaveDir::Right:
		AnimationName = "Right_Slave_";
		break;
	default:
		break;
	}

	AnimationName += _State;

	SlaveRenderer->ChangeAnimation(AnimationName);
}

void SlaveNPC::CatchOnStart()
{
	ChangeAnimationState("CatchOn1");
}
void SlaveNPC::CatchOnUpdate(float _Delta)
{
	{
		// 발밑의 색
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		// 그 색이 흰색이라면 중력 적용(아래로 떨어지기)
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);
		}
		// 그게 아니라면
		else
		{
			// 내 발 위의 색 조사
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			// 발 위의 색이 흰색이 아니라면 위로 이동
			while (CheckColor != RGB(255, 255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}

			GravityReset();
		}
	}

	std::vector<GameEngineCollision*> _Collision;
	if (true == SlaveCatchOnCollision->Collision(CollisionOrder::BulletCollision, _Collision
		, CollisionType::Rect
		, CollisionType::Rect
	))
	{
		for (size_t i = 0; i < _Collision.size(); i++)
		{
			GameEngineCollision* Collision = _Collision[i];

			GameEngineActor* Actor = Collision->GetActor();
			Collision->Death();
			SlaveCatchOnCollision->Off();
		}
		ChangeState(SlaveState::CatchOff);
	}
	else if (true == SlaveCatchOnCollision->Collision(CollisionOrder::PlayerMeleeCollision, _Collision
		, CollisionType::Rect
		, CollisionType::Rect
	))
	{
		for (size_t i = 0; i < _Collision.size(); i++)
		{
			GameEngineCollision* Collision = _Collision[i];

			GameEngineActor* Actor = Collision->GetActor();

		}
		if (Player::GetMainPlayer()->UpperRenderer->IsAnimation("Right_Pistol_Upper_MeleeAtt1") ||
			Player::GetMainPlayer()->UpperRenderer->IsAnimation("Right_Pistol_Upper_MeleeAtt2") ||
			Player::GetMainPlayer()->UpperRenderer->IsAnimation("Left_Pistol_Upper_MeleeAtt1") ||
			Player::GetMainPlayer()->UpperRenderer->IsAnimation("Left_Pistol_Upper_MeleeAtt2") ||
			Player::GetMainPlayer()->UpperRenderer->IsAnimation("Right_Rifle_Upper_MeleeAtt1") || 
			Player::GetMainPlayer()->UpperRenderer->IsAnimation("Right_Rifle_Upper_MeleeAtt2") || 
			Player::GetMainPlayer()->UpperRenderer->IsAnimation("Left_Rifle_Upper_MeleeAtt1") || 
			Player::GetMainPlayer()->UpperRenderer->IsAnimation("Left_Rifle_Upper_MeleeAtt2"))
		{
			if (Player::GetMainPlayer()->UpperRenderer->IsAnimationEnd())
			{
				ChangeState(SlaveState::CatchOff);
			}
		}
	}

	if (SlaveRenderer->IsAnimationEnd())
	{
		if (SlaveRenderer->IsAnimation("Left_Slave_CatchOn1"))
		{
			ChangeAnimationState("CatchOn2");
		}
		else if (SlaveRenderer->IsAnimation("Left_Slave_CatchOn2"))
		{
			ChangeAnimationState("CatchOn1");
		}
	}

}

void SlaveNPC::CatchOffStart()
{
	ChangeAnimationState("CatchOff");
}
void SlaveNPC::CatchOffUpdate(float _Delta)
{
	if (SlaveRenderer->IsAnimationEnd())
	{
		ChangeState(SlaveState::Move);
	}
}

void SlaveNPC::MoveStart()
{
	SlaveCatchOffCollision->On();
	ChangeAnimationState("Move");
}
void SlaveNPC::MoveUpdate(float _Delta)
{
	std::vector<GameEngineCollision*> _Collision;
	if (true == SlaveCatchOffCollision->Collision(CollisionOrder::PlayerCollision, _Collision
		, CollisionType::Rect
		, CollisionType::Rect
	))
	{
		for (size_t i = 0; i < _Collision.size(); i++)
		{
			GameEngineCollision* Collision = _Collision[i];

			GameEngineActor* Actor = Collision->GetActor();
		}
		Dir = SlaveDir::Left;
		ChangeState(SlaveState::Gift);
	}

	if (SlaveRenderer->IsAnimation("Left_Slave_Move"))
	{
		AddPos(float4::LEFT * 0.4f);
		if (SlaveRenderer->IsAnimationEnd())
		{
			SetDir(SlaveDir::Right);
			ChangeAnimationState("Move");
		}
	}
	else if (SlaveRenderer->IsAnimation("Right_Slave_Move"))
	{
		AddPos(float4::RIGHT * 0.4f);
		if (SlaveRenderer->IsAnimationEnd())
		{
			SetDir(SlaveDir::Left);
			ChangeAnimationState("Move");
		}
	}
}

void SlaveNPC::GiftStart()
{
	SlaveCatchOffCollision->Off();
	Sound = GameEngineSound::SoundPlay("thankyouSound.wav");
	ChangeAnimationState("Gift");
}
void SlaveNPC::GiftUpdate(float _Delta)
{

	if (SlaveRenderer->IsAnimationEnd())
	{
		
		ChangeState(SlaveState::Greet);
	}
}

void SlaveNPC::GreetStart()
{

	ChangeAnimationState("Greet");
}
void SlaveNPC::GreetUpdate(float _Delta)
{
	if (SlaveRenderer->IsAnimationEnd())
	{
		ChangeState(SlaveState::Run);
	}
}

void SlaveNPC::RunStart()
{ 
	ResetLiveTime();
	ChangeAnimationState("Run");
}
void SlaveNPC::RunUpdate(float _Delta)
{
	AddPos(float4::LEFT * 3.0f);
	
	if (3.0f <= GetLiveTime()) {
		SlaveRenderer->Off();
	}
}