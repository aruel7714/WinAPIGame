#include "Truck.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "ContentsEnum.h"

Truck::Truck()
{
}

Truck::~Truck()
{
}

void Truck::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Truck.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\");

		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Truck.bmp"), 5, 5);
	}

	{
		TruckRenderer = CreateRenderer(RenderOrder::Enemy);

		TruckRenderer->CreateAnimation("Truck_Idle", "Truck.bmp", 0, 0, 1.0f, true);
		TruckRenderer->CreateAnimation("Truck_Drive", "Truck.bmp", 1, 4, 2.0f, true);
		TruckRenderer->CreateAnimation("Truck_Deploy", "Truck.bmp", 5, 16, 2.0f, true);
		TruckRenderer->CreateAnimation("Truck_Destroy", "Truck.bmp", 17, 22, 2.0f, true);
	}
	TruckRenderer->GetActor()->SetPos({ 12500, 860 });

	ChangeState(TruckState::Idle);
}

void Truck::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void Truck::ChangeState(TruckState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case TruckState::Idle:
			IdleStart();
			break;
		case TruckState::Drive:
			DriveStart();
			break;
		case TruckState::Deploy:
			DeployStart();
			break;
		case TruckState::Destroy:
			DestroyStart();
			break;
		default:
			break;
		}
	}
	State = _State;
}
void Truck::StateUpdate(float _Delta)
{
	switch (State)
	{
	case TruckState::Idle:
		return IdleUpdate(_Delta);
	case TruckState::Drive:
		return DriveUpdate(_Delta);
	case TruckState::Deploy:
		return DeployUpdate(_Delta);
	case TruckState::Destroy:
		return DestroyUpdate(_Delta);
	default:
		break;
	}
}

void Truck::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName;

	AnimationName = "Truck_";
	AnimationName += _State;

	TruckRenderer->ChangeAnimation(AnimationName);
}

void Truck::IdleStart()
{
	ChangeAnimationState("Idle");
}
void Truck::IdleUpdate(float _Delat)
{
	if (2.0f <= GetLiveTime())
	{
		ChangeState(TruckState::Drive);
	}
}

void Truck::DriveStart()
{
	ChangeAnimationState("Drive");
}
void Truck::DriveUpdate(float _Delta)
{
	if (TruckRenderer->IsAnimationEnd())
	{
		ChangeState(TruckState::Deploy);
	}
}

void Truck::DeployStart()
{
	ChangeAnimationState("Deploy");
}
void Truck::DeployUpdate(float _Delta)
{
	if (TruckRenderer->IsAnimationEnd())
	{
		ChangeState(TruckState::Destroy);
	}
}

void Truck::DestroyStart()
{
	ChangeAnimationState("Destroy");
}
void Truck::DestroyUpdate(float _Delta)
{

}