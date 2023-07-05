#pragma once
#include "PlayActor.h"

enum class SwordState
{
	Throw,
	HitGround,
	Max
};

enum class SwordDir
{
	Left,
	Right,
};

// Ό³Έν : 
class ArabianSword : public PlayActor
{
public:
	// constrcuter destructer
	ArabianSword();
	~ArabianSword();

	// delete Function
	ArabianSword(const ArabianSword & _Other) = delete;
	ArabianSword(ArabianSword && _Other) noexcept = delete;
	ArabianSword& operator=(const ArabianSword & _Other) = delete;
	ArabianSword& operator=(ArabianSword && _Other) noexcept = delete;

	GameEngineRenderer* SwordRenderer = nullptr;

protected:
	SwordState State = SwordState::Max;
	SwordDir Dir = SwordDir::Left;

	void ChangeState(SwordState _State);
	void StateUpdate(float _Delta);
	void ChangeAnimationState(const std::string& _State);

	void ThrowStart();
	void ThrowUpdate(float _Delta);

	void HitGroundStart();
	void HitGroundUpdate(float _Delta);

	float4 GravityDir = float4::ZERO;

private:
	void Start() override;
	void Update(float _Delta) override;

	GameEngineCollision* SwordCollision = nullptr;
};

