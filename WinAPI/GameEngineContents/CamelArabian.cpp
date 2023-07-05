#include "CamelArabian.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "EnemyBullet.h"

CamelArabian::CamelArabian()
{
}

CamelArabian::~CamelArabian()
{
}

void CamelArabian::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("CamelArabian_Lower.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("CamelArabian_Lower.bmp"), 5, 5);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("CamelArabian_Lower_Death.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("CamelArabian_Lower_Death.bmp"), 5, 3);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Left_CamelArabian_Upper.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_CamelArabian_Upper.bmp"), 5, 6);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Left_CamelArabian_Upper_Death.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_CamelArabian_Upper_Death.bmp"), 5, 2);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Right_CamelArabian_Upper.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_CamelArabian_Upper.bmp"), 5, 6);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Right_CamelArabian_Upper_Death.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_CamelArabian_Upper_Death.bmp"), 5, 2);
	}

	{
		LowerCamelArabianRenderer = CreateRenderer(RenderOrder::CamelLower);

		LowerCamelArabianRenderer->CreateAnimation("CamelArabian_Lower_Idle", "CamelArabian_Lower.bmp", 0, 3, 0.1f, true);
		LowerCamelArabianRenderer->CreateAnimation("CamelArabian_Lower_Move", "CamelArabian_Lower.bmp", 15, 4, 0.1f, true);
		LowerCamelArabianRenderer->CreateAnimation("CamelArabian_Lower_Move1", "CamelArabian_Lower.bmp", 15, 10, 0.1f, false);
		LowerCamelArabianRenderer->CreateAnimation("CamelArabian_Lower_Move2", "CamelArabian_Lower.bmp", 9, 4, 0.1f, false);
		LowerCamelArabianRenderer->CreateAnimation("CamelArabian_Lower_Down", "CamelArabian_Lower.bmp", 16, 18, 0.1f, false);
		LowerCamelArabianRenderer->CreateAnimation("CamelArabian_Lower_Up", "CamelArabian_Lower.bmp", 18, 16, 0.1f, false);
		LowerCamelArabianRenderer->CreateAnimation("CamelArabian_Lower_DownIdle", "CamelArabian_Lower.bmp", 19, 22, 0.1f, true);
		LowerCamelArabianRenderer->CreateAnimation("CamelArabian_Lower_Death", "CamelArabian_Lower_Death.bmp", 0, 11, 0.1f, true);
	}

	{
		UpperCamelArabianRenderer = CreateRenderer(RenderOrder::CamelUpper);

		UpperCamelArabianRenderer->CreateAnimation("CamelArabian_Left_Upper_Enterance", "Left_CamelArabian_Upper.bmp", 0, 9, 0.1f, false);
		UpperCamelArabianRenderer->CreateAnimation("CamelArabian_Left_Upper_Idle", "Left_CamelArabian_Upper.bmp", 10, 12, 0.1f, true);
		UpperCamelArabianRenderer->CreateAnimation("CamelArabian_Left_Upper_Death", "Left_CamelArabian_Upper_Death.bmp", 0, 9, 0.1f, false);

		UpperCamelArabianRenderer->CreateAnimation("CamelArabian_Right_Upper_Enterance", "Right_CamelArabian_Upper.bmp", 0, 9, 1.0f, false);
		UpperCamelArabianRenderer->CreateAnimation("CamelArabian_Right_Upper_Idle", "Right_CamelArabian_Upper.bmp", 10, 12, 1.0f, true);
		UpperCamelArabianRenderer->CreateAnimation("CamelArabian_Right_Upper_Death", "Right_CamelArabian_Upper_Death.bmp", 0, 9, 1.0f, false);
	}

	{
		UpperDownCamelArabianRenderer = CreateRenderer(RenderOrder::CamelUpperDown);

		UpperDownCamelArabianRenderer->CreateAnimation("CamelArabian_Left_Upper_Down", "Left_CamelArabian_Upper.bmp", 13, 15, 0.1f, false);
		UpperDownCamelArabianRenderer->CreateAnimation("CamelArabian_Left_Upper_Up", "Left_CamelArabian_Upper.bmp", 15, 13, 0.1f, false);
		UpperDownCamelArabianRenderer->CreateAnimation("CamelArabian_Left_Upper_DownIdle", "Left_CamelArabian_Upper.bmp", 26, 28, 0.1f, false);
		//UpperDownCamelArabianRenderer->CreateAnimation("CamelArabian_Left_Upper_Fire", "Left_CamelArabian_Upper.bmp", 16, 25, 0.1f, false);
		UpperDownCamelArabianRenderer->CreateAnimation("CamelArabian_Left_Upper_Fire1", "Left_CamelArabian_Upper.bmp", 16, 22, 0.1f, false);
		UpperDownCamelArabianRenderer->CreateAnimation("CamelArabian_Left_Upper_Fire2", "Left_CamelArabian_Upper.bmp", 23, 25, 0.1f, false);

		UpperDownCamelArabianRenderer->CreateAnimation("CamelArabian_Right_Upper_Down", "Right_CamelArabian_Upper.bmp", 13, 15, 5.0f, false);
		UpperDownCamelArabianRenderer->CreateAnimation("CamelArabian_Right_Upper_Up", "Right_CamelArabian_Upper.bmp", 15, 13, 5.0f, false);
		UpperDownCamelArabianRenderer->CreateAnimation("CamelArabian_Right_Upper_DownIdle", "Right_CamelArabian_Upper.bmp", 26, 28, 1.0f, false);
		//UpperDownCamelArabianRenderer->CreateAnimation("CamelArabian_Right_Upper_Fire", "Right_CamelArabian_Upper.bmp", 16, 25, 1.0f, false);
		UpperDownCamelArabianRenderer->CreateAnimation("CamelArabian_Right_Upper_Fire1", "Right_CamelArabian_Upper.bmp", 16, 22, 1.0f, false);
		UpperDownCamelArabianRenderer->CreateAnimation("CamelArabian_Right_Upper_Fire2", "Right_CamelArabian_Upper.bmp", 23, 25, 1.0f, false);
	}

	

	ChangeLowerState(CamelArabianLowerState::Spawn);
	ChangeUpperState(CamelArabianUpperState::Idle);
	ChangeUpperState(CamelArabianUpperState::DownIdle);

	UpperCamelArabianRenderer->SetRenderPos({ 40, -168 });
	UpperDownCamelArabianRenderer->SetRenderPos({ 40, -168 });

	LowerCamelArabianRenderer->On();
	UpperCamelArabianRenderer->Off();
	UpperDownCamelArabianRenderer->Off();
	//LowerCamelArabianRenderer->GetActor()->SetPos({ 4300, 860 });

	

	{
		/*CamelArabianCollision = CreateCollision(CollisionOrder::EnemyCollision);

		CamelArabianCollision->SetCollisionScale({ 100, 100 });
		CamelArabianCollision->SetCollisionType(CollisionType::Rect);*/
		
		//CamelArabianCollision->SetCollisionPos({ 60, -240 });
	}
	
}

void CamelArabian::Update(float _Delta)
{
	if (LowerCamelArabianRenderer == nullptr)
	{
		return;
	}

	StateLowerUpdate(_Delta);
	StateUpperUpdate(_Delta);
}

void CamelArabian::ChangeLowerState(CamelArabianLowerState _LowerState)
{
	if (_LowerState != LowerState)
	{
		switch (_LowerState)
		{
		case CamelArabianLowerState::Spawn:
			SpawnLowerStart();
			break;
		case CamelArabianLowerState::Idle:
			IdleLowerStart();
			break;
		case CamelArabianLowerState::Move:
			MoveLowerStart();
			break;
		case CamelArabianLowerState::Down:
			DownLowerStart();
			break;
		case CamelArabianLowerState::DownIdle:
			DownIdleLowerStart();
			break;
		case CamelArabianLowerState::Up:
			UpLowerStart();
			break;
		case CamelArabianLowerState::Death:
			DeathLowerStart();
			break;
		default:
			break;
		}
	}
	LowerState = _LowerState;
}
void CamelArabian::StateLowerUpdate(float _Delta)
{
	switch (LowerState)
	{
	case CamelArabianLowerState::Spawn:
		return SpawnLowerUpdate(_Delta);
	case CamelArabianLowerState::Idle:
		return IdleLowerUpdate(_Delta);
	case CamelArabianLowerState::Move:
		return MoveLowerUpdate(_Delta);
	case CamelArabianLowerState::Down:
		return DownLowerUpdate(_Delta);
	case CamelArabianLowerState::DownIdle:
		return DownIdleLowerUpdate(_Delta);
	case CamelArabianLowerState::Up:
		return UpLowerUpdate(_Delta);
	case CamelArabianLowerState::Death:
		return DeathLowerUpdate(_Delta);
	default:
		break;
	}
}

void CamelArabian::ChangeUpperState(CamelArabianUpperState _UpperState)
{
	if (_UpperState != UpperState)
	{
		switch (_UpperState)
		{
		case CamelArabianUpperState::Enterance:
			EnteranceUpperStart();
			break;
		case CamelArabianUpperState::Idle:
			IdleUpperStart();
			break;
		case CamelArabianUpperState::Down:
			DownUpperStart();
			break;
		case CamelArabianUpperState::DownIdle:
			DownIdleUpperStart();
			break;
		case CamelArabianUpperState::Fire:
			FireUpperStart();
			break;
		case CamelArabianUpperState::Up:
			UpUpperStart();
			break;
		case CamelArabianUpperState::Death:
			DeathUpperStart();
			break;
		default:
			break;
		}
	}
	UpperState = _UpperState;
}
void CamelArabian::StateUpperUpdate(float _Delta)
{
	switch (UpperState)
	{
	case CamelArabianUpperState::Enterance:
		return EnteranceUpperUpdate(_Delta);
	case CamelArabianUpperState::Idle:
		return IdleUpperUpdate(_Delta);
	case CamelArabianUpperState::Down:
		return DownUpperUpdate(_Delta);
	case CamelArabianUpperState::DownIdle:
		return DownIdleUpperUpdate(_Delta);
	case CamelArabianUpperState::Fire:
		return FireUpperUpdate(_Delta);
	case CamelArabianUpperState::Up:
		return UpUpperUpdate(_Delta);
	case CamelArabianUpperState::Death:
		return DeathUpperUpdate(_Delta);
	default:
		break;
	}
}

void CamelArabian::ChangeLowerAnimationState(const std::string& _State)
{
	std::string AnimationName;

	AnimationName = "CamelArabian_Lower_";
	AnimationName += _State;

	LowerCamelArabianRenderer->ChangeAnimation(AnimationName);
}
void CamelArabian::ChangeUpperAnimationState(const std::string& _State)
{
	std::string AnimationName;

	switch (Dir)
	{
	case CamelArabianDir::Left:
		AnimationName = "CamelArabian_Left_Upper_";
		break;
	case CamelArabianDir::Right:
		AnimationName = "CamelArabian_Right_Upper_";
		break;
	default:
		break;
	}
	AnimationName += _State;

	UpperCamelArabianRenderer->ChangeAnimation(AnimationName);
}

void CamelArabian::ChangeUpperDownAnimationState(const std::string& _State)
{
	std::string AnimationName;

	switch (Dir)
	{
	case CamelArabianDir::Left:
		AnimationName = "CamelArabian_Left_Upper_";
		break;
	case CamelArabianDir::Right:
		AnimationName = "CamelArabian_Right_Upper_";
		break;
	default:
		break;
	}
	AnimationName += _State;

	UpperDownCamelArabianRenderer->ChangeAnimation(AnimationName);
}

void CamelArabian::SpawnLowerStart()
{
	ResetLiveTime();
	ChangeLowerAnimationState("Move");
	{
		CamelArabianCollision = CreateCollision(CollisionOrder::BossCollision);
		CamelArabianCollision->SetCollisionScale({ 100, 100 });
		CamelArabianCollision->SetCollisionType(CollisionType::Rect);
		CamelArabianCollision->SetCollisionPos({ 60, -240 });
		CamelArabianCollision->Off();
	}
}
void CamelArabian::SpawnLowerUpdate(float _Delta)
{
	float Speed = 200.0f;
	float4 MovePos = float4::ZERO;
	MovePos += {-Speed * _Delta, 0.0f};

	AddPos(MovePos);

	if (1.5f <= GetLiveTime())
	{
		ChangeLowerState(CamelArabianLowerState::Idle);
		UpperCamelArabianRenderer->On();
		ChangeUpperState(CamelArabianUpperState::Enterance);
	}
}

void CamelArabian::IdleLowerStart()
{
	ChangeLowerAnimationState("Idle");
}
void CamelArabian::IdleLowerUpdate(float _Delta)
{
	if (UpperCamelArabianRenderer->IsAnimation("CamelArabian_Left_Upper_Enterance"))
	{
		if (UpperCamelArabianRenderer->IsAnimationEnd())
		{
			ChangeLowerState(CamelArabianLowerState::Move);
		}
	}
}

void CamelArabian::MoveLowerStart()
{
	ChangeLowerAnimationState("Move1");
}
void CamelArabian::MoveLowerUpdate(float _Delta)
{
	float Speed = 150.0f;
	float4 MovePos = float4::ZERO;
	if (LowerCamelArabianRenderer->IsAnimation("CamelArabian_Lower_Move1"))
	{
		MovePos = { -Speed * _Delta, 0.0f };
		if (LowerCamelArabianRenderer->IsAnimationEnd())
		{
			ChangeLowerAnimationState("Move2");
		}
	}
	else if (LowerCamelArabianRenderer->IsAnimation("CamelArabian_Lower_Move2"))
	{
		MovePos = { Speed * _Delta, 0.0f };
		if (LowerCamelArabianRenderer->IsAnimationEnd())
		{
			ChangeLowerState(CamelArabianLowerState::Down);
			UpperCamelArabianRenderer->Off();
			UpperDownCamelArabianRenderer->On();
			ChangeUpperState(CamelArabianUpperState::Down);
		}
	}
	AddPos(MovePos);
}

void CamelArabian::DownLowerStart()
{
	ChangeLowerAnimationState("Down");
}
void CamelArabian::DownLowerUpdate(float _Delta)
{
	if (LowerCamelArabianRenderer->IsAnimationEnd())
	{
		ChangeLowerState(CamelArabianLowerState::DownIdle);
	}
}

void CamelArabian::DownIdleLowerStart()
{
	ChangeLowerAnimationState("DownIdle");
}
void CamelArabian::DownIdleLowerUpdate(float _Delta)
{
	if (UpperDownCamelArabianRenderer->IsAnimation("CamelArabian_Left_Upper_DownIdle") ||
		UpperDownCamelArabianRenderer->IsAnimation("CamelArabian_Right_Upper_DownIdle"))
	{
		if (UpperDownCamelArabianRenderer->IsAnimationEnd())
		{
			ChangeLowerState(CamelArabianLowerState::Up);
		}
	}
}

void CamelArabian::UpLowerStart()
{
	ChangeLowerAnimationState("Up");
}
void CamelArabian::UpLowerUpdate(float _Delta)
{
	if (LowerCamelArabianRenderer->IsAnimationEnd())
	{
		ChangeLowerState(CamelArabianLowerState::Move);
	}
}

void CamelArabian::DeathLowerStart()
{
	ResetLiveTime(); 
	ChangeLowerAnimationState("Death");
}
void CamelArabian::DeathLowerUpdate(float _Delta)
{
	float Speed = 400.0f;
	float4 MovePos = float4::ZERO;
	MovePos = { -Speed * _Delta, 0.0f };
	AddPos(MovePos);

	if (4.0f <= GetLiveTime())
	{
		LowerCamelArabianRenderer->Off();
		LowerCamelArabianRenderer->Death();
		LowerCamelArabianRenderer = nullptr;
		
	}
}

void CamelArabian::EnteranceUpperStart()
{
	ChangeUpperAnimationState("Enterance");
	CamelArabianCollision->On();
	
}
void CamelArabian::EnteranceUpperUpdate(float _Delta)
{
	if (UpperCamelArabianRenderer->IsAnimationEnd())
	{
		ChangeUpperState(CamelArabianUpperState::Idle);
	}
}

void CamelArabian::IdleUpperStart()
{
	ChangeUpperAnimationState("Idle");
	CamelArabianCollision->SetCollisionPos({ 60, -240 });
}
void CamelArabian::IdleUpperUpdate(float _Delta)
{
	DeathCollisionCheck();
}

void CamelArabian::DownUpperStart()
{
	UpperCamelArabianRenderer->Off();
	ChangeUpperDownAnimationState("Down");
	CamelArabianCollision->SetCollisionPos({ 60, -100 });
}
void CamelArabian::DownUpperUpdate(float _Delta)
{
	if (UpperDownCamelArabianRenderer->IsAnimationEnd())
	{
		ChangeUpperState(CamelArabianUpperState::Fire);
	}
}

void CamelArabian::DownIdleUpperStart()
{
	ChangeUpperDownAnimationState("DownIdle");
}
void CamelArabian::DownIdleUpperUpdate(float _Delta)
{
	DeathCollisionCheck();
	if (UpperDownCamelArabianRenderer->IsAnimationEnd())
	{
		ChangeUpperState(CamelArabianUpperState::Up);
	}
}

void CamelArabian::FireUpperStart()
{
	ChangeUpperDownAnimationState("Fire1");

}
void CamelArabian::FireUpperUpdate(float _Delta)
{
	DeathCollisionCheck();

	if (UpperDownCamelArabianRenderer->IsAnimationEnd())
	{
		if (UpperDownCamelArabianRenderer->IsAnimation("CamelArabian_Left_Upper_Fire1") ||
			UpperDownCamelArabianRenderer->IsAnimation("CamelArabian_Left_Upper_Fire1"))
		{
			EnemyBullet* NewBullet = GetLevel()->CreateActor<EnemyBullet>();

			float4 Pos = GetPos();

			if (Dir == CamelArabianDir::Left)
			{
				NewBullet->SetDir(float4::LEFT);
				Pos.X -= 50;
				Pos.Y -= 100;
			}
			else if (Dir == CamelArabianDir::Right)
			{
				NewBullet->SetDir(float4::RIGHT);
				Pos.X += 30;
				Pos.Y -= 100;
			}

			NewBullet->SetPos(Pos);
			ChangeUpperDownAnimationState("Fire2");
		}
		else if (UpperDownCamelArabianRenderer->IsAnimation("CamelArabian_Left_Upper_Fire2") ||
			UpperDownCamelArabianRenderer->IsAnimation("CamelArabian_Left_Upper_Fire2"))
		{
			ChangeUpperState(CamelArabianUpperState::DownIdle);
		}

	}
}

void CamelArabian::UpUpperStart()
{
	ChangeUpperDownAnimationState("Up");
}
void CamelArabian::UpUpperUpdate(float _Delta)
{
	if (UpperDownCamelArabianRenderer->IsAnimationEnd())
	{
		UpperDownCamelArabianRenderer->Off();
		UpperCamelArabianRenderer->On();
		ChangeUpperState(CamelArabianUpperState::Idle);
		CamelArabianCollision->SetCollisionPos({ 60, -240 });
	}
}

void CamelArabian::DeathUpperStart()
{	
	UpperDownCamelArabianRenderer->Off();
	UpperCamelArabianRenderer->On();
	ChangeUpperAnimationState("Death");
}
void CamelArabian::DeathUpperUpdate(float _Delta)
{
	if (UpperCamelArabianRenderer->IsAnimationEnd())
	{
		UpperCamelArabianRenderer->Off();
	}
}

void CamelArabian::DeathCollisionCheck()
{
	std::vector<GameEngineCollision*> _Collision;
	if (true == CamelArabianCollision->Collision(CollisionOrder::BulletCollision, _Collision
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
		CamelArabianCollision->Off();
		ChangeUpperState(CamelArabianUpperState::Death);
		ChangeLowerState(CamelArabianLowerState::Death);
	}
}