#include "MetalSlugCore.h"
#include "TitleLevel.h"
#include "CharacterSelectLevel.h"
#include "Stage1.h"
#include <GameEnginePlatform/GameEngineWindow.h>

MetalSlugCore::MetalSlugCore()
{
}

MetalSlugCore::~MetalSlugCore()
{
}

void MetalSlugCore::Start()
{
	// pos, scale
	// pos : 0, 0 의 위치 (윈도우 왼쪽 위의 위치)
	// scale : 해상도
	// 320, 224
	// 640. 448
	// 960, 672
	// GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 1280, 720 });
	GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 960, 672 });

	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	//GameEngineCore::CreateLevel<CharacterSelectLevel>("CharacterSelectLevel");
	GameEngineCore::CreateLevel<Stage1>("Stage1");

	GameEngineCore::ChangeLevel("TitleLevel");
	// GameEngineCore::ChangeLevel("Stage1");
}

void MetalSlugCore::Update(float _Delta)
{

}

// void MetalSlugCore::Render(){}

void MetalSlugCore::Release()
{

}