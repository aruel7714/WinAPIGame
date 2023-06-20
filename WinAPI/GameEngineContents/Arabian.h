#pragma once
#include "PlayActor.h"

enum class ArabianState
{
	Idle,
	Ready,
	Move,
	Jump,
	BackStep,
	AttackReady,
	MeleeAttack,
	RangeAttack,
	Max
};

enum class ArabianDir
{
	Left,
	Right,
	Max
};

// ���� : 
class Arabian : public PlayActor
{
public:
	// constrcuter destructer
	Arabian();
	~Arabian();

	// delete Function
	Arabian(const Arabian & _Other) = delete;
	Arabian(Arabian && _Other) noexcept = delete;
	Arabian& operator=(const Arabian & _Other) = delete;
	Arabian& operator=(Arabian && _Other) noexcept = delete;

protected:
	ArabianState State = ArabianState::Max;
	ArabianDir Dir = ArabianDir::Left;

	void ChangeState(ArabianState _State);
	void StateUpdate(float _Delta);

	void ChangeAnimationState(const std::string& _State);

	void IdleStart();
	void IdleUpdate(float _Delta);

	//void ReadyStart();
	//void ReadyUpdate(float _Delta);

	//void Movestart();
	//void MoveUpdate(float _Delta);

	//void JumpStart();
	//void JumpUpdate(float _Delta);

private:
	static std::list<Arabian*> AllArabian;

	GameEngineRenderer* ArabianRenderer = nullptr;

	void Start() override;

	void Update(float _Delta) override;

	void Render(float _Delta) override;
};

