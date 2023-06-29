#pragma once

enum class RenderOrder
{
	ThirdBackGround,
	SecondBackGround,
	FirstBackGround,
	Object1,
	Object2,
	Enemy,
	Boss,
	BossAttack,
	NPC,
	Granade,
	PlayerLower,
	PlayerUpper,
	ItemRenderer,
	WeaponSFX,
	PlayUI
};

enum class CollisionOrder
{
	DebugCollision,
	PlayerMeleeCollision,
	PlayerCollision,
	BulletCollision,
	ItemCollision,
	EnemySwordCollision,
	EnemyMeleeCollision,
	EnemyCollision,
	FinalBossCollision,
	FinalBossAttackCollision
};