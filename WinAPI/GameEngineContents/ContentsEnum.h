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
	PlayerMeleeCollision,
	PlayerCollision,
	BulletCollision,
	EnemySwordCollision,
	EnemyMeleeCollision,
	EnemyCollision
};