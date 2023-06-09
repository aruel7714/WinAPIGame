#include "MetalSlugCore.h"
#include "TitleLevel.h"
#include "CharacterSelectLevel.h"
#include "Stage1.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GlobalValue.h"
#include <GameEnginePlatform/GameEngineSound.h>

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
	// 320 - 8 - 8, 224
	// 304, 224
	// 640. 448
	// 608
	// 960, 672
	// 912
	// 1216, 896
	// GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 1280, 720 });
	//GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 912, 672 });
	GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 1216, 896 });

	GlobalValue::WinScale = GameEngineWindow::MainWindow.GetScale();

	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	//GameEngineCore::CreateLevel<CharacterSelectLevel>("CharacterSelectLevel");
	GameEngineCore::CreateLevel<Stage1>("Stage1");

	GameEngineCore::ChangeLevel("TitleLevel");
	//GameEngineCore::ChangeLevel("Stage1");


}

void MetalSlugCore::Update(float _Delta)
{

}

// void MetalSlugCore::Render(){}

void MetalSlugCore::Release()
{

}