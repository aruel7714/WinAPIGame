#include "MiddleBoss.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"

MiddleBoss::MiddleBoss()
{
}

MiddleBoss::~MiddleBoss()
{
}

void MiddleBoss::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Boss);
	if (false == ResourcesManager::GetInst().IsLoadTexture("MiddleBossObject.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\MiddleBoss\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MiddleBossObject.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("MiddleBossObject_Destroy.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Enemy\\MiddleBoss\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MiddleBossObject_Destroy.bmp"));
	}

	
	{
		/*ResourcesManager::GetInst().FindTexture("MiddleBossObject.bmp");
		MainRenderer->SetTexture("MiddleBossObject.bmp");*/
		
		//MainRenderer->GetActor()->SetPos({ 8147, 597 });
		ResourcesManager::GetInst().FindTexture("MiddleBossObject_Destroy.bmp");
		MainRenderer->SetTexture("MiddleBossObject_Destroy.bmp");
		MainRenderer->GetActor()->SetPos({ 8147, 609 });
	}
}