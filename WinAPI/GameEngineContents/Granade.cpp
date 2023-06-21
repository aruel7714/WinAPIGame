#include "Granade.h"
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>

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

	SetGroundTexture("Mission1_Debug_Test.bmp");

	GranadeRenderer->CreateAnimation("Right_GranadeFire", "RGranade.bmp", 0, 15, 0.05f, false);
	GranadeRenderer->CreateAnimation("Right_GranadeBound", "LGranade.bmp", 14, 7, 0.5f, false);

	GranadeRenderer->CreateAnimation("Left_GranadeFire", "LGranade.bmp", 0, 15, 0.5f, false);
	GranadeRenderer->CreateAnimation("Left_GranadeBound", "RGranade.bmp", 14, 7, 0.5f, false);

	GranadeRenderer->CreateAnimation("Right_GranadeExplosion", "GranadeExplosion.bmp", 0, 26, 0.5f, false);
	GranadeRenderer->CreateAnimation("Left_GranadeExplosion", "GranadeExplosion.bmp", 0, 26, 0.5f, false);

	

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
			//ChangeState(GranadeState::Bound);
			return;
		}
	}

}

void Granade::BoundStart()
{
	ChangeAnimationState("Bound");
}
void Granade::BoundUpdate(float _Delta)
{
}

void Granade::ExplosionStart()
{
	ChangeAnimationState("Explosion");
}
void Granade::ExplosionUpdate(float _Delta)
{

}