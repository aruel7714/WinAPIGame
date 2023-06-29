#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

enum class BossAttackState
{
	AttackBase, 
	AttackReady,
	Attack,
	AttackEnd,
	Max
};

// Ό³Έν : 
class FinalBoss : public GameEngineActor
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
	GameEngineRenderer* FinalBossAttackRenderer = nullptr;

	GameEngineCollision* FinalBossBodyCollision = nullptr;
	GameEngineCollision* FinalBossWingCollision = nullptr;
	GameEngineCollision* FinalBossLeftAttackCollision = nullptr;
	GameEngineCollision* FinalBossRightAttackCollision = nullptr;

protected:
	BossState State = BossState::Max;
	BossAttackState AttackState = BossAttackState::Max;

	void ChangeMainState(BossState _State);
	void MainStateUpdate(float _Delta);

	void ChangeAttackState(BossAttackState _AttackState);
	void AttackStateUpdate(float _Delta);

	void ChangeMainAnimationState(const std::string& _State);
	void ChangeAttackAnimationState(const std::string& _State);

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

	void AttackBaseStart();
	void AttackBaseUpdate(float _Delta);

	void AttackReadyStart();
	void AttackReadyUpdate(float _Delta);

	void AttackStart();
	void AttackUpdate(float _Delta);

	void AttackEndStart();
	void AttackEndUpdate(float _Delta);

private:
	void Start() override;
	void Update(float _Delta) override;
};

