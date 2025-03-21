#include "KOF_Character.h"
#include "Image.h"

void KOF_Character::Init()
{
	health = 100;
	maxHealth = 100;
}

void KOF_Character::Release()
{
	
}

void KOF_Character::Update()
{
}

void KOF_Character::Render(HDC hdc)
{
	
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
