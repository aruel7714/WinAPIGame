#include "HeavyMachineGun.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnum.h"
#include "Player.h"

HeavyMachineGun::HeavyMachineGun()
{
}

HeavyMachineGun::~HeavyMachineGun()
{
}

void HeavyMachineGun::Start()
{
	ItemRenderer = CreateRenderer(RenderOrder::ItemRenderer);

	if (false == ResourcesManager::GetInst().IsLoadTexture("HeavyMachineGunItem.bmp"))
	{
		GameEnginePath FilePath;

		FilePath.SetCurrentPath();

		FilePath.MoveParentToExistsChild("ContentsResources");

		FilePath.MoveChild("ContentsResources\\Texture\\Item\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HeavyMachineGunItem.bmp"));
	}

	ResourcesManager::GetInst().FindTexture("HeavyMachineGunItem.bmp");
	ItemRenderer->SetTexture("HeavyMachineGunItem.bmp");
	ItemRenderer->SetRenderScaleToTexture();

	ItemRenderer->GetActor()->SetPos({ 2800, 800 });
	

	ItemCollision = CreateCollision(CollisionOrder::ItemCollision);

	ItemCollision->SetCollisionScale({ 80, 80 });
	ItemCollision->SetCollisionPos({ 0, -40 });
	
}
void HeavyMachineGun::Update(float _Delta)
{
	{
		// �߹��� ��
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		// �� ���� ����̶�� �߷� ����(�Ʒ��� ��������)
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);
		}
		// �װ� �ƴ϶��
		else
		{
			// �� �� ���� �� ����
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			// �� ���� ���� ����� �ƴ϶�� ���� �̵�
			while (CheckColor != RGB(255, 255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}

			GravityReset();
		}
	}

	std::vector<GameEngineCollision*> _Collision;
	if (true == ItemCollision->Collision(CollisionOrder::PlayerCollision, _Collision
		, CollisionType::Rect
		, CollisionType::Rect
	))
	{
		for (size_t i = 0; i < _Collision.size(); i++)
		{
			GameEngineCollision* Collision = _Collision[i];

			GameEngineActor* Actor = Collision->GetActor();

			ItemRenderer->Off();
			
			Player::WeaponName = "Rifle_";
		}
	}
}