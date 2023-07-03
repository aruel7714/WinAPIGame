#include "Player.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include "Bullet.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "Granade.h"
#include "BackGround.h"

// 왼쪽 방향키 : 왼쪽 바라보기, 왼쪽으로 이동
// 오른쪽 방향키 : 오른쪽 바라보기, 오른쪽으로 이동
// 위쪽 방향키 : 위 바라보기
// 아래쪽 방향키 : 앉기
// A : Fire
// S : Jump
// D : Granade

void Player::IdleLowerStart()
{
	//UpperRenderer->On();
	ChangeLowerAnimationState("Idle");
}

void Player::IdleLowerUpdate(float _Delta)
{
	{
		// 발밑의 색
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		// 그 색이 흰색이라면 중력 적용(아래로 떨어지기)
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);
		}
		// 그게 아니라면
		else
		{
			// 내 발 위의 색 조사
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			// 발 위의 색이 흰색이 아니라면 위로 이동
			while (CheckColor != RGB(255, 255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}

			if (true == GameEngineInput::IsPress('S'))
			{
				ChangeLowerState(PlayerLowerState::IdleJump);
				return;
			}


			GravityReset();
		}
	}

	if (true == GameEngineInput::IsPress(VK_LEFT) || true == GameEngineInput::IsPress(VK_RIGHT))
	{
		DirCheck();
		ChangeLowerState(PlayerLowerState::Move);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_DOWN))
	{
		ChangeLowerState(PlayerLowerState::SitDown);
	}

	if (true == GameEngineInput::IsDown('P'))
	{
		//ChangeLowerState(PlayerLowerState::RangeDeathJump);
		//ChangeLowerState(PlayerLowerState::SwordDeath);
	}
}

void Player::IdleUpperStart()
{
	RifleBulletDir = float4::RIGHT;
	ChangeUpperAnimationState("Idle");
}
void Player::IdleUpperUpdate(float _Delta)
{

	if (true == GameEngineInput::IsPress(VK_LEFT) || true == GameEngineInput::IsPress(VK_RIGHT))
	{
		DirCheck();
		ChangeUpperState(PlayerUpperState::Move);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_UP))
	{
		if (true != LowerRenderer->IsAnimation("Right_Lower_IdleJump") ||
			true != LowerRenderer->IsAnimation("Left_Lower_IdleJump") ||
			true != LowerRenderer->IsAnimation("Right_Lower_MoveJump") ||
			true != LowerRenderer->IsAnimation("Left_Lower_MoveJump"))
		{
			ChangeUpperState(PlayerUpperState::LookUp);
		}
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeUpperState(PlayerUpperState::IdleJump);
		
	}
	if (true == GameEngineInput::IsDown('A'))
	{
		//FireUpdate(_Delta);

		PrevState = "Idle";

		ChangeUpperState(PlayerUpperState::Fire);
		//ChangeUpperState(PlayerUpperState::MeleeAtt);
	}
	if (true == GameEngineInput::IsDown('D'))
	{
		PrevState = "Idle";

		ChangeUpperState(PlayerUpperState::Granade);
	}

}

void Player::MoveLowerStart()
{
	ChangeLowerAnimationState("Move");
}
void Player::MoveLowerUpdate(float _Delta) 
{
	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);
		}
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255, 255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}

			

			if (true == GameEngineInput::IsPress('S'))
			{
				ChangeLowerState(PlayerLowerState::MoveJump);
				return;
			}

			GravityReset();
		}
	}
	DirCheck();

	float Speed = 300.0f;
	//float Speed = 1.0f;

	float4 MovePos = float4::ZERO;


	if (true == GameEngineInput::IsPress(VK_LEFT) && Dir == PlayerDir::Left)
	{
		ChangeLowerAnimationState("Move");
		MovePos = { -Speed * _Delta, 0.0f };
	}
	else if (true == GameEngineInput::IsPress(VK_RIGHT) && Dir == PlayerDir::Right)
	{
		ChangeLowerAnimationState("Move");
		MovePos = { Speed * _Delta, 0.0f };
	}

	if (MovePos == float4::ZERO)
	{
		DirCheck();
		//ChangeLowerState(PlayerLowerState::Idle);
		ChangeLowerState(PlayerLowerState::MoveStop);
		return;
	}

	AddPos(MovePos);
}

void Player::MoveUpperStart() 
{
	ChangeUpperAnimationState("Move");
}
void Player::MoveUpperUpdate(float _Delta) 
{
	float Speed = 300.0f;
	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress(VK_LEFT) && Dir == PlayerDir::Left)
	{
		ChangeUpperAnimationState("Move");
		MovePos = { -Speed * _Delta, 0.0f };
	}
	else if (true == GameEngineInput::IsPress(VK_RIGHT) && Dir == PlayerDir::Right)
	{
		ChangeUpperAnimationState("Move");
		MovePos = { Speed * _Delta, 0.0f };
	}

	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChangeUpperState(PlayerUpperState::Idle);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_UP))
	{
		ChangeUpperState(PlayerUpperState::LookUp);
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeUpperState(PlayerUpperState::MoveJump);
		return;
	}

	if (true == GameEngineInput::IsDown('A'))
	{
		PrevState = "Move";

		DirCheck();

		ChangeUpperState(PlayerUpperState::Fire);
	}

	if (true == GameEngineInput::IsDown('D'))
	{
		PrevState = "Move";

		ChangeUpperState(PlayerUpperState::Granade);
	}
}

void Player::IdleJumpLowerStart()
{
	SetGravityVector(float4::UP * 1000.0f);
	ChangeLowerAnimationState("IdleJump");
}
void Player::IdleJumpLowerUpdate(float _Delta)
{
	DirCheck();
	Gravity(_Delta);

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));

		if (Color != RGB(255, 255, 255))
		{
			ChangeLowerState(PlayerLowerState::Idle);
			return;
		}
	}
}

void Player::IdleJumpUpperStart()
{
	ChangeUpperAnimationState("IdleJump");
}
void Player::IdleJumpUpperUpdate(float _Delta)
{
	if (LowerRenderer->IsAnimation("Right_Lower_Idle") || LowerRenderer->IsAnimation("Left_Lower_Idle"))
	{
		ChangeUpperState(PlayerUpperState::Idle);
	}

	if (true == GameEngineInput::IsDown('A'))
	{
		ChangeUpperState(PlayerUpperState::Fire);
	}

	if (true == GameEngineInput::IsDown('D'))
	{
		ChangeUpperState(PlayerUpperState::Granade);
	}

	if (true == GameEngineInput::IsDown(VK_DOWN))
	{
		ChangeUpperState(PlayerUpperState::JumpLookDown);
	}
}

void Player::MoveJumpLowerStart()
{
	SetGravityVector(float4::UP * 1000.0f);
	ChangeLowerAnimationState("MoveJump");
}
void Player::MoveJumpLowerUpdate(float _Delta)
{
	DirCheck();
	Gravity(_Delta);

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));

		if (Color != RGB(255, 255, 255))
		{
			ChangeLowerState(PlayerLowerState::Idle);
			return;
		}
	}

	float Speed = 300.0f;

	float4 MovePos = float4::ZERO;


	if (true == GameEngineInput::IsPress(VK_LEFT) && Dir == PlayerDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}
	else if (true == GameEngineInput::IsPress(VK_RIGHT) && Dir == PlayerDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
	}

	AddPos(MovePos);
}

void Player::MoveJumpUpperStart()
{
	ChangeUpperAnimationState("MoveJump");
}
void Player::MoveJumpUpperUpdate(float _Delta)
{
	if (LowerRenderer->IsAnimation("Right_Lower_Idle") || LowerRenderer->IsAnimation("Left_Lower_Idle"))
	{
		ChangeUpperState(PlayerUpperState::Idle);
	}

	if (true == GameEngineInput::IsDown('A'))
	{
		ChangeUpperState(PlayerUpperState::Fire);
	}

	if (true == GameEngineInput::IsDown('D'))
	{
		ChangeUpperState(PlayerUpperState::Granade);
	}

	if (true == GameEngineInput::IsDown(VK_DOWN))
	{
		ChangeUpperState(PlayerUpperState::JumpLookDown);
	}
}

//if (0 != GetAsyncKeyState('F'))
//{
//	Bullet* NewBullet = GetLevel()->CreateActor<Bullet>();
//	NewBullet->Renderer->SetTexture("Test.Bmp");
//	// 방향을 표현하는 xy는 크기가 1이어야 합니다.
//	NewBullet->SetDir(float4::RIGHT);
//	NewBullet->SetPos(GetPos());
//}

void Player::FireStart()
{
	MachineGunCount = 4;
	ChangeUpperAnimationState("Fire");
	

	if (RifleDir == PlayerRifleBulletDir::Right)
	{
		RifleBulletDir = float4::RIGHT;
	}
	if (RifleDir == PlayerRifleBulletDir::RightUp90)
	{
		RifleBulletDir = float4::UP;
	}

	BulletFire();
}
void Player::FireUpdate(float _Delta)
{
	
	if (true == GameEngineInput::IsDown(VK_LEFT) || true == GameEngineInput::IsDown(VK_RIGHT))
	{
		ChangeUpperState(PlayerUpperState::Move);
	}

	if (WeaponName == "Rifle_" && MachineGunCount != 0 && UpperRenderer->IsAnimationEnd())
	{
		ChangeUpperAnimationState("Fire", true);
		BulletFire();
		
	}
	else if (WeaponName == "Rifle_" && MachineGunCount <= 0)
	{
		ChangeUpperState(PlayerUpperState::Idle);
	}

	if (WeaponName == "Rifle_" &&
		GameEngineInput::IsDown(VK_UP))
	{
		ChangeUpperState(PlayerUpperState::LookUpFire);
	}

	if (WeaponName == "Rifle_" &&
		RifleDir == PlayerRifleBulletDir::RightUp90 &&
		GameEngineInput::IsFree(VK_UP))
	{
		ChangeUpperState(PlayerUpperState::LookDownFire);
	}


	if (true == GameEngineInput::IsDown('A'))
	{	
		MachineGunCount = 4;
		ChangeUpperAnimationState("Fire", true);
		BulletFire();
	}

	if (true == GameEngineInput::IsDown('D'))
	{
		ChangeUpperState(PlayerUpperState::Granade);
	}

	if (true == UpperRenderer->IsAnimationEnd())
	{
		if (LowerRenderer->IsAnimation("Right_Lower_Idle") || LowerRenderer->IsAnimation("Left_Lower_Idle"))
		{
			if (true == GameEngineInput::IsPress(VK_UP))
			{
				ChangeUpperState(PlayerUpperState::UpIdle);
			}
			else
			{
				ChangeUpperState(PlayerUpperState::Idle);
			}
		}
		else if (LowerRenderer->IsAnimation("Right_Lower_Move") || LowerRenderer->IsAnimation("Left_Lower_Move"))
		{
			ChangeUpperState(PlayerUpperState::Move);
		}

	}
}

void Player::GranadeStart()
{
	ChangeUpperAnimationState("Granade");

	{
		Granade* NewGranade = GetLevel()->CreateActor<Granade>();

		NewGranade->SetGroundTexture("Mission1_Debug_Test.bmp");
		

		float4 Pos = GetPos();

		//Pos.X += 132;
		Pos.Y -= 92;

		NewGranade->SetPos(Pos);
	}
}

void Player::GranadeUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown('A'))
	{
		ChangeUpperState(PlayerUpperState::Fire);
	}

	if (true == UpperRenderer->IsAnimationEnd())
	{
		
		//if (PrevState == "Idle")
		if (LowerRenderer->IsAnimation("Right_Lower_Idle") || LowerRenderer->IsAnimation("Left_Lower_Idle"))
		{
			ChangeUpperState(PlayerUpperState::Idle);
		}
		//else if (PrevState == "Move")
		else if (LowerRenderer->IsAnimation("Right_Lower_Move") || LowerRenderer->IsAnimation("Left_Lower_Move"))
		{
			ChangeUpperState(PlayerUpperState::Move);
		}

	}
}

void Player::LookUpStart()
{
	ChangeUpperAnimationState("LookUp");
}
void Player::LookUpUpdate(float _Delta)
{
	if (true == UpperRenderer->IsAnimationEnd() && true == GameEngineInput::IsPress(VK_UP))
	{
		ChangeUpperState(PlayerUpperState::UpIdle);
	}
	if (true == GameEngineInput::IsFree(VK_UP))
	{
		ChangeUpperState(PlayerUpperState::LookDown);
	}
	if (true == GameEngineInput::IsDown('A'))
	{
		ChangeUpperState(PlayerUpperState::Fire);
	}
	if (true == GameEngineInput::IsDown('S'))
	{
		ChangeUpperState(PlayerUpperState::LookDown);
	}
}

void Player::UpIdleStart()
{
	ChangeUpperAnimationState("Idle1");
}
void Player::UpIdleUpdate(float _Delta)
{
	if (true == GameEngineInput::IsFree(VK_UP))
	{
		ChangeUpperState(PlayerUpperState::LookDown);
	}
	if (true == GameEngineInput::IsDown('S'))
	{
		ChangeUpperState(PlayerUpperState::LookDown);
	}
	if (true == GameEngineInput::IsDown('A'))
	{
		ChangeUpperState(PlayerUpperState::Fire);
	}
	if (true == UpperRenderer->IsAnimationEnd())
	{
		if (UpperRenderer->IsAnimation("RightUp_Pistol_Upper_Idle1") || UpperRenderer->IsAnimation("LeftUp_Pistol_Upper_Idle1"))
		{
			ChangeUpperAnimationState("Idle2");
		}
		else if (UpperRenderer->IsAnimation("RightUp_Pistol_Upper_Idle2") || UpperRenderer->IsAnimation("LeftUp_Pistol_Upper_Idle2"))
		{
			ChangeUpperAnimationState("Idle1");
		}
	}
}

void Player::LookDownStart()
{
	ChangeUpperAnimationState("LookDown");
}
void Player::LookDownUpdate(float _Delta)
{
	if (true == UpperRenderer->IsAnimationEnd())
	{
		if (LowerRenderer->IsAnimation("Right_Lower_Idle") || LowerRenderer->IsAnimation("Left_Lower_Idle"))
		{
			ChangeUpperState(PlayerUpperState::Idle);
		}
		else if (LowerRenderer->IsAnimation("Right_Lower_Move") || LowerRenderer->IsAnimation("Left_Lower_Move"))
		{
			ChangeUpperState(PlayerUpperState::Move);
		}

		if (LowerRenderer->IsAnimation("Right_Lower_IdleJump") ||
			LowerRenderer->IsAnimation("Left_Lower_IdleJump") ||
			LowerRenderer->IsAnimation("Right_Lower_MoveJump") ||
			LowerRenderer->IsAnimation("Left_Lower_MoveJump"))
		{
			ChangeUpperAnimationState("Idle");
		}
	}
}

void Player::JumpLookDownStart()
{
	ChangeUpperAnimationState("JumpLookDown");
}
void Player::JumpLookDownUpdate(float _Delta)
{
	if (true == UpperRenderer->IsAnimationEnd() && true == GameEngineInput::IsPress(VK_DOWN))
	{
		ChangeUpperState(PlayerUpperState::DownIdle);
	}
	if (true == GameEngineInput::IsFree(VK_DOWN))
	{
		ChangeUpperState(PlayerUpperState::JumpLookUp);
	}
	if (true == GameEngineInput::IsDown('A'))
	{
		ChangeUpperState(PlayerUpperState::Fire);
	}
}

void Player::DownIdleStart()
{
	ChangeUpperAnimationState("Idle");
}
void Player::DownIdleUpdate(float _Delta)
{
	if (true == GameEngineInput::IsFree(VK_DOWN))
	{
		ChangeUpperState(PlayerUpperState::JumpLookUp);
	}
	if (true == GameEngineInput::IsDown('A'))
	{
		ChangeUpperState(PlayerUpperState::Fire);
	}
}

void Player::JumpLookUpStart()
{
	ChangeUpperAnimationState("JumpLookUp");
}
void Player::JumpLookUpUpdate(float _Delta)
{
	if (true == UpperRenderer->IsAnimationEnd())
	{
		if (LowerRenderer->IsAnimation("Right_Lower_IdleJump") || LowerRenderer->IsAnimation("Left_Lower_IdleJump"))
		{
			ChangeUpperState(PlayerUpperState::IdleJump);
		}
		else if (LowerRenderer->IsAnimation("Right_Lower_MoveJump") || LowerRenderer->IsAnimation("Left_Lower_MoveJump"))
		{
			ChangeUpperState(PlayerUpperState::MoveJump);
		}
	}
}

void Player::MoveStopStart()
{
	UpperRenderer->Off();
	ChangeLowerAnimationState("MoveStop1", true);
}
void Player::MoveStopUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown(VK_LEFT) || true == GameEngineInput::IsDown(VK_RIGHT))
	{
		DirCheck();
		ChangeLowerState(PlayerLowerState::Move);
		UpperRenderer->On();
		ChangeUpperState(PlayerUpperState::Move);
	}

	if (true == GameEngineInput::IsDown('A'))
	{
		ChangeLowerState(PlayerLowerState::Idle);
		UpperRenderer->On();
		ChangeUpperState(PlayerUpperState::Fire);
	}

	if (true == GameEngineInput::IsDown('D'))
	{
		ChangeLowerState(PlayerLowerState::Idle);
		UpperRenderer->On();
		ChangeUpperState(PlayerUpperState::Granade);
	}

	if (true == LowerRenderer->IsAnimationEnd())
	{
		if (true == LowerRenderer->IsAnimation("Right_Pistol_Lower_MoveStop1") ||
			true == LowerRenderer->IsAnimation("Left_Pistol_Lower_MoveStop1") ||
			true == LowerRenderer->IsAnimation("Right_Rifle_Lower_MoveStop1") ||
			true == LowerRenderer->IsAnimation("Left_Rifle_Lower_MoveStop1"))
		{
			ChangeLowerAnimationState("MoveStop2", true);
		}
		else if (true == LowerRenderer->IsAnimation("Right_Pistol_Lower_MoveStop2") ||
			true == LowerRenderer->IsAnimation("Left_Pistol_Lower_MoveStop2") ||
			true == LowerRenderer->IsAnimation("Right_Rifle_Lower_MoveStop2") ||
			true == LowerRenderer->IsAnimation("Left_Rifle_Lower_MoveStop2"))
		{
			ChangeLowerState(PlayerLowerState::Idle);
			UpperRenderer->On();
			ChangeUpperState(PlayerUpperState::Idle);
		}
	}
}

void Player::SitDownStart()
{
	UpperRenderer->Off();
	ChangeLowerAnimationState("SitDown", true);
}
void Player::SitDownUpdate(float _Delta)
{
	if (true == LowerRenderer->IsAnimationEnd())
	{
		if (true == GameEngineInput::IsPress(VK_DOWN))
		{
			ChangeLowerState(PlayerLowerState::SitIdle);
		}
	}
	if (true == GameEngineInput::IsUp(VK_DOWN))
	{
		ChangeLowerState(PlayerLowerState::SitUp);
	}
}

void Player::SitUpStart()
{
	ChangeLowerAnimationState("SitUp", true);
}
void Player::SitUpUpdate(float _Delta)
{
	if (true == LowerRenderer->IsAnimationEnd())
	{
		ChangeLowerState(PlayerLowerState::Idle);
		UpperRenderer->On();
		ChangeUpperState(PlayerUpperState::Idle);
	}
}

void Player::SitIdleStart()
{
	ChangeLowerAnimationState("SitIdle1", true);
}
void Player::SitIdleUpdate(float _Delta)
{
	if (true == LowerRenderer->IsAnimationEnd())
	{
		if (true == LowerRenderer->IsAnimation("Right_Pistol_Lower_SitIdle1") || true == LowerRenderer->IsAnimation("Left_Pistol_Lower_SitIdle1"))
		{
			ChangeLowerAnimationState("SitIdle2", true);
		}
		else if (true == LowerRenderer->IsAnimation("Right_Pistol_Lower_SitIdle2") || true == LowerRenderer->IsAnimation("Left_Pistol_Lower_SitIdle2"))
		{
			ChangeLowerAnimationState("SitIdle1", true);
		}
	}

	if (true == GameEngineInput::IsPress(VK_DOWN))
	{
		if (true == GameEngineInput::IsPress(VK_LEFT) || true == GameEngineInput::IsPress(VK_RIGHT))
		{
			DirCheck();
			ChangeLowerState(PlayerLowerState::SitMove);
		}
		
		if (true == GameEngineInput::IsDown('A'))
		{
			ChangeLowerState(PlayerLowerState::SitFire);
		}

		if (true == GameEngineInput::IsDown('D'))
		{
			ChangeLowerState(PlayerLowerState::SitGranade);
		}
	}

	if (true == GameEngineInput::IsFree(VK_DOWN))
	{
		ChangeLowerState(PlayerLowerState::SitUp);
	}
}

void Player::SitMoveStart()
{
	ChangeLowerAnimationState("SitMove", true);
}
void Player::SitMoveUpdate(float _Delta)
{
	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);
		}
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255, 255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}

			GravityReset();
		}
	}

	DirCheck();

	float Speed = 120.0f;
	//float Speed = 1.0f;

	float4 MovePos = float4::ZERO;
	if (true == GameEngineInput::IsPress(VK_DOWN))
	{
		if (true == GameEngineInput::IsPress(VK_LEFT) && Dir == PlayerDir::Left)
		{
			ChangeLowerAnimationState("SitMove", true);
			MovePos = { -Speed * _Delta, 0.0f };
		}
		else if (true == GameEngineInput::IsPress(VK_RIGHT) && Dir == PlayerDir::Right)
		{
			ChangeLowerAnimationState("SitMove", true);
			MovePos = { Speed * _Delta, 0.0f };
		}

		if (true == GameEngineInput::IsDown('A'))
		{
			ChangeLowerState(PlayerLowerState::SitFire);
		}

		if (true == GameEngineInput::IsDown('D'))
		{
			ChangeLowerState(PlayerLowerState::SitGranade);
		}
	}

	if (true == GameEngineInput::IsFree(VK_DOWN))
	{
		ChangeLowerState(PlayerLowerState::SitUp);
	}

	if (MovePos == float4::ZERO)
	{
		ChangeLowerState(PlayerLowerState::SitIdle);
	}

	AddPos(MovePos);

	
	

	
	
}

void Player::SitFireStart()
{
	ChangeLowerAnimationState("SitFire", true);
}
void Player::SitFireUpdate(float _Delta)
{
	DirCheck();

	if (true == GameEngineInput::IsPress(VK_DOWN))
	{
		if (true == GameEngineInput::IsDown('A'))
		{
			ChangeLowerAnimationState("SitFire", true, true);
		}

		if (true == GameEngineInput::IsDown('D'))
		{
			ChangeLowerState(PlayerLowerState::SitGranade);
		}

		if (true == LowerRenderer->IsAnimationEnd())
		{
			ChangeLowerState(PlayerLowerState::SitFireIdle);
		}
	}

	if (true == GameEngineInput::IsFree(VK_DOWN))
	{
		ChangeLowerState(PlayerLowerState::SitUp);
	}
}

void Player::SitFireIdleStart()
{
	ChangeLowerAnimationState("SitFireIdle1", true);
}
void Player::SitFireIdleUpdate(float _Delta)
{
	if (true == GameEngineInput::IsPress(VK_DOWN))
	{
		if (true == GameEngineInput::IsPress(VK_LEFT) || true == GameEngineInput::IsPress(VK_RIGHT))
		{
			DirCheck();
			ChangeLowerState(PlayerLowerState::SitMove);
		}

		if (true == GameEngineInput::IsDown('A'))
		{
			ChangeLowerState(PlayerLowerState::SitFire);
		}

		if (true == GameEngineInput::IsDown('D'))
		{
			ChangeLowerState(PlayerLowerState::SitGranade);
		}

		if (true == LowerRenderer->IsAnimationEnd())
		{
			if (true == LowerRenderer->IsAnimation("Right_Pistol_Lower_SitFireIdle1") || true == LowerRenderer->IsAnimation("Left_Pistol_Lower_SitFireIdle1"))
			{
				ChangeLowerAnimationState("SitFireIdle2", true);
			}
			else if (true == LowerRenderer->IsAnimation("Right_Pistol_Lower_SitFireIdle2") || true == LowerRenderer->IsAnimation("Left_Pistol_Lower_SitFireIdle2"))
			{
				ChangeLowerAnimationState("SitFireIdle1", true);
			}
		}
	}

	if (true == GameEngineInput::IsFree(VK_DOWN))
	{
		ChangeLowerState(PlayerLowerState::SitUp);
	}
}

void Player::SitGranadeStart()
{
	ChangeLowerAnimationState("SitGranade", true);
}
void Player::SitGranadeUpdate(float _Delta)
{
	if (true == GameEngineInput::IsPress(VK_DOWN))
	{
		if (true == GameEngineInput::IsDown('A'))
		{
			ChangeLowerState(PlayerLowerState::SitFire);
		}

		if (true == GameEngineInput::IsDown('D'))
		{
			ChangeLowerState(PlayerLowerState::SitGranade);
		}

		if (true == LowerRenderer->IsAnimationEnd())
		{
			ChangeLowerState(PlayerLowerState::SitGranadeIdle);
		}
	}

	if (true == GameEngineInput::IsFree(VK_DOWN))
	{
		ChangeLowerState(PlayerLowerState::SitUp);
	}
}

void Player::SitGranadeIdleStart()
{
	ChangeLowerAnimationState("SitGranadeIdle1", true);
}
void Player::SitGranadeIdleUpdate(float _Delta)
{
	if (true == GameEngineInput::IsPress(VK_DOWN))
	{
		if (true == GameEngineInput::IsPress(VK_LEFT) || true == GameEngineInput::IsPress(VK_RIGHT))
		{
			DirCheck();
			ChangeLowerState(PlayerLowerState::SitMove);
		}

		if (true == GameEngineInput::IsDown('A'))
		{
			ChangeLowerState(PlayerLowerState::SitFire);
		}

		if (true == GameEngineInput::IsDown('D'))
		{
			ChangeLowerState(PlayerLowerState::SitGranade);
		}

		if (true == LowerRenderer->IsAnimationEnd())
		{
			if (true == LowerRenderer->IsAnimation("Right_Pistol_Lower_SitGranadeIdle1") || true == LowerRenderer->IsAnimation("Left_Pistol_Lower_SitGranadeIdle1"))
			{
				ChangeLowerAnimationState("SitGranadeIdle2", true);
			}
			else if (true == LowerRenderer->IsAnimation("Right_Pistol_Lower_SitGranadeIdle2") || true == LowerRenderer->IsAnimation("Left_Pistol_Lower_SitGranadeIdle2"))
			{
				ChangeLowerAnimationState("SitGranadeIdle1", true);
			}
		}
	}

	if (true == GameEngineInput::IsFree(VK_DOWN))
	{
		ChangeLowerState(PlayerLowerState::SitUp);
	}
}

void Player::MeleeAttStart()
{
	ChangeUpperAnimationState("MeleeAtt2");

	
}
void Player::MeleeAttUpdate(float _Delta)
{
	if (UpperRenderer->IsAnimationEnd())
	{
		if (UpperRenderer->IsAnimation("Right_Pistol_Upper_MeleeAtt1") ||
			UpperRenderer->IsAnimation("Left_Pistol_Upper_MeleeAtt1"))
		{
			ChangeUpperAnimationState("MeleeAtt1End");
		}
		else if(UpperRenderer->IsAnimation("Right_Pistol_Upper_MeleeAtt1End") ||
			UpperRenderer->IsAnimation("Left_Pistol_Upper_MeleeAtt1End"))
		{
			ChangeUpperState(PlayerUpperState::Idle);
		}

	}
}

void Player::RangeDeathJumpStart()
{
	if (Dir == PlayerDir::Right)
	{
		float4 GravityDir = (float4::UP * 2.0f);
		GravityDir += (float4::LEFT * 0.25f);
		SetGravityVector(GravityDir * 500.0f);
	}
	else if(Dir == PlayerDir::Left)
	{
		float4 GravityDir = (float4::UP * 2.0f);
		GravityDir += (float4::RIGHT * 0.25f);
		SetGravityVector(GravityDir * 500.0f);
	}
	
	UpperRenderer->Off();
	ChangeLowerAnimationState("RangeDeathJump", false);
}
void Player::RangeDeathJumpUpdate(float _Delta)
{
	{
		Gravity(_Delta);
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) == Color)
		{
			
		}
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255, 255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);
				AddPos(float4::UP);
			}

			if (LowerRenderer->IsAnimationEnd())
			{
				ChangeLowerState(PlayerLowerState::RangeDeathGround);
			}

			GravityReset();
		}
	}
	if (LowerRenderer->IsAnimationEnd())
	{
		ChangeLowerState(PlayerLowerState::RangeDeathGround);
	}
}

void Player::RangeDeathGroundStart()
{
	ChangeLowerAnimationState("RangeDeathGround", false);
}
void Player::RangeDeathGroundUpdate(float _Delta)
{
	if (true == LowerRenderer->IsAnimationEnd())
	{
		ChangeLowerState(PlayerLowerState::Idle);
		UpperRenderer->On();
		ChangeUpperState(PlayerUpperState::Idle);
	}
}

void Player::MeleeDeathStart()
{
	UpperRenderer->Off();
	ChangeLowerAnimationState("MeleeDeath", false);
}
void Player::MeleeDeathUpdate(float _Delta)
{
	if (true == LowerRenderer->IsAnimationEnd())
	{
		ChangeLowerState(PlayerLowerState::Idle);
		UpperRenderer->On();
		ChangeUpperState(PlayerUpperState::Idle);
	}
}

void Player::SwordDeathStart()
{
	UpperRenderer->Off();
	ChangeLowerAnimationState("SwordDeath", false);
}
void Player::SwordDeathUpdate(float _Delta)
{
	if (true == LowerRenderer->IsAnimationEnd())
	{
		ChangeLowerState(PlayerLowerState::Idle);
		UpperRenderer->On();
		ChangeUpperState(PlayerUpperState::Idle);
	}
}

void Player::LookUpFireStart()
{
	ChangeUpperAnimationState("LookUpFire1", true);
	RifleBulletDir.X -= 0.1f;
	RifleBulletDir.Y -= BulletPlusDir;
	BulletFire();
}
void Player::LookUpFireUpdate(float _Delta)
{

	
	if (UpperRenderer->IsAnimationEnd())
	{
		if (UpperRenderer->IsAnimation("Right_Rifle_Upper_LookUpFire1"))
		{
			RifleBulletDir.X -= 0.1f;
			RifleBulletDir.Y -= BulletPlusDir;
			BulletFire();
			ChangeUpperAnimationState("LookUpFire2", true);
			
		}
		if (UpperRenderer->IsAnimation("Right_Rifle_Upper_LookUpFire2"))
		{
			RifleBulletDir.X -= 0.1f;
			RifleBulletDir.Y -= BulletPlusDir;
			BulletFire();
			ChangeUpperAnimationState("LookUpFire3", true);
			
		}
		if (UpperRenderer->IsAnimation("Right_Rifle_Upper_LookUpFire3"))
		{
			RifleBulletDir.X -= 0.1f;
			RifleBulletDir.Y -= BulletPlusDir;
			BulletFire();
			ChangeUpperState(PlayerUpperState::Fire);
			
		}
	}
}

void Player::LookDownFireStart()
{
	ChangeUpperAnimationState("LookDownFire1", true);
	RifleBulletDir.X += BulletPlusDir;
	RifleBulletDir.Y += 0.1f;
	BulletFire();
}
void Player::LookDownFireUpdate(float _Delta)
{
	
	if (UpperRenderer->IsAnimationEnd())
	{
		if (UpperRenderer->IsAnimation("Right_Rifle_Upper_LookDownFire1"))
		{
			RifleBulletDir.X += BulletPlusDir;
			RifleBulletDir.Y += 0.1f;
			BulletFire();
			ChangeUpperAnimationState("LookDownFire2", true);

		}
		if (UpperRenderer->IsAnimation("Right_Rifle_Upper_LookDownFire2"))
		{
			RifleBulletDir.X += BulletPlusDir;
			RifleBulletDir.Y += 0.1f;
			BulletFire();
			ChangeUpperAnimationState("LookDownFire3", true);

		}
		if (UpperRenderer->IsAnimation("Right_Rifle_Upper_LookDownFire3"))
		{
			RifleBulletDir.X += BulletPlusDir;
			RifleBulletDir.Y += 0.1f;
			BulletFire();
			ChangeUpperState(PlayerUpperState::Fire);

		}
	}
}