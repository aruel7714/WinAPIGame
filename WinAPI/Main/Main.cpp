#include <iostream>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineContents/MetalSlugCore.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineCore::EngineStart<MetalSlugCore>("MetalSlug", hInstance);
	return 0;
}