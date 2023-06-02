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

class PlayerUpperRender;
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
	void StateUpdate(float _Delta);

	void IdleStart();
	void IdleUpdate(float _Delta);

	void MoveStart();
	void MoveUpdate(float _Delta);

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

	


// gravity
public:
	void Gravity(float _Delta);

	void GravityReset()
	{
		GravityVector = float4::ZERO;
	}

	// void SetGroundTexture(const std::string& _GroundTextureName);

	// int GetGroundColor(unsigned int _DefaultColor, float4 _Pos = float4::ZERO);

	void SetGravityVector(float4 _GravityVector)
	{
		GravityVector = _GravityVector;
	}

private:
	class GameEngineWindowTexture* GroundTexture = nullptr;

	bool IsGravity = true;

	float GravityPower = 1.0f;
	float4 GravityVector = float4::ZERO;
};

