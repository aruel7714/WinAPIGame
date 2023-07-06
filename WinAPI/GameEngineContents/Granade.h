#pragma once
#include "PlayActor.h"
#include <GameEnginePlatform/GameEngineSound.h>

enum class GranadeState
{
	Fire,
	Bound,
	Explosion,
	ExplosionEnd,
	Max
};

enum class GranadeDir
{
	Right,
	Left,
	Max
};

class Granade : public PlayActor
{
public:
	// constrcuter destructer
	Granade();
	~Granade();

	// delete Function
	Granade(const Granade & _Other) = delete;
	Granade(Granade && _Other) noexcept = delete;
	Granade& operator=(const Granade & _Other) = delete;
	Granade& operator=(Granade && _Other) noexcept = delete;

	GameEngineRenderer* GranadeRenderer = nullptr;

	GameEngineSoundPlayer BombSound;

protected:
	GranadeState State = GranadeState::Max;
	GranadeDir Dir = GranadeDir::Right;

	void ChangeState(GranadeState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void FireStart();
	void FireUpdate(float _Delta);

	void BoundStart();
	void BoundUpdate(float _Delta);

	void ExplosionStart();
	void ExplosionUpdate(float _Delta);

	void ExplosionEnd();

	float4 GravityDir = float4::ZERO;

private:
	void Start() override;
	void Update(float _Delta) override;

	GameEngineCollision* GranadeCollision = nullptr;
};

