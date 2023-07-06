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
		TruckRenderer = CreateRenderer(RenderOrder::EnemyTruck);

		TruckRenderer->CreateAnimation("Truck_Idle", "Truck.bmp", 0, 0, 1.0f, true);
		TruckRenderer->CreateAnimation("Truck_Drive", "Truck.bmp", 1, 4, 0.1f, true);
		TruckRenderer->CreateAnimation("Truck_Deploy", "Truck.bmp", 5, 16, 0.1f, false);
		TruckRenderer->CreateAnimation("Truck_DeployEnd", "Truck.bmp", 16, 16, 1.0f, true);
		TruckRenderer->CreateAnimation("Truck_Destroy", "Truck.bmp", 17, 22, 0.1f, true);
	}

	{
		TruckCollision = CreateCollision(CollisionOrder::BossCollision);

		TruckCollision->SetCollisionScale({ 450, 300 });
		TruckCollision->SetCollisionType(CollisionType::Rect);
		TruckCollision->SetCollisionPos({ 0, -150 });
	}

	TruckRenderer->GetActor()->SetPos({ 6750, 864 });

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
	
}

void Truck::DriveStart()
{
	ResetLiveTime();
	ChangeAnimationState("Drive");
}
void Truck::DriveUpdate(float _Delta)
{
	float Speed = 200.0f;
	float4 MovePos = { -Speed * _Delta, 0.0f };
	AddPos(MovePos);

	if (3.0f <= GetLiveTime())
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
	std::vector<GameEngineCollision*> _Collision;
	if (true == TruckCollision->Collision(CollisionOrder::BulletCollision, _Collision
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
		Hp--;
		
	}

	if(Hp <= 0)
	{
		ChangeState(TruckState::Destroy);
	}

	if (TruckRenderer->IsAnimationEnd())
	{
		ChangeAnimationState("DeployEnd");
	}
}

void Truck::DestroyStart()
{
	IsDestroy = true;
	TruckCollision->Off();
	ChangeAnimationState("Destroy");
}
void Truck::DestroyUpdate(float _Delta)
{

}