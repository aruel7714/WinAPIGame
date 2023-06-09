#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>

// ���� : 
class BackGround : public GameEngineActor
{
	friend class Player;
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
	void Init(const std::string& _FileName, const std::string& _DebugFileName);
	void SecondInit(const std::string& _SecondFileName);
	void ThirdInit(const std::string& _ThirdFileName);
	void CloudInit(const std::string& _CloudFileName);
	void ObjectInit(const std::string& _ObjectFileName);
	// void Init(const std::string& _FileName, const std::string& _SecondFileName);

	// void InitDebug(const std::string& _DebugFileName);

	void SwitchRender();

	class GameEngineWindowTexture* MapTexture = nullptr;

	GameEngineRenderer* GetDebugRenderer()
	{
		return DebugRenderer;
	}

protected:

private:
	bool SwitchRenderValue = true;
	std::string FileName;
	class GameEngineRenderer* FirstRenderer;
	class GameEngineRenderer* SecondRenderer;
	class GameEngineRenderer* ThirdRenderer;
	class GameEngineRenderer* CloudRenderer;
	class GameEngineRenderer* ObjectRenderer;
	class GameEngineRenderer* DebugRenderer;

	GameEngineCollision* FirstCollision;

	

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
};

