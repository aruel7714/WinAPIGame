#include "ArabianSword.h"
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Arabian.h"
#include "Player.h"

ArabianSword::ArabianSword()
{
}

ArabianSword::~ArabianSword()
{
}

void ArabianSword::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("ArabianSwordSFX.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("ArabianSwordSFX.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Left_ArabianSwordSFX.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_ArabianSwordSFX.bmp"), 5, 3);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Right_ArabianSwordSFX.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Right_ArabianSwordSFX.bmp"), 5, 3);
	}

	{
		SwordRenderer = CreateRenderer("ArabianSwordSFX.bmp", RenderOrder::EnemyAttack);

		SwordRenderer->CreateAnimation("Left_Sword_Throw", "Left_ArabianSwordSFX.bmp", 0, 10, 0.05f, true);
		SwordRenderer->CreateAnimation("Left_Sword_HitGround", "Left_ArabianSwordSFX.bmp", 11, 11, 1.0f, true);

		SwordRenderer->CreateAnimation("Right_Sword_Throw", "Right_ArabianSwordSFX.bmp", 0, 10, 1.0f, true);
		SwordRenderer->CreateAnimation("Right_Sword_HitGround", "Right_ArabianSwordSFX.bmp", 11, 11, 1.0f, true);
	}

	{
		SwordCollision = CreateCollision(CollisionOrder::EnemySwordCollision);

		SwordCollision->SetCollisionScale({ 20, 20 });
		
		SwordCollision->SetCollisionType(CollisionType::Rect);
	}

	ChangeState(SwordState::Throw);
}

void ArabianSword::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void ArabianSword::ChangeState(SwordState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case SwordState::Throw:
			ThrowStart();
			break;
		case SwordState::HitGround:
			HitGroundStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void ArabianSword::StateUpdate(float _Delta)
{
	switch (State)
	{
	case SwordState::Throw:
		return ThrowUpdate(_Delta);
	case SwordState::HitGround:
		return HitGroundUpdate(_Delta);
	default:
		break;
	}
}
void ArabianSword::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName;

	switch (Dir)
	{
	case SwordDir::Right:
		AnimationName = "Right_Sword_";
		break;
	case SwordDir::Left:
		AnimationName = "Left_Sword_";
		break;
	default:
		break;
	}

	AnimationName += _State;

	SwordRenderer->ChangeAnimation(AnimationName);
}

void ArabianSword::ThrowStart()
{
	GravityReset();
	GravityDir = float4::UP * 2.0f;
	if (Arabian::Dir == ArabianDir::Right)
	{
		GravityDir += float4::RIGHT * 0.4f;
	}
	else if (Arabian::Dir == ArabianDir::Left)
	{
		GravityDir += float4::LEFT * 0.4f;
	}
	SetGravityVector(GravityDir * 650.0f);

	ChangeAnimationState("Throw");
}
void ArabianSword::ThrowUpdate(float _Delta)
{
	Gravity(_Delta);

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (Color != RGB(255, 255, 255))
		{
			ChangeState(SwordState::HitGround);
		}
	}

	std::vector<GameEngineCollision*> _Collision;
	if (true == SwordCollision->Collision(CollisionOrder::PlayerCollision, _Collision
		, CollisionType::Rect
		, CollisionType::Rect
	))
	{
		for (size_t i = 0; i < _Collision.size(); i++)
		{
			GameEngineCollision* Collision = _Collision[i];

			GameEngineActor* Actor = Collision->GetActor();
		}
		Player::GetMainPlayer()->ChangeLowerState(PlayerLowerState::SwordDeath);
		SwordRenderer->Off();
		SwordCollision->Off();
		
	}
}

void ArabianSword::HitGroundStart()
{
	SwordCollision->Off();
	ResetLiveTime();
	ChangeAnimationState("HitGround");
}
void ArabianSword::HitGroundUpdate(float _Delta)
{
	

	if (2.0f <= GetLiveTime())
	{
		SwordRenderer->Off();
		
	}
}