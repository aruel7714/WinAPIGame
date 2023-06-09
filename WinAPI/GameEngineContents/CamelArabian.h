#pragma once
#include "PlayActor.h"
#include <GameEnginePlatform/GameEngineSound.h>

enum class CamelArabianLowerState
{
	Spawn,
	Idle,
	Move,
	Down,
	DownIdle,
	Up,
	Death,
	End,
	Max
};

enum class CamelArabianUpperState
{
	Enterance,
	Idle,
	Down,
	DownIdle,
	Fire,
	Up,
	Death,
	End,
	Max
};

enum class CamelArabianDir
{
	Left,
	Right
};

// ���� : 
class CamelArabian : public PlayActor
{
public:
	// constrcuter destructer
	CamelArabian();
	~CamelArabian();

	// delete Function
	CamelArabian(const CamelArabian & _Other) = delete;
	CamelArabian(CamelArabian && _Other) noexcept = delete;
	CamelArabian& operator=(const CamelArabian & _Other) = delete;
	CamelArabian& operator=(CamelArabian && _Other) noexcept = delete;

	GameEngineRenderer* LowerCamelArabianRenderer = nullptr;
	GameEngineRenderer* UpperCamelArabianRenderer = nullptr;
	GameEngineRenderer* UpperDownCamelArabianRenderer = nullptr;

	bool CamelDeath = false;

	GameEngineSoundPlayer Sound;

protected:
	CamelArabianLowerState LowerState = CamelArabianLowerState::Max;
	CamelArabianUpperState UpperState = CamelArabianUpperState::Max;
	CamelArabianDir Dir = CamelArabianDir::Left;

	void ChangeLowerState(CamelArabianLowerState _LowerState);
	void StateLowerUpdate(float _Delta);

	void ChangeUpperState(CamelArabianUpperState _UpperState);
	void StateUpperUpdate(float _Delta);

	void ChangeLowerAnimationState(const std::string& _State);
	void ChangeUpperAnimationState(const std::string& _State);
	void ChangeUpperDownAnimationState(const std::string& _State);

	void SpawnLowerStart();
	void SpawnLowerUpdate(float _Delta);

	void IdleLowerStart();
	void IdleLowerUpdate(float _Delta);

	void MoveLowerStart();
	void MoveLowerUpdate(float _Delta);

	void DownLowerStart();
	void DownLowerUpdate(float _Delta);

	void DownIdleLowerStart();
	void DownIdleLowerUpdate(float _Delta);

	void UpLowerStart();
	void UpLowerUpdate(float _Delta);

	void DeathLowerStart();
	void DeathLowerUpdate(float _Delta);

	void EnteranceUpperStart();
	void EnteranceUpperUpdate(float _Delta);

	void IdleUpperStart();
	void IdleUpperUpdate(float _Delta);

	void DownUpperStart();
	void DownUpperUpdate(float _Delta);

	void DownIdleUpperStart();
	void DownIdleUpperUpdate(float _Delta);

	void FireUpperStart();
	void FireUpperUpdate(float _Delta);

	void UpUpperStart();
	void UpUpperUpdate(float _Delta);
	
	void DeathUpperStart();
	void DeathUpperUpdate(float _Delta);

	void DeathCollisionCheck();

	void DeathLowerEnd();
	void DeathUpperEnd();

private:
	GameEngineCollision* CamelArabianCollision = nullptr;


	void Start() override;
	void Update(float _Delta) override;
};

