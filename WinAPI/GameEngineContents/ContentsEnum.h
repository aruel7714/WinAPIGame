#pragma once

enum class RenderOrder
{
	CloudBackGround,
	ThirdBackGround,
	SecondBackGround,
	FirstBackGround,
	Object1,
	MiddleBoss,
	MiddleBossTexture,
	CamelUpper,
	CamelLower,
	CamelUpperDown,
	EnemyTruck,
	Enemy,
	EnemyAttack,
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
	EnemyBulletCollision,
	EnemyCollision,
	NPCCollision,
	BossCollision,
	BossAttackCollision
};