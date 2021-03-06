#include "pch.h"
#include "Powerup.h"
#include <cstring>
#include "GameDefines.h"
#include <iostream>


Powerup::Powerup() : m_healthMultiplier{ 1 }, m_attackMultiplier{ 1 }, m_defenceMultiplier{ 1 }
{
	m_priority = PRIORITY_POWERUP;
	m_name[0] = 0;
}

Powerup::Powerup(const char name[30], float health, float attack, float defence) : 
	m_healthMultiplier{health}, 
	m_attackMultiplier{attack}, 
	m_defenceMultiplier{defence}
{
	m_priority = PRIORITY_POWERUP;
	strcpy_s(m_name, name);
}

Powerup::~Powerup()
{
}

char * Powerup::getName()
{
	return m_name;
}


void Powerup::setName(const char * pStr)
{
	strncpy_s(m_name, pStr, 30);
}

bool Powerup::compare(const Powerup* p1, const Powerup* p2)
{
	/*if (strcmp(p1->m_name, p2->m_name) < 0)
	{
		return true;
	}
	else
	{
		return false;
	}*/

	return (strcmp(p1->m_name, p2->m_name) < 0) ? true : false;
}

void Powerup::draw()
{
	std::cout << "[ " << YELLOW << "$" << RESET_COLOR << " ] ";
}

void Powerup::drawDescription()
{
	std::cout << INDENT << "There appears to be some treasure here. Perhaps you should investigate futher." << std::endl;
}

void Powerup::lookAt()
{
	std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is some treasure here. It looks small enough to pick up." << std::endl;
}