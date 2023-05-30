#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� : 
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

	void CameraFocus();

protected:
	//void LevelStart(GameEngineLevel* _PrevLevel) override;
	//void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	class BackGround* BackGroundPtr;
	class Player* LevelPlayer = nullptr;
	
};

