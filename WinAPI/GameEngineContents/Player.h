#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class PlayerState
{
	Idle,
	Move,
	Jump,
	Sit,
	Max
};

enum class PlayerRenderOrder
{
	Lower,
	Upper
};

enum class PlayerDir
{
	Left,
	Right,
	Max
};

// Ό³Έν : 
class Player : public GameEngineActor
{
private:
	static Player* MainPlayer;

public:
	static Player* GetMainPlayer()
	{
		return MainPlayer;
	}

public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player & _Other) = delete;
	Player(Player && _Other) noexcept = delete;
	Player& operator=(const Player & _Other) = delete;
	Player& operator=(Player && _Other) noexcept = delete;

	// GameEngineRenderer* MainRenderer = nullptr;
	GameEngineRenderer* LowerRenderer = nullptr;
	GameEngineRenderer* UpperRenderer = nullptr;

	void CameraFocus();

protected:
	PlayerState State = PlayerState::Max;
	void ChangeState(PlayerState _State);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void RunStart();
	void RunUpdate(float _Delta);

	void IdleJumpStart();
	void IdleJumpUpdate(float _Delta);

	void MoveJumpStart();
	void MoveJumpUpdate(float _Delta);

	PlayerDir Dir = PlayerDir::Right;
	void DirCheck();

	std::string CurState = "";
	void ChangeAnimationState(const std::string& _State);

private:
	void LevelStart() override;

	void Start() override;
	void Update(float _Delta) override;
	// void Render() override;
	void Release() override;
};

