#pragma once
#include "PlayActor.h"

// Ό³Έν : 
class HeavyMachineGun : public PlayActor
{
public:
	// constrcuter destructer
	HeavyMachineGun();
	~HeavyMachineGun();

	// delete Function
	HeavyMachineGun(const HeavyMachineGun & _Other) = delete;
	HeavyMachineGun(HeavyMachineGun && _Other) noexcept = delete;
	HeavyMachineGun& operator=(const HeavyMachineGun & _Other) = delete;
	HeavyMachineGun& operator=(HeavyMachineGun && _Other) noexcept = delete;

	GameEngineRenderer* ItemRenderer;
protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	GameEngineCollision* ItemCollision = nullptr;
};

