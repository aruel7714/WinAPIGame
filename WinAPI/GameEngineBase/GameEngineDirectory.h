#pragma once
#include "GameEngineFile.h"

// 설명 : 스프라이트가 여러개일경우 사용
class GameEngineDirectory : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineDirectory();
	GameEngineDirectory(const std::string& _Path);
	~GameEngineDirectory();

	// delete Function
	GameEngineDirectory(const GameEngineDirectory & _Other) = delete;
	GameEngineDirectory(GameEngineDirectory && _Other) noexcept = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory & _Other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory && _Other) noexcept = delete;

	std::vector<class GameEngineFile> GetAllFile(std::vector<std::string> _Ext);

protected:

private:

};

