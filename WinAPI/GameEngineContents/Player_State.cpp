#include "Player.h"
#include <GameEnginePlatform/GameEngineInput.h>

void Player::IdleStart() 
{
	ChangeAnimationState("Idle");
}

void Player::IdleUpdate(float _Delta)
{
	

	if (true == GameEngineInput::IsDown('A') ||
		true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChangeState(PlayerState::Move);
		return;
	}

	/*if (GameEngineInput::IsDown('W'))
	{
		ChangeState(PlayerState::Jump);
		return;
	}*/
}

void Player::MoveStart()
{
	ChangeAnimationState("Move");
}

void Player::MoveUpdate(float _Delta)
{
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

}

void Player::IdleJumpUpdate(float _Delta)
{

}

void Player::MoveJumpStart()
{

}

void Player::MoveJumpUpdate(float _Delta)
{

}
