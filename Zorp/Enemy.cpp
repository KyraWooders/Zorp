#include "pch.h"
#include "Enemy.h"


void Enemy::onAttacked(int attackPoints)
{
	int damage = attackPoints - m_defendPoints;
	m_healthPoints -= damage;
	if (m_healthPoints < 0)
		m_healthPoints = 0;
}
