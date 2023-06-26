#include "Stage1.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>

#include "Player.h"
#include "BackGround.h"
#include "Arabian.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"

Stage1::Stage1()
{
}

Stage1::~Stage1()
{
}

void Stage1::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Mission1_Test.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Mission1_Test.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Mission1_Debug_Test.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Mission1_Debug_Test.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Mission1_Second_Test.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Mission1_Second_Test.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Mission1_Third_Test.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Mission1_Third_Test.bmp"));
	}

	//if (false == ResourcesManager::GetInst().IsLoadTexture("Mission1_SecondBackGround.bmp"))
	//{
	//	GameEnginePath FilePath;
	//	FilePath.SetCurrentPath();
	//	FilePath.MoveParentToExistsChild("ContentsResources");

	//	FilePath.MoveChild("ContentsResources\\Texture\\Map\\");
	//	ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Mission1_SecondBackGround.bmp"));
	//}

	BackGroundPtr = CreateActor<BackGround>();
	// BackGroundPtr->Init("Mission1.bmp", "Mission1_SecondBackGround.bmp");
	BackGroundPtr->Init("Mission1_Test.bmp", "Mission1_Debug_Test.bmp");
	BackGroundPtr->SecondInit("Mission1_Second_Test.bmp");
	BackGroundPtr->ThirdInit("Mission1_Third_Test.bmp");
	//BackGroundPtr->Init("Mission1.bmp");
	// BackGroundPtr->SecondInit("Mission1_SecondBackGround.bmp");

	GameEngineWindowTexture* Ptr = ResourcesManager::GetInst().FindTexture("Mission1_Test.bmp");

	if (nullptr == Ptr)
	{
		MsgBoxAssert("�� �ؽ�ó�� ã���� �����ϴ�.");
	}

	GlobalValue::MapScale = Ptr->GetScale();

	
	

	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("Mission1_Debug_Test.bmp");

	
	//EnemyArabian = CreateActor<Arabian>();
	NewArabian1 = CreateActor<Arabian>();
	NewArabian1->SetGroundTexture("Mission1_Debug_Test.bmp");
	
	//NewArabian2 = CreateActor<Arabian>();
	//NewArabian2->SetGroundTexture("Mission1_Debug_Test.bmp");
	//NewArabian2->SetDir(2);
}

//int Stage1::GetColor(unsigned int _DefaultColor, float4 _Pos)
//{
//	if (nullptr == BackGroundPtr)
//	{
//		MsgBoxAssert("�� �ؽ�ó�� �������� �ʽ��ϴ�.");
//	}
//
//	return BackGroundPtr->MapTexture->GetColor(_DefaultColor, _Pos);
//}


void Stage1::Update(float _Delta) 
{
	if (true == GameEngineInput::IsDown(VK_F1))
	{
		BackGroundPtr->SwitchRender();
	}

	//CameraFocus();
	

	//if (1.0f <= GetLiveTime())
	//{
	//	Monster* NewMonster = CreateActor<Monster>(UpdateOrder::Monster);
	//	ResetLiveTime();
	//}
}
void Stage1::Release() {}

void Stage1::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�.");
	}

	/*if (nullptr == EnemyArabian)
	{
		MsgBoxAssert("������ ���������� �ʾҽ��ϴ�.");
	}*/

	//LevelPlayer->SetGroundTexture("Mission1_Debug.bmp");
}

void Stage1::LevelEnd(GameEngineLevel* _NextLevel)
{

}