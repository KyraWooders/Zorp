#include "pch.h"
#include "Player.h"
#include "GameDefines.h"
#include <iostream>
#include <cstring>
#include <algorithm>
#include "Room.h"
#include "Food.h"
#include "Enemy.h"
#include "Powerup.h"

Player::Player() : Character({ 0,0 }, 100, 20, 20)
{
	m_priority = PRIORITY_PLAYER;
	/*m_mapPosition.x = 0;
	m_mapPosition.y = 0;*/
}

Player::Player(int x, int y) : Character({ x,y }, 100, 20, 20)
{
	/*m_mapPosition.x = x;
	m_mapPosition.y = y;*/
}

Player::~Player()
{
	/*for (std::vector<Powerup*>::iterator it = m_powerups.begin(); it < m_powerups.end(); it++)
	{
		delete *it;
	}
	m_powerups.clear();*/
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

void Player::drawDescription()
{

}

void Player::lookAt()
{
	std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "Hmmm, I look good!" << std::endl;
}

void Player::executeCommand(int command, Room* room)
{
	switch (command)
	{
	case EAST:
		if (m_mapPosition.x < MAZE_WIDTH - 1)
			m_mapPosition.x++;
		return;
	case WEST:
		if (m_mapPosition.x > 0)
			m_mapPosition.x--;
		return;
	case NORTH:
		if (m_mapPosition.y > 0)
			m_mapPosition.y--;
		return;
	case SOUTH:
		if (m_mapPosition.y < MAZE_HEIGHT - 1)
			m_mapPosition.y++;
		return;
	case LOOK:
		room->lookAt();
		break;
	case FIGHT:
		attack(room->getEnemy());
		break;
	case PICKUP:
		pickup(room);
		break;
	default:
		std::cout << INDENT << "You try, but you just can't do it." << std::endl;
		break;
		/*
	case PICKUP:
		return pickup(); */
	}

	std::cout << INDENT << "Press 'Enter' to continue.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
}

void Player::pickup(Room * room)
{
	Powerup* powerup = room->getPowerup();
	Food* food = room->getFood();
	std::cout << EXTRA_OUTPUT_POS << RESET_COLOR;

	if (room->getPowerup() != nullptr)
	{
		std::cout << "You pick up the " << powerup->getName() <<"."<< std::endl;
		addPowerup(powerup);
		room->removeGameObject(powerup);
	}
	else if (room->getFood() != nullptr)
	{
		m_healthPoints += food->getHP();
		std::cout << "You feel refreshed. Your health is now " << m_healthPoints << std::endl;
		room->removeGameObject(food);
	}
	else
	{
		std::cout << "There is nothing here to pick up." << std::endl;
	}
}

void Player::attack(Enemy * enemy)
{
	if (enemy == nullptr)
	{
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is no one here you can fight with." << std::endl;
	}
	else
	{
		enemy->onAttacked(m_attackPoints);

		if (enemy->isAlive() == false)
		{
			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You fight a grue and kill it." << std::endl;
		}
		else
		{
			int damage = enemy->getAP() - m_defensePoints;
			if (damage < 1) damage = 1;
			m_healthPoints -= damage;

			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You fight a grue and take " << damage << " points damage. Your health is now at " << m_healthPoints << "." << std::endl;
			std::cout << INDENT << "The grue has " << enemy->getHP() << " health remaining." << std::endl;
		}
	}
}