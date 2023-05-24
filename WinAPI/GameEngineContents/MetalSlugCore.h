#pragma once
#include <GameEngineCore/GameEngineCore.h>

// Ό³Έν : 
class MetalSlugCore : public CoreProcess
{
public:
	// constrcuter destructer
	MetalSlugCore();
	~MetalSlugCore();

	// delete Function
	MetalSlugCore(const MetalSlugCore & _Other) = delete;
	MetalSlugCore(MetalSlugCore && _Other) noexcept = delete;
	MetalSlugCore& operator=(const MetalSlugCore & _Other) = delete;
	MetalSlugCore& operator=(MetalSlugCore && _Other) noexcept = delete;

protected:

private:
	void Start() override;

	void Update(float _Delta) override;

	//void Render() override;

	void Release() override;
};

