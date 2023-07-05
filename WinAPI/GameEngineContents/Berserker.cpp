#include "Berserker.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "ContentsEnum.h"

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

	{
		BerserkerRenderer = CreateRenderer(RenderOrder::Enemy);

		BerserkerRenderer->CreateAnimation("Berserker_SitIdle", "Berserker.bmp", 0, 3, 2.0f, true);
		BerserkerRenderer->CreateAnimation("Berserker_StandIdle", "Berserker.bmp", 4, 7, 2.0f, true);
		BerserkerRenderer->CreateAnimation("Berserker_Move", "Berserker.bmp", 8, 13, 2.0f, true);
		BerserkerRenderer->CreateAnimation("Berserker_Attack", "Berserker.bmp", 14, 19, 2.0f, true);
		BerserkerRenderer->CreateAnimation("Berserker_Death", "Berserker.bmp", 20, 28, 2.0f, true);
	}
	BerserkerRenderer->GetActor()->SetPos({ 12500, 860 });

	ChangeState(BerserkerState::Death);
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

void Berserker::SitIdleStart()
{
	ChangeAnimationState("SitIdle");
}
void Berserker::SitIdleUpdate(float _Delta)
{

}

void Berserker::StandIdleStart()
{
	ChangeAnimationState("StandIdle");
}
void Berserker::StandIdleUpdate(float _Delta)
{

}

void Berserker::MoveStart()
{
	ChangeAnimationState("Move");
}
void Berserker::MoveUpdate(float _Delta)
{

}

void Berserker::AttackStart()
{
	ChangeAnimationState("Attack");
}
void Berserker::AttackUpdate(float _Delta)
{

}

void Berserker::DeathStart()
{
	ChangeAnimationState("Death");
}
void Berserker::DeathUpdate(float _Delta)
{

}
