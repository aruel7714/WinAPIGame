#include "Stage1.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Player.h"
#include "BackGround.h"
#include "Arabian.h"
#include "ContentsEnum.h"
#include "GlobalValue.h"
#include "HeavyMachineGun.h"
#include "SlaveNPC.h"
#include "MiddleBoss.h"
#include "FinalBoss.h"
#include "DebugCollision.h"
#include "CamelArabian.h"
#include "Berserker.h"
#include "Truck.h"


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

	if (false == ResourcesManager::GetInst().IsLoadTexture("Mission1_Cloud.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Mission1_Cloud.bmp"));
	}

	if (false == ResourcesManager::GetInst().IsLoadTexture("Mission1_Object.bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Map\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Mission1_Object.bmp"));
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
	BackGroundPtr->CloudInit("Mission1_Cloud.bmp");
	BackGroundPtr->ObjectInit("Mission1_Object.bmp");
	//BackGroundPtr->Init("Mission1.bmp");
	// BackGroundPtr->SecondInit("Mission1_SecondBackGround.bmp");

	GameEngineWindowTexture* Ptr = ResourcesManager::GetInst().FindTexture("Mission1_Test.bmp");

	if (nullptr == Ptr)
	{
		MsgBoxAssert("맵 텍스처를 찾을수 없습니다.");
	}

	GlobalValue::MapScale = Ptr->GetScale();

	{
		FirstCollision = CreateActor<DebugCollision>();
		FirstCollision->FocusCollision->SetCollisionPos({ 4150, 400 });
		// 5800 864
		// 8170
		// 9950

		
	}
	

	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("Mission1_Debug_Test.bmp");

	
	//EnemyArabian = CreateActor<Arabian>();
	{
		NewArabian = CreateActor<Arabian>();
		NewArabian->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewArabian->SetPos({ 1650, 800 });

		NewArabian = CreateActor<Arabian>();
		NewArabian->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewArabian->SetPos({ 1953, 864 });

		NewArabian = CreateActor<Arabian>();
		NewArabian->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewArabian->SetPos({ 2360, 732 });

		NewArabian = CreateActor<Arabian>();
		NewArabian->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewArabian->SetPos({ 2810, 864 });

		NewArabian = CreateActor<Arabian>();
		NewArabian->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewArabian->SetPos({ 2843, 512 });

		NewArabian = CreateActor<Arabian>();
		NewArabian->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewArabian->SetPos({ 3552, 864 });

		NewArabian = CreateActor<Arabian>();
		NewArabian->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewArabian->SetPos({ 4001, 864 });

		NewArabian = CreateActor<Arabian>();
		NewArabian->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewArabian->SetPos({ 5353, 580 });

		NewArabian = CreateActor<Arabian>();
		NewArabian->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewArabian->SetPos({ 5353, 380 });

		NewArabian = CreateActor<Arabian>();
		NewArabian->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewArabian->SetPos({ 5580, 580 });

		NewArabian = CreateActor<Arabian>();
		NewArabian->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewArabian->SetPos({ 6412, 580 });

		NewArabian = CreateActor<Arabian>();
		NewArabian->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewArabian->SetPos({ 6412, 380 });

		NewArabian = CreateActor<Arabian>();
		NewArabian->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewArabian->SetPos({ 6678, 380 });
	}
	// 1953, 864
	// 2360, 732
	// 2810 864
	// 2843 512
	// 3552 864
	// 4001 864
	// 5353 580
	// 5353 380
	// 5580 580
	// 6412 580
	// 6412 380
	// 6678 380

	/*NewBerserker = CreateActor<Berserker>();
	NewBerserker->SetGroundTexture("Mission1_Debug_Test.bmp");*/

	NewTruck = CreateActor<Truck>();

	MiddleBossPtr = CreateActor<MiddleBoss>();
	FinalBossPtr = CreateActor<FinalBoss>();
	

	/*NewItem = CreateActor<HeavyMachineGun>();
	NewItem->SetGroundTexture("Mission1_Debug_Test.bmp");*/


	{
		NewSlave = CreateActor<SlaveNPC>();
		NewSlave->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewSlave->SetPos({ 2366, 864 });
		NewSlave->SetSlaveItem(SlaveItem::HeavyMachineGun);
		
		NewSlave = CreateActor<SlaveNPC>();
		NewSlave->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewSlave->SetPos({ 2590, 614 });
		NewSlave->SetSlaveItem(SlaveItem::HeavyMachineGun);

		NewSlave = CreateActor<SlaveNPC>();
		NewSlave->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewSlave->SetPos({ 5243, 580 });

		NewSlave = CreateActor<SlaveNPC>();
		NewSlave->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewSlave->SetPos({ 6678, 580 });

		NewSlave = CreateActor<SlaveNPC>();
		NewSlave->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewSlave->SetPos({ 8100, 580 });

		NewSlave = CreateActor<SlaveNPC>();
		NewSlave->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewSlave->SetPos({ 11340, 580 });
	}
	
	// 2366 864
	// 2590 614
	// 5243 580
	// 5655 580
	// 6678 580
	// 8100 580
	// 11340
	
	/*NewCamelArabian2 = CreateActor<CamelArabian>();
	NewCamelArabian2->LowerCamelArabianRenderer->GetActor()->SetPos({ 12500, 860 });*/
	
	/*NewArabian2 = CreateActor<Arabian>();
	NewArabian2->SetGroundTexture("Mission1_Debug_Test.bmp");
	NewArabian2->SetDir(2);*/

	// truck
	// 6430 864
}

//int Stage1::GetColor(unsigned int _DefaultColor, float4 _Pos)
//{
//	if (nullptr == BackGroundPtr)
//	{
//		MsgBoxAssert("맵 텍스처가 존재하지 않습니다.");
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

	//SlaveNPC::AllSlave
	for (SlaveNPC* Slave : SlaveNPC::AllSlave)
	{
		if (Slave->SlaveRenderer->IsAnimationEnd())
		{
			if (Slave->SlaveRenderer->IsAnimation("Left_Slave_Gift"))
			{
				if (Slave->Item == SlaveItem::HeavyMachineGun)
				{
					NewHeavyMachineGun = CreateActor<HeavyMachineGun>();
					NewHeavyMachineGun->SetGroundTexture("Mission1_Debug_Test.bmp");
					NewHeavyMachineGun->SetPos(Slave->GetPos());
				}
			}
		}
	}

	//CameraFocus();
	

	//if (1.0f <= GetLiveTime())
	//{
	//	Monster* NewMonster = CreateActor<Monster>(UpdateOrder::Monster);
	//	ResetLiveTime();
	//}

	if (true == FirstCollision->FocusCollision->IsDeath() && false == IsCamelArabian)
	{
		NewCamelArabian1 = CreateActor<CamelArabian>();
		NewCamelArabian1->SetGroundTexture("Mission1_Debug_Test.bmp");
		NewCamelArabian1->LowerCamelArabianRenderer->GetActor()->SetPos({ 4774, 860 });
		IsCamelArabian = true;
	}

	//if (NewCamelArabian1->IsDeath())
	//{
	//	LevelPlayer->SetFocusOn();
	//}
}
void Stage1::Release() {}

void Stage1::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅해주지 않았습니다.");
	}

	/*if (nullptr == EnemyArabian)
	{
		MsgBoxAssert("적군을 세팅해주지 않았습니다.");
	}*/

	//LevelPlayer->SetGroundTexture("Mission1_Debug.bmp");
}

void Stage1::LevelEnd(GameEngineLevel* _NextLevel)
{

}