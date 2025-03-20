#include "KOF_Character.h"

void KOF_Character::Init()
{
	health = 100;
	maxHealth = 100;
}

KOF_Character::KOF_Character()
{
}

KOF_Character::~KOF_Character()
{
}

void KOF_Character::SetHealth(int newHealth)
{
	health = newHealth;
	if (health <= 0)
	{
		health = 0;
	}
}
