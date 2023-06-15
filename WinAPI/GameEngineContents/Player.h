#pragma once
#include "PlayActor.h"

enum class PlayerState
{
	Idle,
	Move,
	IdleJump,
	MoveJump,
	Fire,
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

class PlayerUpperRender;
// 설명 : 
class Player : public PlayActor
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

	//void CameraFocus();

	

protected:
	// PlayerState관련
	PlayerState State = PlayerState::Max;
	void ChangeState(PlayerState _State);
	void StateUpdate(float _Delta);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

	void IdleJumpStart();
	void IdleJumpUpdate(float _Delta);

	void MoveJumpStart();
	void MoveJumpUpdate(float _Delta);

	
	//void FireUpdate(float _Delta);

	PlayerDir Dir = PlayerDir::Right;
	void DirCheck();

	std::string CurState = "";
	std::string PrevState = "";
	std::string AnimationName = "";
	void ChangeAnimationState(const std::string& _State);

	void ChangeLowerAnimationState(const std::string& _State);
	void ChangeUpperAnimationState(const std::string& _State);

private:
	void LevelStart() override;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void Release() override;

	// Debug
	


};

