#include "Player.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>

// 왼쪽 방향키 : 왼쪽 바라보기, 왼쪽으로 이동
// 오른쪽 방향키 : 오른쪽 바라보기, 오른쪽으로 이동
// 위쪽 방향키 : 위 바라보기
// 아래쪽 방향키 : 앉기
// A : Fire
// S : Jump
// D : Granade

/*
void Player::IdleStart() 
{
	ChangeAnimationState("Idle");
}

void Player::IdleUpdate(float _Delta)
{
	//ChangeAnimationState("Idle");
	// 중력
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
				ChangeState(PlayerState::IdleJump);
				return;
			}


			GravityReset();
		}
	}
	UpperRenderer->SetRenderPos({ 0, -92 });

	// if (true == GameEngineInput::IsDown('A') || true == GameEngineInput::IsDown('D'))
	if(true == GameEngineInput::IsPress(VK_LEFT) || true == GameEngineInput::IsPress(VK_RIGHT))
	{
		DirCheck();
		ChangeState(PlayerState::Move);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_UP))
	{
		// UpDia, Up, UpFire

		//ChangeUpperAnimationState("Dia");

		//if (true == UpperRenderer->IsAnimation(AnimationName))
		//{
		//	if (UpperRenderer->GetCurFrame() >=
		//		(UpperRenderer->FindAnimation(AnimationName)->EndFrame) -
		//		(UpperRenderer->FindAnimation(AnimationName)->StartFrame))
		//	{
		//		ChangeUpperAnimationState("Up");
		//	}
		//}
	}

	if (true == GameEngineInput::IsPress(VK_DOWN))
	{
		// 
	}
	
	//if (true == GameEngineInput::IsDown('A'))
	//{
	//	PrevState = "Idle";
	//	ChangeUpperAnimationState("Fire");
	//	return FireUpdate(_Delta);
	//}

	if (true == GameEngineInput::IsDown('A'))
	{
		//FireUpdate(_Delta);
		PrevState = "Idle";

		ChangeState(PlayerState::Fire);
		
	}

	if (true == GameEngineInput::IsDown('D'))
	{
		//Granade
	}

	//if (true == UpperRenderer->IsAnimation(AnimationName))
	//{
	//	if (UpperRenderer->GetCurFrame() >=
	//		(UpperRenderer->FindAnimation(AnimationName)->EndFrame) -
	//		(UpperRenderer->FindAnimation(AnimationName)->StartFrame))
	//	{
	//		ChangeUpperAnimationState("Idle");
	//	}
	//}
	

	
}

void Player::MoveStart()
{
	ChangeAnimationState("Move");
}

void Player::MoveUpdate(float _Delta)
{
	// 중력
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
				ChangeState(PlayerState::MoveJump);
				return;
			}

			GravityReset();
		}
	}
	//UpperRenderer->SetRenderPos({ 0, -96 });

	DirCheck();

	float Speed = 300.0f;
	//float Speed = 1.0f;

	float4 MovePos = float4::ZERO;
	

	if (true == GameEngineInput::IsPress(VK_LEFT) && Dir == PlayerDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
		//if (GameEngineInput::IsDown('A'))
		//{
		//	ChangeUpperAnimationState("Fire");
		//}
	}
	else if (true == GameEngineInput::IsPress(VK_RIGHT) && Dir == PlayerDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
		//if (GameEngineInput::IsDown('A'))
		//{
		//	ChangeUpperAnimationState("Fire");
		//}
	}

	//if (true == GameEngineInput::IsDown('A'))
	//{
	//	PrevState = "Move";
	//	ChangeUpperAnimationState("Fire");
	//	return FireUpdate(_Delta);
	//}
	
	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChangeState(PlayerState::Idle);
		return;
	}

	if (true == GameEngineInput::IsDown('A'))
	{
		PrevState = "Move";
		//ChangeUpperAnimationState("FireStart");
		//ChangeUpperAnimationState("Fire");
		ChangeState(PlayerState::Fire);
	}

	//if (true == UpperRenderer->IsAnimation(AnimationName))
	//{
	//	if (UpperRenderer->GetCurFrame() >=
	//		(UpperRenderer->FindAnimation(AnimationName)->EndFrame) -
	//		(UpperRenderer->FindAnimation(AnimationName)->StartFrame))
	//	{
	//		ChangeUpperAnimationState("Move");
	//	}
	//}



	AddPos(MovePos);
}

void Player::IdleJumpStart()
{
	SetGravityVector(float4::UP * 1200.0f);
	ChangeAnimationState("IdleJump");
}

void Player::IdleJumpUpdate(float _Delta)
{
	Gravity(_Delta);

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));

		if (Color != RGB(255, 255, 255))
		{
			ChangeState(PlayerState::Idle);
			return;
		}
	}

	if (true == GameEngineInput::IsDown('A'))
	{
		PrevState = "IdleJump";
		ChangeState(PlayerState::Fire);
	}
}

void Player::MoveJumpStart()
{
	SetGravityVector(float4::UP * 1200.0f);
	ChangeAnimationState("MoveJump");
}

void Player::MoveJumpUpdate(float _Delta)
{
	Gravity(_Delta);

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));

		if (Color != RGB(255, 255, 255))
		{
			ChangeState(PlayerState::Move);
			return;
		}
	}

	float Speed = 300.0f;
	//float Speed = 1.0f;

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

	if (true == GameEngineInput::IsDown('T'))
	{
		ChangeState(PlayerState::Idle);
		return;
	}
}

//void Player::FireUpdate(float _Delta)
//{
//	ChangeUpperAnimationState("FireStart");
//	ChangeUpperAnimationState("Fire");
//
//	if (true == UpperRenderer->IsAnimation(AnimationName))
//	{
//		if (UpperRenderer->GetCurFrame() >=
//			(UpperRenderer->FindAnimation(AnimationName)->EndFrame) -
//			(UpperRenderer->FindAnimation(AnimationName)->StartFrame))
//		{
//			IdleUpdate(_Delta);
//			//ChangeUpperAnimationState("Idle");
//		}
//	}
//
//	//ChangeUpperAnimationState(PrevState);
//}

*/






void Player::IdleLowerStart()
{
	UpperRenderer->SetRenderPos({ 0, -92 });
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
}

void Player::IdleUpperStart()
{
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

	}

	if (true == GameEngineInput::IsPress('S'))
	{
		ChangeUpperState(PlayerUpperState::IdleJump);
		return;
	}
	if (true == GameEngineInput::IsDown('A'))
	{
		//FireUpdate(_Delta);

		PrevState = "Idle";

		ChangeUpperState(PlayerUpperState::Fire);
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
		ChangeLowerState(PlayerLowerState::Idle);
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
	SetGravityVector(float4::UP * 1200.0f);
	ChangeLowerAnimationState("IdleJump");
}
void Player::IdleJumpLowerUpdate(float _Delta)
{
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
		PrevState = "IdleJump";
		ChangeUpperState(PlayerUpperState::Fire);
	}
}

void Player::MoveJumpLowerStart()
{
	SetGravityVector(float4::UP * 1200.0f);
	ChangeLowerAnimationState("MoveJump");
}
void Player::MoveJumpLowerUpdate(float _Delta)
{
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
		PrevState = "IdleJump";
		ChangeUpperState(PlayerUpperState::Fire);
	}
}

void Player::FireStart()
{
	ChangeUpperAnimationState("Fire");
}
void Player::FireUpdate(float _Delta)
{
	DirCheck();
	if (true == GameEngineInput::IsDown('A'))
	{
		ChangeUpperAnimationState("Fire", true);
	}

	if (true == UpperRenderer->IsAnimationEnd())
	{
		if (PrevState == "Idle")
		{
			ChangeUpperState(PlayerUpperState::Idle);
		}
		else if (PrevState == "Move")
		{
			ChangeUpperState(PlayerUpperState::Move);
		}
		else if (PrevState == "IdleJump")
		{
			ChangeUpperState(PlayerUpperState::IdleJump);
		}
	}
	
}

void Player::GranadeStart()
{
	ChangeUpperAnimationState("Granade");
}

void Player::GranadeUpdate(float _Delta)
{
	if(true == UpperRenderer->IsAnimationEnd())
	{
		if (PrevState == "Idle")
		{
			ChangeUpperState(PlayerUpperState::Idle);
		}
		else if (PrevState == "Move")
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
	if (true == UpperRenderer->IsAnimationEnd())
	{
		return;
	}
}