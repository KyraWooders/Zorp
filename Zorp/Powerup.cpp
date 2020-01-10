#include "pch.h"
#include "Powerup.h"


Powerup::Powerup()
{
}

Powerup::Powerup(const char name[30], float health, float attack, float defence)
{
}

Powerup::~Powerup()
{
}

char * Powerup::getName()
{
	return nullptr;
}

float Powerup::getHealthMultiplier()
{
	return 0.0f;
}

float Powerup::getAttackMultiplier()
{
	return 0.0f;
}

float Powerup::getDefenceMultiplier()
{
	return 0.0f;
}
