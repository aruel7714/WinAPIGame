#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class MiddleBoss : public GameEngineActor
{
public:
	// constrcuter destructer
	MiddleBoss();
	~MiddleBoss();

	// delete Function
	MiddleBoss(const MiddleBoss & _Other) = delete;
	MiddleBoss(MiddleBoss && _Other) noexcept = delete;
	MiddleBoss& operator=(const MiddleBoss & _Other) = delete;
	MiddleBoss& operator=(MiddleBoss && _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;

	GameEngineRenderer* LeftRenderer = nullptr;
	GameEngineRenderer* MiddleRenderer = nullptr;
	GameEngineRenderer* RightRenderer = nullptr;



protected:

private:
	void Start() override;
	//void Update(float _Delta) override;
};

