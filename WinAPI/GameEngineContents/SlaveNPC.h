#pragma once
#include "PlayActor.h"
#include <GameEnginePlatform/GameEngineSound.h>

enum class SlaveState
{
	CatchOn,
	CatchOff,
	Move,
	Gift,
	Greet,
	Run,
	Max,
};

enum class SlaveDir
{
	Left,
	Right,
	Max
};

enum class SlaveItem
{
	HeavyMachineGun,
	Max
};

// Ό³Έν : 
class SlaveNPC : public PlayActor
{
	friend class Stage1;
public:
	// constrcuter destructer
	SlaveNPC();
	~SlaveNPC();

	// delete Function
	SlaveNPC(const SlaveNPC & _Other) = delete;
	SlaveNPC(SlaveNPC && _Other) noexcept = delete;
	SlaveNPC& operator=(const SlaveNPC & _Other) = delete;
	SlaveNPC& operator=(SlaveNPC && _Other) noexcept = delete;

	GameEngineSoundPlayer Sound;

	void SetSlaveItem(SlaveItem _Item)
	{
		Item = _Item;
	}

	protected:
	SlaveState State = SlaveState::Max;
	SlaveDir Dir = SlaveDir::Left;
	SlaveItem Item = SlaveItem::Max;

	void SetDir(SlaveDir _Dir);

	void ChangeState(SlaveState _State);
	void StateUpdate(float _Delta);

	void ChangeAnimationState(const std::string& _State);

	void CatchOnStart();
	void CatchOnUpdate(float _Delta);

	void CatchOffStart();
	void CatchOffUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void GiftStart();
	void GiftUpdate(float _Delta);

	void GreetStart();
	void GreetUpdate(float _Delta);

	void RunStart();
	void RunUpdate(float _Delta);

private:
	static std::list<SlaveNPC*> AllSlave;

	GameEngineRenderer* SlaveRenderer = nullptr;
	
	GameEngineCollision* SlaveCatchOnCollision = nullptr;
	GameEngineCollision* SlaveCatchOffCollision = nullptr;

	class HeavyMachineGun* NewHeavyMachineGun = nullptr;

	void Start() override;

	void Update(float _Delta) override;
};

