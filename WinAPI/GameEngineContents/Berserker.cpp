#include "Berserker.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
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
}

void Berserker::Update(float _Delta)
{

}

void Berserker::ChangeState(BerserkerState _State)
{

}

void Berserker::StateUpdate(float _Delta)
{

}

void Berserker::ChangeAnimationState(const std::string& _State)
{

}

void Berserker::SitIdleStart()
{

}
void Berserker::SitIdleUpdate(float _Delta)
{

}

void Berserker::StandIdleStart()
{

}
void Berserker::StandIdleUpdate(float _Delta)
{

}

void Berserker::MoveStart()
{

}
void Berserker::MoveUpdate(float _Delta)
{

}

void Berserker::AttackStart()
{

}
void Berserker::AttackUpdate(float _Delta)
{

}

void Berserker::DeathStart()
{

}
void Berserker::DeathUpdate(float _Delta)
{

}
