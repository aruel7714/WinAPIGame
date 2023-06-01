#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class PlayerUpperRender : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerUpperRender();
	~PlayerUpperRender();

	// delete Function
	PlayerUpperRender(const PlayerUpperRender & _Other) = delete;
	PlayerUpperRender(PlayerUpperRender && _Other) noexcept = delete;
	PlayerUpperRender& operator=(const PlayerUpperRender & _Other) = delete;
	PlayerUpperRender& operator=(PlayerUpperRender && _Other) noexcept = delete;

	GameEngineRenderer* UpperRenderer = nullptr;

	void SetUpperRenderer();

protected:

private:

};

