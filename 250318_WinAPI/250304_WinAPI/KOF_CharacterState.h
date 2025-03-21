#pragma once



enum class EAttackHeightType
{
	NONE = 0,
	UPPER,
	LOWER
};

enum class EFiniteStateMachineState
{
	IDLE,
	MOVE,
	ATTACK,
	GUARD,
	HITSTUN,
	COUNT_MAX
};

enum class EMoveType
{
	MOVING_FORWARD,
	MOVING_BACKWARD,
	COUNT_MAX
};

/*
 	WEAK_PUNCH,
	WEAK_KICK,
	STRONG_PUNCH,
	STRONG_KICK,
	COUNT_MAX
 */
enum class EAttackType
{
	WEAK_PUNCH,
	WEAK_KICK,
	STRONG_PUNCH,
	STRONG_KICK,
	COUNT_MAX
};