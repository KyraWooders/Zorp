#include "pch.h"
#include "Room.h"
#include <iostream>
#include "GameDefines.h"
#include "Player.h"
#include "Powerup.h"


static const char itemNames[15][30] =
	{		
	    "yes", "invisibility", "why", "GG",
		"stop", "impatience", "indecision", "please",
		"high", "no", "integration", "invocation",
		"inferno", "AAAAA", "inoculation"
	};

Room::Room() : m_type{ EMPTY }, m_mapPosition{ 0, 0 }, m_powerup{nullptr}
{
	/*m_type = EMPTY;
	m_mapPosition.x = 0;
	m_mapPosition.y = 0;*/
}

Room::~Room()
{
	if (m_powerup != nullptr)
		delete m_powerup;
}

void Room::setPosition(Point2D position)
{
	m_mapPosition = position;
}

void Room::setType(int type)
{
	m_type = type;

	if (!(m_type == TREASURE_HP || m_type == TREASURE_AT || m_type == TREASURE_DF))
		return;
	if (m_powerup != nullptr)
		return;

	int item = rand() % 15; 
	char name[30] = ""; 
	
	float hp = 1; 
	float at = 1; 
	float df = 1;

	switch (type)
		{
		case TREASURE_HP:
			strcpy_s(name, "potion of ");
			hp = 1.1f;
			break;
		case TREASURE_AT:
			strcpy_s(name, "sword of ");
			at = 1.1f;
			break;
		case TREASURE_DF:
			strcpy_s(name, "shield of ");
			df = 1.1f;
			break;
		}

	strncat_s(name, itemNames[item], 30);
	if (m_powerup != nullptr)
		delete m_powerup;
	m_powerup = new Powerup(name, hp, at, df);
}

int Room::getType()
{
	return m_type;
}

void Room::draw()
{
	int outX = INDENT_X + (6 * m_mapPosition.x) + 1;
	int outY = MAP_Y + m_mapPosition.y;

	std::cout << CSI << outY << ";" << outX << "H";

	switch (m_type)
	{
	case EMPTY:
		std::cout << "[ " << GREEN << "\xb0" << RESET_COLOR << " ] ";
		break;
	case ENEMY:
		std::cout << "[ " << RED << "\x94" << RESET_COLOR << " ] ";
		break;
	case TREASURE_HP:
	case TREASURE_AT:
	case TREASURE_DF:
	/*case TREASURE:*/
		std::cout << "[ " << YELLOW << "$" << RESET_COLOR << " ] ";
		break;
	case FOOD:
		std::cout << "[ " << WHITE << "\xcf" << RESET_COLOR << " ] ";
		break;
	case ENTRANCE:
		std::cout << "[ " << WHITE << "\x9d" << RESET_COLOR << " ] ";
		break;
	case EXIT:
		std::cout << "[ " << WHITE << "\xFE" << RESET_COLOR << " ] ";
		break;
	}
}

void Room::drawDescription()
{
	std::cout << RESET_COLOR;
	std::cout << CSI << ROOM_DESC_Y << ";" << 0 << "H";
	std::cout << CSI << "4M" << CSI << "4L" << std::endl;

	switch (m_type)
	{
	case EMPTY:
		std::cout << INDENT << "You are in an empty meadow. There is nothing of note here." << std::endl;
		break;
	case ENEMY:
		std::cout << INDENT << RED << "Beware." << RESET_COLOR << "An enemy is approaching." << std::endl;
		break;
	case TREASURE_HP:
	case TREASURE_AT:
	case TREASURE_DF:
	/*case TREASURE:*/
		std::cout << INDENT << "There apppers to be some treasure here. perhaps you should investigate futher." << std::endl;
		break;
	case FOOD:
		std::cout << INDENT << "At last! You collect some food to sustain you on your journey." << std::endl;
		break;
	case ENTRANCE:
		std::cout << INDENT << "The entrance you used to enter this maze is blocked. There is no going back." << std::endl;
		break;
	case EXIT:
		std::cout << INDENT << "Despite all odds, you made it to the exit. Congratulations." << std::endl;
		break;
	}
}

bool Room::executeCommand(int command, Player* player)
{
	std::cout << EXTRA_OUTPUT_POS;
	switch (command)
	{
	case LOOK:
		if (m_type == TREASURE_HP || m_type == TREASURE_AT || m_type == TREASURE_DF)
		{
			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is some treasure here. It looks small enough to pick up." << std::endl;
		}
		else
		{
			std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning" << std::endl;
		}
		std::cout << INDENT << "Press 'Enter' to continue.";
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin.get();
		return true;
	case FIGHT:
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You could try to fight, but you don't have a weapon" << std::endl;
		std::cout << INDENT << "Press 'Enter' to continue.";
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin.get();
		return true;
	case PICKUP:
		return pickup(player);
	default:
		std::cout << INDENT << "You try, but you just can't do it." << std::endl;
		std::cout << INDENT << "Press 'Enter' to continue.";
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cin.get();
		break;
	}
	return false;
}

bool Room::pickup(Player* player)
{
	if (m_powerup == nullptr)
	{
		std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is nothing here to pick up." << std::endl;
		return true;
	}

	std::cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You pick up the " << m_powerup->getName() << std::endl;

	player->addPowerup(m_powerup);

	m_powerup = nullptr;

	m_type = EMPTY;

	std::cout << INDENT << "Press 'Enter' to continue.";
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
	return true;
}



//void Room::waitForInput()
//{
//	std::cin.clear();
//	std::cin.ignore(std::cin.rdbuf()->in_avail());
//	std::cin.get();
//}
