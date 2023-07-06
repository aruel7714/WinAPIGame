#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEnginePlatform/GameEngineSound.h>

// ���� : 
class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel & _Other) = delete;
	TitleLevel(TitleLevel && _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel & _Other) = delete;
	TitleLevel& operator=(TitleLevel && _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _DeltaTime) override;
private:
	class TitleBackGround* BackGroundPtr = nullptr;

	GameEngineSoundPlayer BGMPlayer;
};

