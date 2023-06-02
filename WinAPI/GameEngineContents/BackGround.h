#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>

// ���� : 
class BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	BackGround();
	~BackGround();

	// delete Function
	BackGround(const BackGround & _Other) = delete;
	BackGround(BackGround && _Other) noexcept = delete;
	BackGround& operator=(const BackGround & _Other) = delete;
	BackGround& operator=(BackGround && _Other) noexcept = delete;

	void Init(const std::string& _FileName);
	// void Init(const std::string& _FileName, const std::string& _DebugFileName);
	void Init(const std::string& _FileName, const std::string& _SecondFileName);

	void SwitchRender();

protected:

private:
	bool SwitchRenderValue = true;
	std::string FileName;
	class GameEngineRenderer* FirstRenderer;
	class GameEngineRenderer* SecondRenderer;
	class GameEngineRenderer* DebugRenderer;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
};

