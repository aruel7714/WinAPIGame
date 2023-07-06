#pragma once
#include "PlayActor.h"
#include <GameEnginePlatform/GameEngineSound.h>

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
	MoveStop,
	SitDown,
	SitUp,
	SitIdle,
	SitMove,
	SitFire,
	SitFireIdle,
	SitGranade,
	SitGranadeIdle,
	RangeDeathJump,
	RangeDeathGround,
	MeleeDeath,
	SwordDeath,
	Revive,
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
	LookUp,
	UpIdle,
	LookDown,
	UpFire,
	JumpLookDown,
	DownIdle,
	JumpLookUp,
	DownFire,
	MeleeAtt,
	LookUpFire,
	LookDownFire,
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

enum class PlayerBulletDir
{
	Left,
	Right,
	LeftUp,
	RightUp,
	LeftDown,
	RightDown,
	Max
};

enum class PlayerRifleBulletDir
{
	Left,
	LeftUp30,
	LeftUp45,
	LeftUp60,
	LeftUp90,
	LeftDown30,
	LeftDown45,
	LeftDown60,
	LeftDown90,
	Right,
	RightUp30,
	RightUp45,
	RightUp60,
	RightUp90,
	RightDown30,
	RightDown45,
	RightDown60,
	RightDown90
};

// 설명 : 
class Player : public PlayActor
{
	friend class Arabian;
	friend class ArabianSword;
	friend class Berserker;
	friend class FinalBoss;
	friend class HeavyMachineGun;
	friend class Bullet;
	friend class Granade;
	friend class EnemyBullet;
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

	GameEngineSoundPlayer Sound;

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

	void LookUpStart();
	void LookUpUpdate(float _Delta);

	void UpIdleStart();
	void UpIdleUpdate(float _Delta);

	void LookDownStart();
	void LookDownUpdate(float _Delta);

	void JumpLookDownStart();
	void JumpLookDownUpdate(float _Delta);

	void DownIdleStart();
	void DownIdleUpdate(float _Delta);

	void JumpLookUpStart();
	void JumpLookUpUpdate(float _Delta);

	void MoveStopStart();
	void MoveStopUpdate(float _Delta);

	void SitDownStart();
	void SitDownUpdate(float _Delta);

	void SitUpStart();
	void SitUpUpdate(float _Delta);

	void SitIdleStart();
	void SitIdleUpdate(float _Delta);

	void SitMoveStart();
	void SitMoveUpdate(float _Delta);

	void SitFireStart();
	void SitFireUpdate(float _Delta);

	void SitFireIdleStart();
	void SitFireIdleUpdate(float _Delta);

	void SitGranadeStart();
	void SitGranadeUpdate(float _Delta);

	void SitGranadeIdleStart();
	void SitGranadeIdleUpdate(float _Delta);

	void MeleeAttStart();
	void MeleeAttUpdate(float _Delta);

	void RangeDeathJumpStart();
	void RangeDeathJumpUpdate(float _Delta);

	void RangeDeathGroundStart();
	void RangeDeathGroundUpdate(float _Delta);

	void MeleeDeathStart();
	void MeleeDeathUpdate(float _Delta);

	void SwordDeathStart();
	void SwordDeathUpdate(float _Delta);

	void LookUpFireStart();
	void LookUpFireUpdate(float _Delta);

	void LookDownFireStart();
	void LookDownFireUpdate(float _Delta);

	static PlayerDir Dir;
	static PlayerBulletDir BulletDir;
	static PlayerRifleBulletDir RifleDir;

	//PlayerRifleBulletDir RifleDir = PlayerRifleBulletDir::Right;
	void DirCheck();
	void BulletDirCheck();
	void RifleDirCheck();

	std::string CurState = "";
	std::string PrevState = "";
	void ChangeAnimationState(const std::string& _State);

	void ChangeLowerAnimationState(const std::string& _State, bool _IsWeapon = false, bool _IsForce = false);
	void ChangeUpperAnimationState(const std::string& _State, bool _IsForce = false);

	static std::string WeaponName;

	bool IsWeapon = false;
	bool IsKnife = false;

	// Collision
	GameEngineCollision* BodyCollision = nullptr;
	GameEngineCollision* MeleeAttCollision = nullptr;

private:
	void LevelStart() override;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void Release() override;

	float4 Pos = float4::ZERO;
	// Debug
	
	int MachineGunCount = 4;
	void BulletFire();
	float4 RifleBulletDir = float4::ZERO;
	float BulletPlusDir = 0.25f;
	int AngleCount = 0;

	int MeleeAttCount = 1;
};

