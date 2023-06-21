#pragma once
#include "PlayActor.h"

// Ό³Έν : 
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

private:
	void Start() override;
	void Update(float _Delta) override;
};

