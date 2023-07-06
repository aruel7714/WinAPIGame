#pragma once
#include "PlayActor.h"
#include <GameEnginePlatform/GameEngineSound.h>

enum class ArabianState
{
	Idle,
	Ready,
	Move,
	JumpReady,
	Jump,
	BackStep,
	AttackReady,
	MeleeAttack,
	RangeAttack,
	RangeDeath,
	MeleeDeath,
	AirDeath,
	DeathEnd,
	Max
};

enum class ArabianDir
{
	Left,
	Right,
	Max
};

// ¼³¸í : 
class Arabian : public PlayActor
{
	friend class ArabianSword;
public:
	// constrcuter destructer
	Arabian();
	~Arabian();

	// delete Function
	Arabian(const Arabian & _Other) = delete;
	Arabian(Arabian && _Other) noexcept = delete;
	Arabian& operator=(const Arabian & _Other) = delete;
	Arabian& operator=(Arabian && _Other) noexcept = delete;

	void SetDir(int _Value)
	{
		if (_Value == 1)
		{
			Dir = ArabianDir::Left;
		}
		else if (_Value == 2)
		{
			Dir = ArabianDir::Right;
		}
	}

	GameEngineSoundPlayer Sound;

protected:
	ArabianState State = ArabianState::Max;
	//ArabianDir Dir = ArabianDir::Left;
	static ArabianDir Dir;

	void ChangeState(ArabianState _State);
	void StateUpdate(float _Delta);

	void ChangeAnimationState(const std::string& _State);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void ReadyStart();
	void ReadyUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void JumpReadyStart();
	void JumpReadyUpdate(float _Delta);

	void JumpStart();
	void JumpUpdate(float _Delta);

	void BackStepStart();
	void BackStepUpdate(float _Delta);

	void AttackReadyStart();
	void AttackReadyUpdate(float _Delta);
	
	void MeleeAttackStart();
	void MeleeAttackUpdate(float _Delta);
	
	void RangeAttackStart();
	void RangeAttackUpdate(float _Delta);

	void RangeDeathStart();
	void RangeDeathUpdate(float _Delta);

	void MeleeDeathStart();
	void MeleeDeathUpdate(float _Delta);

	void AirDeathStart();
	void AirDeathUpdate(float _Delta);

	void DeathEndStart();
	void DeathEndUpdate(float _Delta);

	void DeathCollisionCheck();

private:
	static std::list<Arabian*> AllArabian;

	GameEngineRenderer* ArabianRenderer = nullptr;

	GameEngineCollision* ArabianCollision = nullptr;
	GameEngineCollision* ArabianMeleeAttCollision = nullptr;

	void Start() override;

	void Update(float _Delta) override;

	void Render(float _Delta) override;
};

