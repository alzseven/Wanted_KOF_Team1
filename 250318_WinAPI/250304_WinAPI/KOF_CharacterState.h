#pragma once

enum class State{
	Idle,
	MovingFoward,
	MovingBack,
	StrongPunch,
	StrongKick

};

enum class EAttackHeightType
{
	NONE = 0,
	UPPER,
	LOWER
};

enum class EFiniteStateMachineState
{
	IDLE					= 0,
	MOVE					= 1,
	// MOVE_FORWARD			= 1,
	// MOVE_BACKWARD		= 2
	ATTACK					= 3,
	// ATTACK_WEAK_PUNCH	= 3
	// ATTACK_WEAK_KICK		= 4
	// ATTACK_STRONG_PUNCH	= 5
	// ATTACK_STRONG_KICK	= 6
	GUARD					= 7,
	COUNT_MAX			//  = 8
};

enum class EMoveType
{
	MOVING_FORWARD,
	MOVING_BACKWARD,
	COUNT_MAX
};

enum class EAttackType
{
	WEAK_PUNCH,
	WEAK_KICK,
	STRONG_PUNCH,
	STRONG_KICK,
	COUNT_MAX
};