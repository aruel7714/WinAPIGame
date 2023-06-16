#include "Player.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>

// ���� ����Ű : ���� �ٶ󺸱�, �������� �̵�
// ������ ����Ű : ������ �ٶ󺸱�, ���������� �̵�
// ���� ����Ű : �� �ٶ󺸱�
// �Ʒ��� ����Ű : �ɱ�
// A : Fire
// S : Jump
// D : Granade

void Player::IdleStart() 
{
	ChangeAnimationState("Idle");
}

void Player::IdleUpdate(float _Delta)
{
	//ChangeAnimationState("Idle");
	// �߷�
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

			if (true == GameEngineInput::IsPress('S'))
			{
				ChangeState(PlayerState::IdleJump);
				return;
			}


			GravityReset();
		}
	}

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

		ChangeState(PlayerState::Fire);
		
	}

	if (true == GameEngineInput::IsDown('D'))
	{
		//Granade
	}

	if (true == UpperRenderer->IsAnimation(AnimationName))
	{
		if (UpperRenderer->GetCurFrame() >=
			(UpperRenderer->FindAnimation(AnimationName)->EndFrame) -
			(UpperRenderer->FindAnimation(AnimationName)->StartFrame))
		{
			ChangeUpperAnimationState("Idle");
		}
	}
	

	
}

void Player::MoveStart()
{
	ChangeAnimationState("Move");
}

void Player::MoveUpdate(float _Delta)
{
	//ChangeAnimationState("Move");
	// �߷�
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
		ChangeUpperAnimationState("FireStart");
		ChangeUpperAnimationState("Fire");
	}

	if (true == UpperRenderer->IsAnimation(AnimationName))
	{
		if (UpperRenderer->GetCurFrame() >=
			(UpperRenderer->FindAnimation(AnimationName)->EndFrame) -
			(UpperRenderer->FindAnimation(AnimationName)->StartFrame))
		{
			ChangeUpperAnimationState("Move");
		}
	}



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


void Player::FireStart()
{
	ChangeUpperAnimationState("Fire");
}
void Player::FireUpdate(float _Delta)
{
	if (true == GameEngineInput::IsDown('A'))
	{
		ChangeUpperAnimationState("Fire", true);
	}

	if (true == UpperRenderer->IsAnimationEnd())
	{
		ChangeState(PlayerState::Idle);
	}
}