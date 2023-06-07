#include "Player.h"
#include <GameEnginePlatform/GameEngineInput.h>

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

			GravityReset();
		}
	}

	// if (true == GameEngineInput::IsDown('A') || true == GameEngineInput::IsDown('D'))
	if(true == GameEngineInput::IsDown(VK_LEFT) || true == GameEngineInput::IsDown(VK_RIGHT))
	{
		DirCheck();
		ChangeState(PlayerState::Move);
		return;
	}

	if (true == GameEngineInput::IsDown('S'))
	{
		ChangeState(PlayerState::IdleJump);
		return;
	}
	
}

void Player::MoveStart()
{
	ChangeAnimationState("Move");
}

void Player::MoveUpdate(float _Delta)
{
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

			if (true == GameEngineInput::IsDown('S'))
			{
				ChangeState(PlayerState::MoveJump);
				return;
			}

			GravityReset();
		}
	}

	DirCheck();

	float Speed = 100.0f;

	float4 MovePos = float4::ZERO;
	

	if (true == GameEngineInput::IsPress('A') && Dir == PlayerDir::Left)
	{
		MovePos = { -Speed * _Delta, 0.0f };
	}
	else if (true == GameEngineInput::IsPress('D') && Dir == PlayerDir::Right)
	{
		MovePos = { Speed * _Delta, 0.0f };
	}
	
	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChangeState(PlayerState::Idle);
		return;
	}

	AddPos(MovePos);
}

void Player::IdleJumpStart()
{
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
	ChangeAnimationState("MoveJump");
}

void Player::MoveJumpUpdate(float _Delta)
{
	Gravity(_Delta);

	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));

		if (Color != RGB(255, 255, 255))
		{
			// �ٷ� Idle�� ���°� �³�? Move�� ���°� �³�?
			// ChangeState(PlayerState::Move);
			return;
		}
	}
}
