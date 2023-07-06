#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class TitleBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleBackGround();
	~TitleBackGround();

	// delete Function
	TitleBackGround(const TitleBackGround & _Other) = delete;
	TitleBackGround(TitleBackGround && _Other) noexcept = delete;
	TitleBackGround& operator=(const TitleBackGround & _Other) = delete;
	TitleBackGround& operator=(TitleBackGround && _Other) noexcept = delete;

	void Init(const std::string& _FileName);

protected:

private:
	class GameEngineRenderer* FirstRenderer;

	void Start() override;
	
};

