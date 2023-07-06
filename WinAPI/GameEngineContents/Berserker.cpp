#include "Berserker.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "ContentsEnum.h"
#include "Player.h"

Berserker::Berserker()
{
}

Berserker::~Berserker()
{
}

void Berserker::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Berserker.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Berserker.bmp"), 5, 6);
	}
	if (nullptr == GameEngineSound::FindSound("BerserkerDeathSound.wav"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Sound\\");
		GameEngineSound::SoundLoad(FilePath.PlusFilePath("BerserkerDeathSound.wav"));
	}

	{
		BerserkerRenderer = CreateRenderer(RenderOrder::Enemy);

		BerserkerRenderer->CreateAnimation("Berserker_SitIdle1", "Berserker.bmp", 0, 3, 0.1f, false);
		BerserkerRenderer->CreateAnimation("Berserker_SitIdle2", "Berserker.bmp", 2, 1, 0.1f, false);
		BerserkerRenderer->CreateAnimation("Berserker_StandIdle1", "Berserker.bmp", 4, 7, 0.3f, false);
		BerserkerRenderer->CreateAnimation("Berserker_StandIdle2", "Berserker.bmp", 6, 5, 0.3f, false);
		BerserkerRenderer->CreateAnimation("Berserker_Move", "Berserker.bmp", 8, 13, 0.05f, true);
		BerserkerRenderer->CreateAnimation("Berserker_Attack", "Berserker.bmp", 14, 19, 0.05f, true);
		BerserkerRenderer->CreateAnimation("Berserker_Death", "Berserker.bmp", 20, 28, 0.01f, false);
	}

	{
		BerserkerCollision = CreateCollision(CollisionOrder::EnemyCollision);

		BerserkerCollision->SetCollisionScale({ 100, 120 });
		BerserkerCollision->SetCollisionType(CollisionType::Rect);
		BerserkerCollision->SetCollisionPos({ 0, -60 });
	}

	{
		BerserkerMeleeAttCollision = CreateCollision(CollisionOrder::EnemyMeleeCollision);

		BerserkerMeleeAttCollision->SetCollisionScale({ 160, 120 });
		BerserkerMeleeAttCollision->SetCollisionType(CollisionType::Rect);
		BerserkerMeleeAttCollision->SetCollisionPos({ -30, -60 });
	}


	//BerserkerRenderer->GetActor()->SetPos({ 12500, 860 });

	ChangeState(BerserkerState::StandIdle);
}

void Berserker::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void Berserker::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	CollisionData Data;

	Data.Pos = ActorCameraPos();

	Data.Scale = { 5, 5 };

	Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
}

void Berserker::ChangeState(BerserkerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BerserkerState::Spawn:
			SpawnStart();
			break;
		case BerserkerState::SitIdle:
			SitIdleStart();
			break;
		case BerserkerState::StandIdle:
			StandIdleStart();
			break;
		case BerserkerState::Move:
			MoveStart();
			break;
		case BerserkerState::Attack:
			AttackStart();
			break;
		case BerserkerState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}

void Berserker::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BerserkerState::Spawn:
		return SpawnUpdate(_Delta);
	case BerserkerState::SitIdle:
		return SitIdleUpdate(_Delta);
	case BerserkerState::StandIdle:
		return StandIdleUpdate(_Delta);
	case BerserkerState::Move:
		return MoveUpdate(_Delta);
	case BerserkerState::Attack:
		return AttackUpdate(_Delta);
	case BerserkerState::Death:
		return DeathUpdate(_Delta);
	default:
		break;
	}
}

void Berserker::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName;

	AnimationName = "Berserker_";
	AnimationName += _State;

	BerserkerRenderer->ChangeAnimation(AnimationName);
}

void Berserker::SpawnStart()
{
	ResetLiveTime();
	PrevState = BerserkerState::Spawn;
	ChangeAnimationState("Move");
}
void Berserker::SpawnUpdate(float _Delta)
{
	float Speed = 200.0f;
	float4 MovePos = { -Speed * _Delta, 0.0f };
	AddPos(MovePos);

	if (3.0f <= GetLiveTime())
	{
		ResetLiveTime();
		ChangeState(BerserkerState::SitIdle);
	}
}

void Berserker::SitIdleStart()
{
	ChangeAnimationState("SitIdle1");
}
void Berserker::SitIdleUpdate(float _Delta)
{
	if (PrevState == BerserkerState::Spawn && 2.0f <= GetLiveTime())
	{
		ChangeState(BerserkerState::Move);
	}


	if (BerserkerRenderer->IsAnimationEnd())
	{
		if (BerserkerRenderer->IsAnimation("Berserker_SitIdle1"))
		{
			ChangeAnimationState("SitIdle2");
		}
		else if (BerserkerRenderer->IsAnimation("Berserker_SitIdle2"))
		{
			ChangeAnimationState("SitIdle1");
		}
	}
}

void Berserker::StandIdleStart()
{
	ChangeAnimationState("StandIdle1");
}
void Berserker::StandIdleUpdate(float _Delta)
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
	if (BerserkerRenderer->IsAnimationEnd())
	{
		if (BerserkerRenderer->IsAnimation("Berserker_StandIdle1"))
		{
			ChangeAnimationState("StandIdle2");
		}
		else if (BerserkerRenderer->IsAnimation("Berserker_StandIdle2"))
		{
			ChangeAnimationState("StandIdle1");
		}
	}
}

void Berserker::MoveStart()
{
	ResetLiveTime();
	ChangeAnimationState("Move");
}
void Berserker::MoveUpdate(float _Delta)
{
	DeathCollisionCheck();
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
	float Speed = 200.0f;
	float4 MovePos = float4::ZERO;
	MovePos = { -Speed * _Delta, 0.0f };

	AddPos(MovePos);

	if (300.0f >= BerserkerRenderer->GetActor()->GetPos().X - Player::GetMainPlayer()->GetPos().X &&
		0.0f <= BerserkerRenderer->GetActor()->GetPos().X - Player::GetMainPlayer()->GetPos().X)
	{
		
		ChangeState(BerserkerState::Attack);
	}

	if (5.0f <= GetLiveTime())
	{
		ChangeState(BerserkerState::Death);
	}
}

void Berserker::AttackStart()
{
	ChangeAnimationState("Attack");
}
void Berserker::AttackUpdate(float _Delta)
{
	DeathCollisionCheck();
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
	float Speed = 200.0f;
	float4 MovePos = float4::ZERO;
	MovePos = { -Speed * _Delta, 0.0f };

	AddPos(MovePos);

	std::vector<GameEngineCollision*> _Collision;
	if (true == BerserkerMeleeAttCollision->Collision(CollisionOrder::PlayerCollision, _Collision
		, CollisionType::Rect
		, CollisionType::Rect
	))
	{
		for (size_t i = 0; i < _Collision.size(); i++)
		{
			GameEngineCollision* Collision = _Collision[i];

			GameEngineActor* Actor = Collision->GetActor();

		}
		Player::GetMainPlayer()->ChangeLowerState(PlayerLowerState::MeleeDeath);
	}

	if (0.0f >= BerserkerRenderer->GetActor()->GetPos().X - Player::GetMainPlayer()->GetPos().X)
	{
		ChangeState(BerserkerState::Move);
	}
}

void Berserker::DeathStart()
{
	GravityReset();
	BerserkerDeath = true;
	float4 GravityDir = (float4::UP);
	GravityDir += (float4::RIGHT);
	SetGravityVector(GravityDir * 500.0f);
	ChangeAnimationState("Death");
}
void Berserker::DeathUpdate(float _Delta)
{
	{
		Gravity(_Delta);
		// 발밑의 색
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		// 그 색이 흰색이라면 중력 적용(아래로 떨어지기)
		if (RGB(255, 255, 255) == Color)
		{

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

	
}
void Berserker::DeathCollisionCheck()
{
	std::vector<GameEngineCollision*> _Collision;
	if (true == BerserkerCollision->Collision(CollisionOrder::BulletCollision, _Collision
		, CollisionType::Rect
		, CollisionType::Rect
	))
	{
		for (size_t i = 0; i < _Collision.size(); i++)
		{
			GameEngineCollision* Collision = _Collision[i];

			GameEngineActor* Actor = Collision->GetActor();
			Collision->Off();
		}
		BerserkerCollision->Off();
		BerserkerMeleeAttCollision->Off();
		Sound = GameEngineSound::SoundPlay("BerserkerDeathSound.wav");
		ChangeState(BerserkerState::Death);
	}
	else if (true == BerserkerCollision->Collision(CollisionOrder::PlayerMeleeCollision, _Collision
		, CollisionType::Rect
		, CollisionType::Rect
	))
	{
		for (size_t i = 0; i < _Collision.size(); i++)
		{
			GameEngineCollision* Collision = _Collision[i];

			GameEngineActor* Actor = Collision->GetActor();

		}
		Sound = GameEngineSound::SoundPlay("BerserkerDeathSound.wav");
		if (Player::GetMainPlayer()->UpperRenderer->IsAnimation("Right_Pistol_Upper_MeleeAtt1") ||
			Player::GetMainPlayer()->UpperRenderer->IsAnimation("Right_Pistol_Upper_MeleeAtt2") ||
			Player::GetMainPlayer()->UpperRenderer->IsAnimation("Left_Pistol_Upper_MeleeAtt1") ||
			Player::GetMainPlayer()->UpperRenderer->IsAnimation("Left_Pistol_Upper_MeleeAtt2") ||
			Player::GetMainPlayer()->UpperRenderer->IsAnimation("Right_Rifle_Upper_MeleeAtt1") ||
			Player::GetMainPlayer()->UpperRenderer->IsAnimation("Right_Rifle_Upper_MeleeAtt2") ||
			Player::GetMainPlayer()->UpperRenderer->IsAnimation("Left_Rifle_Upper_MeleeAtt1") ||
			Player::GetMainPlayer()->UpperRenderer->IsAnimation("Left_Rifle_Upper_MeleeAtt2")
			)
		{
			if (Player::GetMainPlayer()->UpperRenderer->IsAnimationEnd())
			{
				BerserkerCollision->Off();
				BerserkerMeleeAttCollision->Off();
				ChangeState(BerserkerState::Death);
			}
		}
	}
}