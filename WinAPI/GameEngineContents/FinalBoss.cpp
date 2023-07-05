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
	if (false == ResourcesManager::GetInst().IsLoadTexture("FinalBoss1.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\FinalBoss\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("FinalBoss1.bmp"), 1, 8);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("FinalBossAttack1.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\FinalBoss\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("FinalBossAttack1.bmp"), 5, 3);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("FinalBossAttack2.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\FinalBoss\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("FinalBossAttack2.bmp"), 5, 4);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("FinalBossAttack3.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\FinalBoss\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("FinalBossAttack3.bmp"), 5, 2);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("FinalBossAttackEnd.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\FinalBoss\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("FinalBossAttackEnd.bmp"), 5, 4);
	}

	

	{
		FinalBossRenderer = CreateRenderer(RenderOrder::Boss);
		
		FinalBossRenderer->CreateAnimation("FinalBoss_Pattern1", "FinalBoss1.bmp", 0, 0, 1.0f, false);
		FinalBossRenderer->CreateAnimation("FinalBoss_Pattern2", "FinalBoss1.bmp", 0, 1, 1.0f, false);
		FinalBossRenderer->CreateAnimation("FinalBoss_Pattern3", "FinalBoss1.bmp", 0, 2, 1.0f, false);
		FinalBossRenderer->CreateAnimation("FinalBoss_Pattern4", "FinalBoss1.bmp", 0, 3, 1.0f, false);
		FinalBossRenderer->CreateAnimation("FinalBoss_Pattern5", "FinalBoss1.bmp", 0, 4, 1.0f, false);
		FinalBossRenderer->CreateAnimation("FinalBoss_Pattern6", "FinalBoss1.bmp", 0, 5, 1.0f, false);
		FinalBossRenderer->CreateAnimation("FinalBoss_Pattern7", "FinalBoss1.bmp", 0, 6, 1.0f, false);
		FinalBossRenderer->CreateAnimation("FinalBoss_Destroy", "FinalBoss1.bmp", 0, 7, 1.0f, false);
	}

	{
		FinalBossAttackRenderer = CreateRenderer(RenderOrder::BossAttack);
		FinalBossAttackRenderer->CreateAnimation("FinalBoss_AttackBase", "FinalBossAttack1.bmp", 0, 3, 0.1f, true);
		FinalBossAttackRenderer->CreateAnimation("FinalBoss_AttackReady1", "FinalBossAttack1.bmp", 4, 6, 0.1f, false);
		FinalBossAttackRenderer->CreateAnimation("FinalBoss_AttackReady2", "FinalBossAttack1.bmp", 7, 12, 0.1f, true);
		FinalBossAttackRenderer->CreateAnimation("FinalBoss_Attack1", "FinalBossAttack2.bmp", 0, 15, 0.1f, false);
		FinalBossAttackRenderer->CreateAnimation("FinalBoss_Attack2", "FinalBossAttack3.bmp", 0, 5, 0.1f, true);
		FinalBossAttackRenderer->CreateAnimation("FinalBoss_AttackEnd", "FinalBossAttackEnd.bmp", 0, 15, 0.1f, false);
	}

	{
		FinalBossBodyCollision = CreateCollision(CollisionOrder::BossCollision);

		FinalBossBodyCollision->SetCollisionScale({ 320, 420 });
		FinalBossBodyCollision->SetCollisionType(CollisionType::Rect);
		FinalBossBodyCollision->SetCollisionPos({ 0, -210 });
	}

	{
		FinalBossWingCollision = CreateCollision(CollisionOrder::BossCollision);

		FinalBossWingCollision->SetCollisionScale({ 900, 280 });
		FinalBossWingCollision->SetCollisionType(CollisionType::Rect);
		FinalBossWingCollision->SetCollisionPos({ 0, -240 });
	}

	{
		FinalBossLeftAttackCollision = CreateCollision(CollisionOrder::BossAttackCollision);
		
		FinalBossLeftAttackCollision->SetCollisionScale({ 140, 560 });
		FinalBossLeftAttackCollision->SetCollisionType(CollisionType::Rect);
		FinalBossLeftAttackCollision->SetCollisionPos({ -360, 250 });
	}

	{
		FinalBossRightAttackCollision = CreateCollision(CollisionOrder::BossAttackCollision);

		FinalBossRightAttackCollision->SetCollisionScale({ 140, 560 });
		FinalBossRightAttackCollision->SetCollisionType(CollisionType::Rect);
		FinalBossRightAttackCollision->SetCollisionPos({ 360, 250 });
	}

	FinalBossRenderer->GetActor()->SetPos({ 14000, 500 });
	FinalBossAttackRenderer->SetRenderPos({ 0, -116 });

	

	ChangeMainState(BossState::Pattern1);
	ChangeAttackState(BossAttackState::Attack);

}

void FinalBoss::Update(float _Delta)
{
	MainStateUpdate(_Delta);
	AttackStateUpdate(_Delta);
}

void FinalBoss::ChangeMainState(BossState _State)
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
	State = _State;
}

void FinalBoss::MainStateUpdate(float _Delta)
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

void FinalBoss::ChangeAttackState(BossAttackState _AttackState)
{
	if (_AttackState != AttackState)
	{
		switch (_AttackState)
		{
		case BossAttackState::AttackBase:
			AttackBaseStart();
			break;
		case BossAttackState::AttackReady:
			AttackReadyStart();
			break;
		case BossAttackState::Attack:
			AttackStart();
			break;
		case BossAttackState::AttackEnd:
			AttackEndStart();
			break;
		default:
			break;
		}
	}
	AttackState = _AttackState;
}
void FinalBoss::AttackStateUpdate(float _Delta)
{
	switch (AttackState)
	{
	case BossAttackState::AttackBase:
		return AttackBaseUpdate(_Delta);
	case BossAttackState::AttackReady:
		return AttackReadyUpdate(_Delta);
	case BossAttackState::Attack:
		return AttackUpdate(_Delta);
	case BossAttackState::AttackEnd:
		return AttackEndUpdate(_Delta);
	default:
		break;
	}
}



void FinalBoss::ChangeMainAnimationState(const std::string& _State)
{
	std::string AnimationName;

	AnimationName = "FinalBoss_";

	AnimationName += _State;

	FinalBossRenderer->ChangeAnimation(AnimationName);
}

void FinalBoss::ChangeAttackAnimationState(const std::string& _State)
{
	std::string AnimationName;

	AnimationName = "FinalBoss_";

	AnimationName += _State;

	FinalBossAttackRenderer->ChangeAnimation(AnimationName);
}


void FinalBoss::Pattern1Start()
{
	ChangeMainAnimationState("Pattern1");
}
void FinalBoss::Pattern1Update(float _Delta)
{

}

void FinalBoss::Pattern2Start()
{
	ChangeMainAnimationState("Pattern2");
}
void FinalBoss::Pattern2Update(float _Delta)
{

}

void FinalBoss::Pattern3Start()
{
	ChangeMainAnimationState("Pattern3");
}
void FinalBoss::Pattern3Update(float _Delta)
{

}

void FinalBoss::Pattern4Start()
{
	ChangeMainAnimationState("Pattern4");
}
void FinalBoss::Pattern4Update(float _Delta)
{

}

void FinalBoss::Pattern5Start()
{
	ChangeMainAnimationState("Pattern5");
}
void FinalBoss::Pattern5Update(float _Delta)
{

}

void FinalBoss::Pattern6Start()
{
	ChangeMainAnimationState("Pattern6");
}
void FinalBoss::Pattern6Update(float _Delta)
{

}

void FinalBoss::Pattern7Start()
{
	ChangeMainAnimationState("Pattern7");
}
void FinalBoss::Pattern7Update(float _Delta)
{

}

void FinalBoss::DestroyStart()
{
	ChangeMainAnimationState("Destroy");
}
void FinalBoss::DestroyUpdate(float _Delta)
{

}

void FinalBoss::AttackBaseStart()
{
	ChangeAttackAnimationState("AttackBase");
}
void FinalBoss::AttackBaseUpdate(float _Delta)
{
}

void FinalBoss::AttackReadyStart()
{
	ChangeAttackAnimationState("AttackReady1");
}
void FinalBoss::AttackReadyUpdate(float _Delta)
{
	if (FinalBossAttackRenderer->IsAnimationEnd())
	{
		ChangeAttackAnimationState("AttackReady2");
	}
}

void FinalBoss::AttackStart()
{
	ChangeAttackAnimationState("Attack1");
}
void FinalBoss::AttackUpdate(float _Delta)
{
	if (FinalBossAttackRenderer->IsAnimationEnd())
	{
		ChangeAttackAnimationState("Attack2");
	}
}

void FinalBoss::AttackEndStart()
{
	ChangeAttackAnimationState("AttackEnd");
}
void FinalBoss::AttackEndUpdate(float _Delta)
{
	if (FinalBossAttackRenderer->IsAnimationEnd())
	{
		ChangeAttackState(BossAttackState::AttackBase);
	}
}