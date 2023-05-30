#include "Player.h"
#include <GameEnginePlatform/GameEngineInput.h>

void Player::IdleStart() 
{
	ChangeAnimationState("Idle");
}

void Player::IdleUpdate(float _Delta)
{
	if (GameEngineInput::IsDown('A') ||
		GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChangeAnimationState("Run");
		return;
	}

	if (GameEngineInput::IsDown('W'))
	{
		ChangeAnimationState("Jump");
		return;
	}
}

void Player::RunStart()
{
	ChangeAnimationState("Run");
}

void Player::RunUpdate(float _Delta)
{

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
