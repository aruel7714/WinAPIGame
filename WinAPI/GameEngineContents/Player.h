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

enum class PlayerLowerState
{
	Idle,
	Move,
	IdleJump,
	MoveJump,
	Sit,
	Max
};

enum class PlayerUpperState
{
	Idle,
	Move,
	IdleJump,
	MoveJump,
	Fire,
	Granade,
	Dia,
	Up,
	UpFire,
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
	//PlayerState State = PlayerState::Max;
	PlayerLowerState LowerState = PlayerLowerState::Max;
	PlayerUpperState UpperState = PlayerUpperState::Max;
	//void ChangeState(PlayerState _State);
	//void StateUpdate(float _Delta);

	void ChangeLowerState(PlayerLowerState _LowerState);
	void StateLowerUpdate(float _Delta);

	void ChangeUpperState(PlayerUpperState _UpperState);
	void StateUpperUpdate(float _Delta);

	//void IdleStart();
	//void IdleUpdate(float _Delta);

	void IdleLowerStart();
	void IdleLowerUpdate(float _Delta);

	void IdleUpperStart();
	void IdleUpperUpdate(float _Delta);

	

	//void MoveStart();
	//void MoveUpdate(float _Delta);

	//void IdleJumpStart();
	//void IdleJumpUpdate(float _Delta);

	//void MoveJumpStart();
	//void MoveJumpUpdate(float _Delta);

	void MoveLowerStart();
	void MoveLowerUpdate(float _Delta);

	void MoveUpperStart();
	void MoveUpperUpdate(float _Delta);

	void IdleJumpLowerStart();
	void IdleJumpLowerUpdate(float _Delta);

	void IdleJumpUpperStart();
	void IdleJumpUpperUpdate(float _Delta);

	void MoveJumpLowerStart();
	void MoveJumpLowerUpdate(float _Delta);

	void MoveJumpUpperStart();
	void MoveJumpUpperUpdate(float _Delta);

	void FireStart();
	void FireUpdate(float _Delta);

	void GranadeStart();
	void GranadeUpdate(float _Delta);

	//UpperRenderer->CreateAnimation("Right_Pistol_Upper_LookUp", "Right_Pistol_Upper.bmp", 46, 47, 0.5f, false);
	//UpperRenderer->CreateAnimation("RightUp_Pistol_Upper_Idle", "Right_Pistol_Upper.bmp", 48, 51, 0.5f, true);
	//UpperRenderer->CreateAnimation("RightUp_Pistol_Upper_Fire", "Right_Pistol_Upper.bmp", 52, 61, 0.5f, false);

	void LookUpStart();
	void LookUpUpdate(float _Delta);


	PlayerDir Dir = PlayerDir::Right;
	void DirCheck();

	std::string CurState = "";
	std::string PrevState = "";
	void ChangeAnimationState(const std::string& _State);

	void ChangeLowerAnimationState(const std::string& _State, bool _IsForce = false);
	void ChangeUpperAnimationState(const std::string& _State, bool _IsForce = false);

	std::string WeaponName;

	bool IsWeapon = false;
	bool IsKnife = false;

private:
	void LevelStart() override;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void Release() override;

	float4 Pos = float4::ZERO;
	// Debug
	


};

