#include "GameEngineCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include "GameEngineLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>

std::string GameEngineCore::WindowTitle = "";
std::map<std::string, class GameEngineLevel*> GameEngineCore::AllLevel;
CoreProcess* GameEngineCore::Process = nullptr;
GameEngineLevel* GameEngineCore::CurLevel = nullptr;
GameEngineLevel* GameEngineCore::NextLevel = nullptr;

GameEngineCore::GameEngineCore()
{
}

GameEngineCore::~GameEngineCore()
{
}

void GameEngineCore::CoreStart(HINSTANCE _Inst)
{
	GameEngineWindow::MainWindow.Open(WindowTitle, _Inst);

	GameEngineInput::InputInit();

	Process->Start();
}

void GameEngineCore::CoreUpdate()
{
	if (nullptr != NextLevel)
	{
		if (nullptr != CurLevel)
		{
			CurLevel->LevelEnd(NextLevel);
		}
	}
}

void GameEngineCore::CoreEnd()
{

}
