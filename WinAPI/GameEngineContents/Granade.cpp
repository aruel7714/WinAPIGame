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

	

	GranadeRenderer->CreateAnimation("Right_GranadeFire", "RGranade.bmp", 0, 15, 0.04f, false);
	GranadeRenderer->CreateAnimation("Right_GranadeBound", "LGranade.bmp", 14, 7, 0.04f, false);

	GranadeRenderer->CreateAnimation("Left_GranadeFire", "LGranade.bmp", 0, 15, 0.01f, false);
	GranadeRenderer->CreateAnimation("Left_GranadeBound", "RGranade.bmp", 14, 7, 0.01f, false);

	GranadeRenderer->CreateAnimation("Right_GranadeExplosion", "GranadeExplosion.bmp", 0, 25, 0.1f, false);
	GranadeRenderer->CreateAnimation("Right_GranadeEnd", "GranadeExplosion.bmp", 26, 26, 0.1f, false);
	GranadeRenderer->CreateAnimation("Left_GranadeExplosion", "GranadeExplosion.bmp", 0, 26, 0.5f, false);

	

	ChangeState(GranadeState::Fire);

}
void Granade::Update(float _Delta)
{

	StateUpdate(_Delta);
}

void Granade::Release()
{
	if (nullptr != GranadeRenderer)
	{
		// Death();
		GranadeRenderer->Death();
		GranadeRenderer = nullptr;
	}
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
			ChangeState(GranadeState::Bound);
		}
	}

}

//unsigned int Color = GetGroundColor(RGB(255, 255, 255));
//// 그 색이 흰색이라면 중력 적용(아래로 떨어지기)
//if (RGB(255, 255, 255) == Color)
//{
//	Gravity(_Delta);
//}
//// 그게 아니라면
//else
//{
//	// 내 발 위의 색 조사
//	unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
//
//	// 발 위의 색이 흰색이 아니라면 위로 이동
//	while (CheckColor != RGB(255, 255, 255))
//	{
//		CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
//		AddPos(float4::UP);
//	}
//
//	if (true == GameEngineInput::IsPress('S'))
//	{
//		ChangeLowerState(PlayerLowerState::IdleJump);
//		return;
//	}
//
//
//	GravityReset();
//}

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
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));

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
		Release();
	}
}