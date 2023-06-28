#pragma once
#include "PlayActor.h"

enum class BossState
{
	Pattern1,
	Pattern2,
	Pattern3,
	Pattern4,
	Pattern5,
	Pattern6,
	Pattern7,
	Destroy,
	Max
};

// Ό³Έν : 
class FinalBoss : PlayActor
{
public:
	// constrcuter destructer
	FinalBoss();
	~FinalBoss();

	// delete Function
	FinalBoss(const FinalBoss & _Other) = delete;
	FinalBoss(FinalBoss && _Other) noexcept = delete;
	FinalBoss& operator=(const FinalBoss & _Other) = delete;
	FinalBoss& operator=(FinalBoss && _Other) noexcept = delete;

	GameEngineRenderer* FinalBossRenderer = nullptr;

protected:
	BossState State = BossState::Max;
	void ChangeState(BossState _State);
	void StateUpdate(float _Delta);

	void ChangeAnimationState(const std::string& _State);

	void Pattern1Start();
	void Pattern1Update(float _Delta);

	void Pattern2Start();
	void Pattern2Update(float _Delta);

	void Pattern3Start();
	void Pattern3Update(float _Delta);

	void Pattern4Start();
	void Pattern4Update(float _Delta);

	void Pattern5Start();
	void Pattern5Update(float _Delta);

	void Pattern6Start();
	void Pattern6Update(float _Delta);

	void Pattern7Start();
	void Pattern7Update(float _Delta);

	void DestroyStart();
	void DestroyUpdate(float _Delta);

private:
	void Start() override;
};

