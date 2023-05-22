#include "Stage1.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>

#include "BackGround.h"

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
}

void Stage1::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Mission1.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentResource");

		FilePath.MoveChild("ContentResource\\Texture\\Map");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Mission1.bmp"));
	}

	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("Mission1.bmp");
	
}

void Stage1::Update(float _Delta) {}
void Stage1::Render() {}
void Stage1::Release() {}
