#include "PlayActor.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "GlobalValue.h"


PlayActor::PlayActor()
{
}

PlayActor::~PlayActor()
{
}

void PlayActor::CameraFocus()
{
	if (false == IsCameraFocus)
	{
		return;
	}

	float4 WindowScale = GameEngineWindow::MainWindow.GetScale();
	GetLevel()->GetMainCamera()->SetPos(GetPos() + float4{ -WindowScale.hX(), -WindowScale.hY() });

	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();

	if (0 >= CameraPos.X)
	{
		CameraPos.X = 0.0f;
	}

	if ((GlobalValue::MapScale.Y - WindowScale.Y) >= CameraPos.Y)
	{
		CameraPos.Y = 0.0f + (GlobalValue::MapScale.Y - WindowScale.Y);
	}

	if (GlobalValue::MapScale.X <= CameraPos.X + WindowScale.X)
	{
		CameraPos.X = GlobalValue::MapScale.X - WindowScale.X;
	}

	if (GlobalValue::MapScale.Y <= CameraPos.Y + WindowScale.Y)
	{
		CameraPos.Y = GlobalValue::MapScale.Y - WindowScale.Y;
	}

	GetLevel()->GetMainCamera()->SetPos(CameraPos);
}

void PlayActor::SetGroundTexture(const std::string& _GroundTextureName)
{
	GroundTexture = ResourcesManager::GetInst().FindTexture(_GroundTextureName);

	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("존재하지 않는 텍스처로 픽셀충돌을 하려고 했습니다.");
	}
}

int PlayActor::GetGroundColor(unsigned int _DefaultColor, float4 _Pos)
{
	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("땅 체크용 텍스처가 존재하지 않습니다.");
	}

	return GroundTexture->GetColor(_DefaultColor, GetPos() + _Pos);
}

void PlayActor::Gravity(float _Delta)
{
	if (false == IsGravity)
	{
		return;
	}

	GravityVector += float4::DOWN * GravityPower * _Delta;

	AddPos(GravityVector * _Delta);
}

float4 PlayActor::ActorCameraPos()
{
	return GetPos() - GetLevel()->GetMainCamera()->GetPos();
}

void PlayActor::SetFocusOn()
{
	IsCameraFocus = true;
}

void PlayActor::SetFocusOff()
{
	IsCameraFocus = false;
}