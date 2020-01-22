#include "pch.h"
#include "Character.h"
#include "Powerup.h"
#include <algorithm>


Character::Character() : 
	GameObject{ { 0, 0 } }, m_healthPoints{ 0 }, 
	m_attackPoints{ 0 }, m_defensePoints{ 0 }
{
}

Character::Character(Point2D position, int health, int attack, int defense) :
	GameObject{ position }, m_healthPoints{ health },
	m_attackPoints{ attack }, m_defensePoints{ defense }
{
}

Character::~Character()
{
}

void Character::addPowerup(Powerup* powerup)
{
	m_powerups.push_back(powerup);
	std::sort(m_powerups.begin(), m_powerups.end(), Powerup::compare);
}
