#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class EnemyBullet : public GameEngineActor
{
public:
	// constrcuter destructer
	EnemyBullet();
	~EnemyBullet();

	// delete Function
	EnemyBullet(const EnemyBullet & _Other) = delete;
	EnemyBullet(EnemyBullet && _Other) noexcept = delete;
	EnemyBullet& operator=(const EnemyBullet & _Other) = delete;
	EnemyBullet& operator=(EnemyBullet && _Other) noexcept = delete;

	GameEngineRenderer* Renderer;

	void SetDir(const float4& _Dir)
	{
		Dir = _Dir;
	}

protected:


private:
	float4 Dir;
	float Speed = 100.0f;

	void Start() override;
	void Update(float _Delta) override;

	GameEngineCollision* BulletCollision = nullptr;
};

