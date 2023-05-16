#pragma once
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineString.h>
#include <Windows.h>
#include <string>
#include <map>

class CoreProcess /*: public GameEngineObject*/
{

};

// Ό³Έν : 
class GameEngineCore
{
public:
	

	// delete Function
	GameEngineCore(const GameEngineCore & _Other) = delete;
	GameEngineCore(GameEngineCore && _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore & _Other) = delete;
	GameEngineCore& operator=(GameEngineCore && _Other) noexcept = delete;

protected:

private:
	static std::string WindowTitle;
	static CoreProcess* Process;

	static void LevelInit(GameEngineLevel* _Level);

	static void CoreStart(HINSTANCE _Inst);
	static void CoreUpdate();
	static void CoreEnd();

	static void EngineStart(const std::string& _Title, HINSTANCE _Inst, CoreProcess* _Ptr);

	static GameEngineLevel* CurLevel;
	static GameEngineLevel* NextLevel;

	static std::map<std::string, class GameEngineLevel*> AllLevel;

	// constrcuter destructer
	GameEngineCore();
	~GameEngineCore();
};

