#include "Arabian.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCollision.h>

std::list<Arabian*> Arabian::AllArabian;

Arabian::Arabian()
{
	AllArabian.push_back(this);
}

Arabian::~Arabian()
{
}

void Arabian::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Left_Arabian_All.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\");
		
		// ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Left_Arabian.bmp"));
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Left_Arabian_All.bmp"), 5, 14);
	}

	{
		ArabianRenderer = CreateRenderer(RenderOrder::Enemy);
		
		ArabianRenderer->CreateAnimation("Left_Arabian_Idle", "Left_Arabian_All.bmp", 0, 5, 0.5f, false);
		ArabianRenderer->CreateAnimation("Left_Arabian_Ready", "Left_Arabian_All.bmp", 6, 9, 0.5f, false);
		ArabianRenderer->CreateAnimation("Left_Arabian_Move", "Left_Arabian_All.bmp", 10, 21, 0.5f, true);
		ArabianRenderer->CreateAnimation("Left_Arabian_Jump", "Left_Arabian_All.bmp", 22, 30, 0.5f, false);
		ArabianRenderer->CreateAnimation("Left_Arabian_BackStep", "Left_Arabian_All.bmp", 31, 34, 0.5f, false);
		ArabianRenderer->CreateAnimation("Left_Arabian_AttackReady", "Left_Arabian_All.bmp", 35, 38, 0.5f, false);
		ArabianRenderer->CreateAnimation("Left_Arabian_MeleeAttack", "Left_Arabian_All.bmp", 39, 46, 0.5f, false);
		ArabianRenderer->CreateAnimation("Left_Arabian_RangeAttack", "Left_Arabian_All.bmp", 47, 65, 0.5f, false);


		ArabianRenderer->GetActor()->SetPos({ 3200, 850 });
	}

	ChangeState(ArabianState::Idle);
}

void Arabian::Update(float _Delta)
{

}

void Arabian::Render(float _Delta)
{
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	CollisionData Data;

	Data.Pos = ActorCameraPos();

	Data.Scale = { 5,5 };

	Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
}

void Arabian::ChangeState(ArabianState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case ArabianState::Idle:
			IdleStart();
			break;
		case ArabianState::Ready:
			break;
		case ArabianState::Move:
			break;
		case ArabianState::Jump:
			break;
		case ArabianState::BackStep:
			break;
		case ArabianState::AttackReady:
			break;
		case ArabianState::MeleeAttack:
			break;
		case ArabianState::RangeAttack:
			break;
		default:
			break;
		}
	}
}

void Arabian::StateUpdate(float _Delta)
{
	switch (State)
	{
	case ArabianState::Idle:
		return IdleUpdate(_Delta);
	case ArabianState::Ready:
		break;
	case ArabianState::Move:
		break;
	case ArabianState::Jump:
		break;
	case ArabianState::BackStep:
		break;
	case ArabianState::AttackReady:
		break;
	case ArabianState::MeleeAttack:
		break;
	case ArabianState::RangeAttack:
		break;
	default:
		break;
	}
}

void Arabian::ChangeAnimationState(const std::string& _State)
{
	std::string AnimationName;

	switch (Dir)
	{
	case ArabianDir::Left:
		AnimationName = "Left_Arabian_";
		break;
	case ArabianDir::Right:
		AnimationName = "Right_Arabian_";
		break;
	default:
		break;
	}

	AnimationName += _State;

	ArabianRenderer->ChangeAnimation(AnimationName);
}


////////////// Arabian State Function ///////////////
void Arabian::IdleStart()
{
	ChangeAnimationState("Idle");
}
void Arabian::IdleUpdate(float _Delta)
{

}