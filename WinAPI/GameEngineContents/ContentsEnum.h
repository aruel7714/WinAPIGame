#pragma once

enum class RenderOrder
{
	SecondBackGround,
	FirstBackGround,
	Enemy,
	Granade,
	PlayerLower,
	PlayerUpper,
	WeaponSFX,
	PlayUI
};

enum class CollisionOrder
{
	PlayerCollision,
	PlayerMeleeCollision,
	BulletCollision,
	EnemySwordCollision,
	EnemyMeleeCollision,
	EnemyCollision
};