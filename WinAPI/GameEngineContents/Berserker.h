#pragma once
#include "PlayActor.h"

enum class BerserkerState
{
	SitIdle,
	StandIdle,
	Move,
	Attack,
	Death,
	Max
};

// Ό³Έν : 
class Berserker : public PlayActor
{
public:
	// constrcuter destructer
	Berserker();
	~Berserker();

	// delete Function
	Berserker(const Berserker & _Other) = delete;
	Berserker(Berserker && _Other) noexcept = delete;
	Berserker& operator=(const Berserker & _Other) = delete;
	Berserker& operator=(Berserker && _Other) noexcept = delete;

protected:
	BerserkerState State = BerserkerState::Max;

	void ChangeState(BerserkerState _State);
	void StateUpdate(float _Delta);

	void ChangeAnimationState(const std::string& _State);

	void SitIdleStart();
	void SitIdleUpdate(float _Delta);

	void StandIdleStart();
	void StandIdleUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void DeathStart();
	void DeathUpdate(float _Delta);


private:
	GameEngineRenderer* BerserkerRenderer = nullptr;

	//GameEngineCollision* BerserkerCollision = nullptr;
	//GameEngineCollision* BerserkerMeleeAttCollision = nullptr;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
};

