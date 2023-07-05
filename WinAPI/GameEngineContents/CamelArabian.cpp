#include "CamelArabian.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

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

		LowerCamelArabianRenderer->CreateAnimation("CamelArabian_Lower_Idle", "CamelArabian_Lower.bmp", 0, 3, 1.0f, true);
		LowerCamelArabianRenderer->CreateAnimation("CamelArabian_Lower_Move", "CamelArabian_Lower.bmp", 15, 4, 2.0f, true);
		LowerCamelArabianRenderer->CreateAnimation("CamelArabian_Lower_Move1", "CamelArabian_Lower.bmp", 15, 10, 2.0f, false);
		LowerCamelArabianRenderer->CreateAnimation("CamelArabian_Lower_Move2", "CamelArabian_Lower.bmp", 9, 4, 2.0f, false);
		LowerCamelArabianRenderer->CreateAnimation("CamelArabian_Lower_Down", "CamelArabian_Lower.bmp", 16, 18, 5.0f, true);
		LowerCamelArabianRenderer->CreateAnimation("CamelArabian_Lower_DownIdle", "CamelArabian_Lower.bmp", 19, 22, 1.0f, true);
		LowerCamelArabianRenderer->CreateAnimation("CamelArabian_Lower_Death", "CamelArabian_Lower_Death.bmp", 0, 11, 1.0f, true);
	}

	{
		UpperCamelArabianRenderer = CreateRenderer(RenderOrder::CamelUpper);

		UpperCamelArabianRenderer->CreateAnimation("CamelArabian_Left_Upper_Enterance", "Left_CamelArabian_Upper.bmp", 0, 9, 1.0f, true);
		UpperCamelArabianRenderer->CreateAnimation("CamelArabian_Left_Upper_Idle", "Left_CamelArabian_Upper.bmp", 10, 12, 1.0f, true);
		UpperCamelArabianRenderer->CreateAnimation("CamelArabian_Left_Upper_Death", "Left_CamelArabian_Upper_Death.bmp", 0, 9, 1.0f, true);

		UpperCamelArabianRenderer->CreateAnimation("CamelArabian_Right_Upper_Enterance", "Right_CamelArabian_Upper.bmp", 0, 9, 1.0f, true);
		UpperCamelArabianRenderer->CreateAnimation("CamelArabian_Right_Upper_Idle", "Right_CamelArabian_Upper.bmp", 10, 12, 1.0f, true);
		UpperCamelArabianRenderer->CreateAnimation("CamelArabian_Right_Upper_Death", "Right_CamelArabian_Upper_Death.bmp", 0, 9, 1.0f, true);
	}

	{
		UpperDownCamelArabianRenderer = CreateRenderer(RenderOrder::CamelUpperDown);

		UpperDownCamelArabianRenderer->CreateAnimation("CamelArabian_Left_Upper_Down", "Left_CamelArabian_Upper.bmp", 13, 15, 5.0f, true);
		UpperDownCamelArabianRenderer->CreateAnimation("CamelArabian_Left_Upper_DownIdle", "Left_CamelArabian_Upper.bmp", 26, 28, 1.0f, true);
		UpperDownCamelArabianRenderer->CreateAnimation("CamelArabian_Left_Upper_Fire", "Left_CamelArabian_Upper.bmp", 16, 25, 1.0f, true);

		UpperDownCamelArabianRenderer->CreateAnimation("CamelArabian_Right_Upper_Down", "Right_CamelArabian_Upper.bmp", 13, 15, 5.0f, true);
		UpperDownCamelArabianRenderer->CreateAnimation("CamelArabian_Right_Upper_DownIdle", "Right_CamelArabian_Upper.bmp", 26, 28, 1.0f, true);
		UpperDownCamelArabianRenderer->CreateAnimation("CamelArabian_Right_Upper_Fire", "Right_CamelArabian_Upper.bmp", 16, 25, 1.0f, true);
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
		CamelArabianCollision = CreateCollision(CollisionOrder::EnemyCollision);

		CamelArabianCollision->SetCollisionScale({ 100, 100 });
		CamelArabianCollision->SetCollisionType(CollisionType::Rect);
		
		//CamelArabianCollision->SetCollisionPos({ 60, -240 });
	}
	
}

void CamelArabian::Update(float _Delta)
{
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
	ChangeLowerAnimationState("Move");
}
void CamelArabian::SpawnLowerUpdate(float _Delta)
{

}

void CamelArabian::IdleLowerStart()
{
	ChangeLowerAnimationState("Idle");
}
void CamelArabian::IdleLowerUpdate(float _Delta)
{

}

void CamelArabian::MoveLowerStart()
{
	ChangeLowerAnimationState("Move");
}
void CamelArabian::MoveLowerUpdate(float _Delta)
{

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
	if (LowerCamelArabianRenderer->IsAnimationEnd())
	{
	//	ChangeLowerState(CamelArabianLowerState::Down);
	}
}

void CamelArabian::DeathLowerStart()
{
	ChangeLowerAnimationState("Death");
}
void CamelArabian::DeathLowerUpdate(float _Delta)
{

}

void CamelArabian::EnteranceUpperStart()
{
	ChangeUpperAnimationState("Enterance");
	CamelArabianCollision->SetCollisionPos({ 60, -240 });
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
}
void CamelArabian::IdleUpperUpdate(float _Delta)
{

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
	if (UpperDownCamelArabianRenderer->IsAnimationEnd())
	{
		ChangeUpperState(CamelArabianUpperState::Down);
	}
}

void CamelArabian::FireUpperStart()
{
	ChangeUpperDownAnimationState("Fire");
}
void CamelArabian::FireUpperUpdate(float _Delta)
{
	if (UpperDownCamelArabianRenderer->IsAnimationEnd())
	{
		/*UpperDownCamelArabianRenderer->Off();
		UpperCamelArabianRenderer->On();
		ChangeUpperState(CamelArabianUpperState::Idle);*/
		ChangeUpperState(CamelArabianUpperState::DownIdle);
	}
}

void CamelArabian::DeathUpperStart()
{
	ChangeUpperAnimationState("Death");
}
void CamelArabian::DeathUpperUpdate(float _Delta)
{
	
}