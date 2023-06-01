#pragma once

// Ό³Έν : 
class PlayerLowerRender
{
public:
	// constrcuter destructer
	PlayerLowerRender();
	~PlayerLowerRender();

	// delete Function
	PlayerLowerRender(const PlayerLowerRender & _Other) = delete;
	PlayerLowerRender(PlayerLowerRender && _Other) noexcept = delete;
	PlayerLowerRender& operator=(const PlayerLowerRender & _Other) = delete;
	PlayerLowerRender& operator=(PlayerLowerRender && _Other) noexcept = delete;

protected:

private:

};

