#include "Granade.h"
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Granade::Granade()
{
}

Granade::~Granade()
{
}

void Granade::Start() 
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("OneGranade.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\SFX\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("OneGranade.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("LGranade.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\SFX\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("LGranade.bmp"), 5, 4);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("RGranade.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\SFX\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("RGranade.bmp"), 5, 4);
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("GranadeExplosion.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\SFX\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("GranadeExplosion.bmp"), 27, 1);
	}

	GranadeRenderer = CreateRenderer("OneGranade.bmp", RenderOrder::Granade);

	

	GranadeRenderer->CreateAnimation("Right_GranadeFire", "RGranade.bmp", 0, 15, 0.04f, false);
	GranadeRenderer->CreateAnimation("Right_GranadeBound", "LGranade.bmp", 14, 7, 0.04f, false);

	GranadeRenderer->CreateAnimation("Left_GranadeFire", "LGranade.bmp", 0, 15, 0.01f, false);
	GranadeRenderer->CreateAnimation("Left_GranadeBound", "RGranade.bmp", 14, 7, 0.01f, false);

	GranadeRenderer->CreateAnimation("Right_GranadeExplosion", "GranadeExplosion.bmp", 0, 25, 0.03f, false);
	GranadeRenderer->CreateAnimation("Right_GranadeEnd", "GranadeExplosion.bmp", 26, 26, 0.03f, false);
	GranadeRenderer->CreateAnimation("Left_GranadeExplosion", "GranadeExplosion.bmp", 0, 26, 0.5f, false);

	{
		GranadeCollision = CreateCollision(CollisionOrder::BulletCollision);

		GranadeCollision->SetCollisionScale({ 45, 45 });
		GranadeCollision->SetCollisionType(CollisionType::Rect);
		
	}

	ChangeState(GranadeState::Fire);

}
void Granade::Update(float _Delta)
{

	StateUpdate(_Delta);
}



//Gravity(_Delta);
//
//{
//	unsigned int Color = GetGroundColor(RGB(255, 255, 255));
//
//	if (Color != RGB(255, 255, 255))
//	{
//		ChangeLowerState(PlayerLowerState::Idle);
//		return;
//	}
//}


void Granade::ChangeState(GranadeState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case GranadeState::Fire:
			FireStart();
			break;
		case GranadeState::Bound:
			BoundStart();
			break;
		case GranadeState::Explosion:
			ExplosionStart();
			break;
		case GranadeState::ExplosionEnd:
			ExplosionEnd();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void Granade::StateUpdate(float _Delta)
{
	switch (State)
	{
	case GranadeState::Fire:
		return FireUpdate(_Delta);
		break;
	case GranadeState::Bound:
		return BoundUpdate(_Delta);
		break;
	case GranadeState::Explosion:
		return ExplosionUpdate(_Delta);
		break;
	default:
		break;
	}

}
void Granade::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName;

	switch (Dir)
	{
	case GranadeDir::Right:
		AnimationName = "Right_Granade";
		break;
	case GranadeDir::Left:
		AnimationName = "Left_Granade";
		break;
	default:
		break;
	}

	AnimationName += _State;

	GranadeRenderer->ChangeAnimation(AnimationName);
}

void Granade::FireStart()
{
	float4 GravityDir = float4::UP;
	GravityDir += (float4::RIGHT);
	SetGravityVector(GravityDir * 600.0f);
	ChangeAnimationState("Fire");
}
void Granade::FireUpdate(float _Delta)
{
	Gravity(_Delta);

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (Color != RGB(255, 255, 255))
		{
			ChangeState(GranadeState::Bound);
		}
	}

	std::vector<GameEngineCollision*> _Collision;
	if (true == GranadeCollision->Collision(CollisionOrder::EnemyCollision, _Collision
		, CollisionType::Rect
		, CollisionType::Rect
	))
	{
		for (size_t i = 0; i < _Collision.size(); i++)
		{
			GameEngineCollision* Collision = _Collision[i];

			GameEngineActor* Actor = Collision->GetActor();

			//Actor->Death();
		}
		ChangeState(GranadeState::Explosion);
	}

}



void Granade::BoundStart()
{
	float4 GravityDir = (float4::UP);
	GravityDir += (float4::RIGHT);
	SetGravityVector(GravityDir * 500.0f);
	ChangeAnimationState("Bound");
}
void Granade::BoundUpdate(float _Delta)
{
	Gravity(_Delta);
	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), float4::UP);

		if (Color != RGB(255, 255, 255))
		{
			ChangeState(GranadeState::Explosion);
		}
	}

}

void Granade::ExplosionStart()
{

	ChangeAnimationState("Explosion");
	GranadeRenderer->SetRenderScaleToTexture();

}
void Granade::ExplosionUpdate(float _Delta)
{
	if (true == GranadeRenderer->IsAnimationEnd())
	{
		ChangeState(GranadeState::ExplosionEnd);
	}
}

void Granade::ExplosionEnd()
{
	ChangeAnimationState("End");
	if (nullptr != GranadeRenderer)
	{
		GranadeRenderer->Death();
		GranadeRenderer = nullptr;
		GranadeCollision->Death();
		GranadeCollision = nullptr;
	}
}