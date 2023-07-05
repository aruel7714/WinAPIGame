#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class TruckState
{
	Idle,
	Drive,
	Deploy,
	Destroy,
	Max
};

// Ό³Έν : 
class Truck : public GameEngineActor
{
public:
	// constrcuter destructer
	Truck();
	~Truck();

	// delete Function
	Truck(const Truck & _Other) = delete;
	Truck(Truck && _Other) noexcept = delete;
	Truck& operator=(const Truck & _Other) = delete;
	Truck& operator=(Truck && _Other) noexcept = delete;

protected:
	TruckState State = TruckState::Max;

	void ChangeState(TruckState _State);
	void StateUpdate(float _Delta);

	void ChangeAnimationState(const std::string& _State);

	void IdleStart();
	void IdleUpdate(float _Delat);

	void DriveStart();
	void DriveUpdate(float _Delta);

	void DeployStart();
	void DeployUpdate(float _Delta);

	void DestroyStart();
	void DestroyUpdate(float _Delta);

private:
	GameEngineRenderer* TruckRenderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};

