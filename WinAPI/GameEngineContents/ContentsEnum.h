#pragma once

enum class RenderOrder
{
	CloudBackGround,
	ThirdBackGround,
	SecondBackGround,
	FirstBackGround,
	Object1,
	CamelUpper,
	CamelLower,
	CamelUpperDown,
	Enemy,
	Boss,
	BossAttack,
	NPC,
	Granade,
	PlayerLower,
	PlayerUpper,
	ItemRenderer,
	WeaponSFX,
	Object2,
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