#include "Arabian.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"

std::list<Arabian*> Arabian::AllArabian;

Arabian::Arabian()
{
	AllArabian.push_back(this);
}

Arabian::~Arabian()
{
}

void Arabian::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Left_Arabian_All.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\");
		
		// ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Left_Arabian.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Arabian_All.bmp"), 5, 14);
	}

	{
		ArabianRenderer = CreateRenderer(RenderOrder::Enemy);
		
		ArabianRenderer->CreateAnimation("Left_Arabian_Idle1", "Left_Arabian_All.bmp", 0, 5, 0.1f, false);
		ArabianRenderer->CreateAnimation("Left_Arabian_Idle2", "Left_Arabian_All.bmp", 4, 1, 0.1f, false);
		ArabianRenderer->CreateAnimation("Left_Arabian_Ready1", "Left_Arabian_All.bmp", 6, 9, 0.08f, false);
		ArabianRenderer->CreateAnimation("Left_Arabian_Ready2", "Left_Arabian_All.bmp", 8, 7, 0.08f, false);
		ArabianRenderer->CreateAnimation("Left_Arabian_Move", "Left_Arabian_All.bmp", 10, 21, 1.0f, true);
		ArabianRenderer->CreateAnimation("Left_Arabian_JumpReady", "Left_Arabian_All.bmp", 22, 26, 0.05f, false);
		ArabianRenderer->CreateAnimation("Left_Arabian_Jump", "Left_Arabian_All.bmp", 27, 30, 0.05f, false);
		
		ArabianRenderer->CreateAnimation("Left_Arabian_BackStep", "Left_Arabian_All.bmp", 31, 34, 0.1f, false);
		ArabianRenderer->CreateAnimation("Left_Arabian_AttackReady", "Left_Arabian_All.bmp", 35, 38, 0.1f, true);
		ArabianRenderer->CreateAnimation("Left_Arabian_MeleeAttack", "Left_Arabian_All.bmp", 39, 45, 0.05f, true);
		ArabianRenderer->CreateAnimation("Left_Arabian_RangeAttack", "Left_Arabian_All.bmp", 46, 64, 0.5f, true);


		ArabianRenderer->GetActor()->SetPos({ 3200, 850 });
	}

	{
		ArabianCollision = CreateCollision(CollisionOrder::EnemyCollision);

		ArabianCollision->SetCollisionScale({ 80, 140 });
		ArabianCollision->SetCollisionType(CollisionType::Rect);
		ArabianCollision->SetCollisionPos({ 0, -70 });
	}

	ChangeState(ArabianState::Idle);
	//ChangeState(ArabianState::Ready);
}

void Arabian::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void Arabian::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	CollisionData Data;

	Data.Pos = ActorCameraPos();

	Data.Scale = { 5,5 };

	Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
}

void Arabian::ChangeState(ArabianState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case ArabianState::Idle:
			IdleStart();
			break;
		case ArabianState::Ready:
			ReadyStart();
			break;
		case ArabianState::Move:
			MoveStart();
			break;
		case ArabianState::JumpReady:
			JumpReadyStart();
			break;
		case ArabianState::Jump:
			JumpStart();
			break;
		case ArabianState::BackStep:
			BackStepStart();
			break;
		case ArabianState::AttackReady:
			AttackReadyStart();
			break;
		case ArabianState::MeleeAttack:
			MeleeAttackStart();
			break;
		case ArabianState::RangeAttack:
			RangeAttackStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}

void Arabian::StateUpdate(float _Delta)
{
	switch (State)
	{
	case ArabianState::Idle:
		return IdleUpdate(_Delta);
	case ArabianState::Ready:
		return ReadyUpdate(_Delta);
	case ArabianState::Move:
		return MoveUpdate(_Delta);
	case ArabianState::JumpReady:
		return JumpReadyUpdate(_Delta);
	case ArabianState::Jump:
		return JumpUpdate(_Delta);
	case ArabianState::BackStep:
		return BackStepUpdate(_Delta);
	case ArabianState::AttackReady:
		return AttackReadyUpdate(_Delta);
	case ArabianState::MeleeAttack:
		return MeleeAttackUpdate(_Delta);
	case ArabianState::RangeAttack:
		return RangeAttackUpdate(_Delta);
	default:
		break;
	}
}

void Arabian::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName;

	switch (Dir)
	{
	case ArabianDir::Left:
		AnimationName = "Left_Arabian_";
		break;
	case ArabianDir::Right:
		AnimationName = "Right_Arabian_";
		break;
	default:
		break;
	}

	AnimationName += _State;

	ArabianRenderer->ChangeAnimation(AnimationName);
}


////////////// Arabian State Function ///////////////
void Arabian::IdleStart()
{
	ChangeAnimationState("Idle1");
}
void Arabian::IdleUpdate(float _Delta)
{
	{
		// �߹��� ��
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		// �� ���� ����̶�� �߷� ����(�Ʒ��� ��������)
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);
		}
		// �װ� �ƴ϶��
		else
		{
			// �� �� ���� �� ����
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			// �� ���� ���� ����� �ƴ϶�� ���� �̵�
			while (CheckColor != RGB(255, 255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}

			GravityReset();
		}
	}

	if (ArabianRenderer->IsAnimationEnd())
	{
		if (ArabianRenderer->IsAnimation("Left_Arabian_Idle1") || ArabianRenderer->IsAnimation("Right_Arabian_Idle1"))
		{
			ChangeAnimationState("Idle2");
		}
		else if (ArabianRenderer->IsAnimation("Left_Arabian_Idle2") || ArabianRenderer->IsAnimation("Right_Arabian_Idle2"))
		{
			//ChangeAnimationState("Idle1");
			ChangeState(ArabianState::JumpReady);
		}
	}
}

void Arabian::ReadyStart()
{
	ChangeAnimationState("Ready1");
}
void Arabian::ReadyUpdate(float _Delta)
{
	
	if (ArabianRenderer->IsAnimation("Left_Arabian_Ready1") || ArabianRenderer->IsAnimation("Right_Arabian_Ready1"))
	{
		AddPos(float4::LEFT * 0.25);
		if (ArabianRenderer->IsAnimationEnd())
		{
			ChangeAnimationState("Ready2");
		}
	}
	else if (ArabianRenderer->IsAnimation("Left_Arabian_Ready2") || ArabianRenderer->IsAnimation("Right_Arabian_Ready2"))
	{
		AddPos(float4::RIGHT * 0.5);
		if (ArabianRenderer->IsAnimationEnd())
		{
			ChangeAnimationState("Ready1");
		}
	}
}

void Arabian::MoveStart()
{
	ChangeAnimationState("Move");
}
void Arabian::MoveUpdate(float _Delta)
{
	
}

void Arabian::JumpReadyStart()
{
	ChangeAnimationState("JumpReady");
}
void Arabian::JumpReadyUpdate(float _Delta)
{
	if (ArabianRenderer->IsAnimationEnd())
	{
		ChangeState(ArabianState::Jump);
	}
}

void Arabian::JumpStart()
{
	if (Dir == ArabianDir::Left)
	{
		GravityReset();
		float4 GravityDir = (float4::UP);
		GravityDir += (float4::LEFT * 0.5f);
		SetGravityVector(GravityDir * 300.0f);
	}
	else if (Dir == ArabianDir::Right)
	{
		GravityReset();
		float4 GravityDir = (float4::UP);
		GravityDir += (float4::RIGHT);
		SetGravityVector(GravityDir * 100.0f);
	}
	ChangeAnimationState("Jump");
}
void Arabian::JumpUpdate(float _Delta)
{
	Gravity(_Delta);

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (Color != RGB(255, 255, 255))
		{
			if (ArabianRenderer->IsAnimationEnd())
			{
				ChangeState(ArabianState::Idle);
			}
		}
	}
		

	
}

void Arabian::BackStepStart()
{
	if (Dir == ArabianDir::Left)
	{
		float4 GravityDir = (float4::UP);
		GravityDir += (float4::RIGHT);
		SetGravityVector(GravityDir * 500.0f);
	}
	else if (Dir == ArabianDir::Right)
	{
		float4 GravityDir = (float4::UP);
		GravityDir += (float4::LEFT);
		SetGravityVector(GravityDir * 100.0f);
	}
	ChangeAnimationState("BackStep");
}
void Arabian::BackStepUpdate(float _Delta)
{
	Gravity(_Delta);

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (Color != RGB(255, 255, 255))
		{
			ChangeState(ArabianState::Idle);
		}
	}
	
}

void Arabian::AttackReadyStart()
{
	ChangeAnimationState("AttackReady");
}
void Arabian::AttackReadyUpdate(float _Delta)
{
	if (ArabianRenderer->IsAnimationEnd())
	{
		//ChangeState(ArabianState::MeleeAttack);
		ChangeState(ArabianState::RangeAttack);
	}
}

void Arabian::MeleeAttackStart()
{
	ChangeAnimationState("MeleeAttack");
}
void Arabian::MeleeAttackUpdate(float _Delta)
{
	if (ArabianRenderer->IsAnimationEnd())
	{
		ChangeState(ArabianState::Idle);
	}
}

void Arabian::RangeAttackStart()
{
	ChangeAnimationState("RangeAttack");
}
void Arabian::RangeAttackUpdate(float _Delta)
{
	if (ArabianRenderer->IsAnimationEnd())
	{
		ChangeState(ArabianState::Idle);
	}
}