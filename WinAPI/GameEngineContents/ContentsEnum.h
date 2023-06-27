#pragma once

enum class RenderOrder
{
	ThirdBackGround,
	SecondBackGround,
	FirstBackGround,
	Object1,
	Object2,
	Enemy,
	Granade,
	PlayerLower,
	PlayerUpper,
	ItemRenderer,
	WeaponSFX,
	PlayUI
};

enum class CollisionOrder
{
	PlayerMeleeCollision,
	PlayerCollision,
	BulletCollision,
	ItemCollision,
	EnemySwordCollision,
	EnemyMeleeCollision,
	EnemyCollision
};