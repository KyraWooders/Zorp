#include "pch.h"
#include "Player.h"
#include "GameDefines.h"
#include <iostream>
#include <cstring>
#include <algorithm>
#include "Room.h"
#include "Powerup.h"

Player::Player() : m_mapPosition{ 0, 0 }, m_healthPoints{100}, m_attackPoints{20}, m_defendPoints{20}
{
	/*m_mapPosition.x = 0;
	m_mapPosition.y = 0;*/
}

Player::Player(int x, int y) : m_mapPosition{ x, y }, m_healthPoints{ 100 }, m_attackPoints{ 20 }, m_defendPoints{ 20 }
{
	/*m_mapPosition.x = x;
	m_mapPosition.y = y;*/
}

Player::~Player()
{
	for (std::vector<Powerup*>::iterator it = m_powerups.begin(); it < m_powerups.end(); it++)
	{
		delete *it;
	}
	m_powerups.clear();
}

void Player::addPowerup(Powerup * powerup)
{
	m_powerups.push_back(powerup); 
	
	std::sort(m_powerups.begin(), m_powerups.end(), Powerup::compare);
}

void Player::setPosition(Point2D position)
{
	m_mapPosition = position;
}

Point2D Player::getPosition()
{
	return m_mapPosition;
}

void Player::draw()
{
	Point2D outPos =
	{
		INDENT_X + (6 * m_mapPosition.x) + 3,
		MAP_Y + m_mapPosition.y
	};

	std::cout << CSI << outPos.y << ";" << outPos.x << "H";
	std::cout << MAGENTA << "\x81" << RESET_COLOR;

	std::cout << INVENTORY_OUTPUT_POS;
	for (std::vector<Powerup*>::iterator it = m_powerups.begin(); it < m_powerups.end(); it++)
	{
		std::cout << (*it)->getName() << "\t";
	}
}

bool Player::executeCommand(int command)
{
	switch (command)
	{
	case EAST:
		if (m_mapPosition.x < MAZE_WIDTH - 1)
			m_mapPosition.x++;
		return true;
	case WEST:
		if (m_mapPosition.x > 0)
			m_mapPosition.x--;
		return true;
	case NORTH:
		if (m_mapPosition.y > 0)
			m_mapPosition.y--;
		return true;
	case SOUTH:
		if (m_mapPosition.y < MAZE_HEIGHT - 1)
			m_mapPosition.y++;
		return true;/*
	case PICKUP:
		return pickup(); */
	}
	return false;
}