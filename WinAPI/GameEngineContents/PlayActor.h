#pragma once
#include <GameEngineCore/GameEngineActor.h>


// Ό³Έν : 
class PlayActor : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayActor();
	~PlayActor();

	// delete Function
	PlayActor(const PlayActor & _Other) = delete;
	PlayActor(PlayActor && _Other) noexcept = delete;
	PlayActor& operator=(const PlayActor & _Other) = delete;
	PlayActor& operator=(PlayActor && _Other) noexcept = delete;

	void SetGroundTexture(const std::string& _GroundTextureName);

	int GetGroundColor(unsigned int _DefaultColor, float4 _Pos = float4::ZERO);

	void CameraFocus();

	float4 ActorCameraPos();

	void SetFocusOn();
	void SetFocusOff();

	float4 GetGravityVector()
	{
		return GravityVector;
	}

protected:

private:
	class GameEngineWindowTexture* GroundTexture = nullptr;

// gravity
public:
	void Gravity(float _Delta);
	

	void GravityReset()
	{
		GravityVector = float4::ZERO;
	}

	void SetGravityVector(float4 _GravityVector)
	{
		GravityVector = _GravityVector;
	}

private:
	bool IsGravity = true;

	float GravityPower = 2000.0f;
	float4 GravityVector = float4::ZERO;

	bool IsCameraFocus = true;
};


