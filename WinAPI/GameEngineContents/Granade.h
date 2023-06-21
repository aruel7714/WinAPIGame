#pragma once
#include "PlayActor.h"

enum class GranadeState
{
	Fire,
	Bound,
	Explosion,
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

private:
	void Start() override;
	void Update(float _Delta) override;
};

