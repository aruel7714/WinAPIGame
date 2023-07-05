#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν : 
class Stage1 : public GameEngineLevel
{
public:
	// constrcuter destructer
	Stage1();
	~Stage1();

	// delete Function
	Stage1(const Stage1 & _Other) = delete;
	Stage1(Stage1 && _Other) noexcept = delete;
	Stage1& operator=(const Stage1 & _Other) = delete;
	Stage1& operator=(Stage1 && _Other) noexcept = delete;

	//int GetColor(unsigned int _DefaultColor, float4 _Pos);

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	class BackGround* BackGroundPtr;
	class Player* LevelPlayer = nullptr;

	//Enemy
	class Arabian* NewArabian = nullptr;
	
	class Berserker* NewBerserker = nullptr;
	
	class Truck* NewTruck = nullptr;
	
	
	
	
	
	
	
	



	class CamelArabian* NewCamelArabian1 = nullptr;
	class CamelArabian* NewCamelArabian2 = nullptr;
	//class Arabian* NewArabian2 = nullptr;
	
	class MiddleBoss* MiddleBossPtr = nullptr;

	class FinalBoss* FinalBossPtr = nullptr;

	class SlaveNPC* NewSlave = nullptr;

	//Etc
	class SlaveNPC* NewSlave1 = nullptr;
	
	

	class HeavyMachineGun* NewHeavyMachineGun = nullptr;
	

	class DebugCollision* FirstCollision = nullptr;
	//class DebugCollision* SecondCollision = nullptr;

	//class Arabian* EnemyArabian = nullptr;
	
	bool IsCamelArabian = false;
};

