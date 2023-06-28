#include "FinalBoss.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"

FinalBoss::FinalBoss()
{
}

FinalBoss::~FinalBoss()
{
}

void FinalBoss::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("FinalBoss.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("FinalBoss.bmp"), 1, 8);
	}

	{
		FinalBossRenderer = CreateRenderer(RenderOrder::Boss);
		
		FinalBossRenderer->CreateAnimation("FinalBoss_Pattern1", "FinalBoss.bmp", 0, 0, true, 1.0f);
		FinalBossRenderer->CreateAnimation("FinalBoss_Pattern2", "FinalBoss.bmp", 0, 1, true, 1.0f);
		FinalBossRenderer->CreateAnimation("FinalBoss_Pattern3", "FinalBoss.bmp", 0, 2, true, 1.0f);
		FinalBossRenderer->CreateAnimation("FinalBoss_Pattern4", "FinalBoss.bmp", 0, 3, true, 1.0f);
		FinalBossRenderer->CreateAnimation("FinalBoss_Pattern5", "FinalBoss.bmp", 0, 4, true, 1.0f);
		FinalBossRenderer->CreateAnimation("FinalBoss_Pattern6", "FinalBoss.bmp", 0, 5, true, 1.0f);
		FinalBossRenderer->CreateAnimation("FinalBoss_Pattern7", "FinalBoss.bmp", 0, 6, true, 1.0f);
		FinalBossRenderer->CreateAnimation("FinalBoss_Destroy", "FinalBoss.bmp", 0, 7, true, 1.0f);
	}

}

void FinalBoss::ChangeState(BossState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case BossState::Pattern1:
			Pattern1Start();
			break;
		case BossState::Pattern2:
			Pattern2Start();
			break;
		case BossState::Pattern3:
			Pattern3Start();
			break;
		case BossState::Pattern4:
			Pattern4Start();
			break;
		case BossState::Pattern5:
			Pattern5Start();
			break;
		case BossState::Pattern6:
			Pattern6Start();
			break;
		case BossState::Pattern7:
			Pattern7Start();
			break;
		case BossState::Destroy:
			DestroyStart();
			break;
		default:
			break;
		}
	}
}

void FinalBoss::StateUpdate(float _Delta)
{
	switch (State)
	{
	case BossState::Pattern1:
		return Pattern1Update(_Delta);
	case BossState::Pattern2:
		return Pattern1Update(_Delta);
	case BossState::Pattern3:
		return Pattern1Update(_Delta);
	case BossState::Pattern4:
		return Pattern1Update(_Delta);
	case BossState::Pattern5:
		return Pattern1Update(_Delta);
	case BossState::Pattern6:
		return Pattern1Update(_Delta);
	case BossState::Pattern7:
		return Pattern1Update(_Delta);
	case BossState::Destroy:
		return DestroyUpdate(_Delta);
	default:
		break;
	}
}

void FinalBoss::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName;

	AnimationName = "FinalBoss_";

	AnimationName += _State;

	FinalBossRenderer->ChangeAnimation(AnimationName);
}

void FinalBoss::Pattern1Start()
{
	ChangeAnimationState("Pattern1");
}
void FinalBoss::Pattern1Update(float _Delta)
{

}

void FinalBoss::Pattern2Start()
{
	ChangeAnimationState("Pattern2");
}
void FinalBoss::Pattern2Update(float _Delta)
{

}

void FinalBoss::Pattern3Start()
{
	ChangeAnimationState("Pattern3");
}
void FinalBoss::Pattern3Update(float _Delta)
{

}

void FinalBoss::Pattern4Start()
{
	ChangeAnimationState("Pattern4");
}
void FinalBoss::Pattern4Update(float _Delta)
{

}

void FinalBoss::Pattern5Start()
{
	ChangeAnimationState("Pattern5");
}
void FinalBoss::Pattern5Update(float _Delta)
{

}

void FinalBoss::Pattern6Start()
{
	ChangeAnimationState("Pattern6");
}
void FinalBoss::Pattern6Update(float _Delta)
{

}

void FinalBoss::Pattern7Start()
{
	ChangeAnimationState("Pattern7");
}
void FinalBoss::Pattern7Update(float _Delta)
{

}

void FinalBoss::DestroyStart()
{
	ChangeAnimationState("Destroy");
}
void FinalBoss::DestroyUpdate(float _Delta)
{

}