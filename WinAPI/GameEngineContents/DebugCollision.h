#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class DebugCollision : public GameEngineActor
{
public:
	// constrcuter destructer
	DebugCollision();
	~DebugCollision();

	// delete Function
	DebugCollision(const DebugCollision& _Other) = delete;
	DebugCollision(DebugCollision&& _Other) noexcept = delete;
	DebugCollision& operator=(const DebugCollision& _Other) = delete;
	DebugCollision& operator=(DebugCollision&& _Other) noexcept = delete;

	GameEngineCollision* FocusCollision = nullptr;
protected:

private:
	void Start();
};

