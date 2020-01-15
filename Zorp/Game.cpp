#include "pch.h"
#include "Game.h"
#include "Enemy.h"
#include "Food.h"
#include "Powerup.h"
#include <iostream>
#include <random>
#include <time.h>
#include <windows.h>

Game::Game() : m_gameOver{ false }
{
	//m_gameOver = false;
}

Game::~Game()
{
	delete[] m_powerups;
	delete[] m_enemies;
	delete[] m_food;
}

bool Game::startup()
{
	if (enableVirtualTerminal() == false)
	{
		std::cout << "The virtual terminal processing mode could not be activated." << std::endl;
		std::cout << "Press 'Enter' to exit." << std::endl;
		std::cin.get();
		return false;
	}
	srand(time(nullptr));

	initializeMap();
	initializeEnemies();
	initializePowerups();
	initializeFood();

	m_player.setPosition(Point2D{ 0,0 });
	
	drawWelcomeMessage();

	return true;
}

bool Game::isGameOver() 
{
	return m_gameOver;
}

bool Game::enableVirtualTerminal()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))
	{
		return false;
	}

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(hOut, dwMode))
	{
		return false;
	}
	return true;
}

void Game::initializeMap()
{
	//srand(time(nullptr));

	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			m_map[y][x].setPosition(Point2D{ x,y });
		}
	}

	m_map[0][0].setType(ENTRANCE);
	m_map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1].setType(EXIT);
}

void Game::initializeEnemies()
{
	m_enemyCount = 1 + rand() % 4;
	m_enemies = new Enemy[m_enemyCount];

	for (int i = 0; i < m_enemyCount; i++)
	{
		int x = 2 + (rand() % (MAZE_WIDTH - 3));
		int y = 2 + (rand() % (MAZE_HEIGHT - 3));

		m_enemies[i].setPosition(Point2D{ x,y });
		m_map[y][x].setEnemy(&m_enemies[i]);
	}
}

void Game::initializePowerups()
{
	m_powerupCount = 3;
	m_powerups = new Powerup[m_powerupCount];

	for (int i = 0; i < m_powerupCount; i++)
	{
		char name[30] = ""; 
		int x = rand() % (MAZE_WIDTH - 1); 
		int y = rand() % (MAZE_HEIGHT - 1);

		float HP = 1; 
		float AT = 1; 
		float DF = 1;

		switch (i)
		{
		case 0:
			strcpy_s(name, "potion of ");
			m_powerups[i].setHealthMultiplier(1.1f);
			break;
		case 1:
			strcpy_s(name, "sword of ");
			m_powerups[i].setAttackMultiplier(1.1f);
			break;
		case 2:
			strcpy_s(name, "shield of ");
			m_powerups[i].setDefenceMultiplier(1.1f);
			break;
		}

		strncat_s(name, itemNames[ (rand()%15) ], 30);
		m_powerups[i].setName(name);
		m_map[y][x].setPowerup(&m_powerups[i]);
	}
}

void Game::initializeFood()
{
	m_foodCount = 3;
	m_food = new Food[m_foodCount];

	for (int i = 0; i < m_foodCount; i++)
	{
		int x = 2 + (rand() % (MAZE_WIDTH - 1));
		int y = 2 + (rand() % (MAZE_HEIGHT - 1));

		m_map[y][x].setFood(&m_food[i]);
	}
}

void Game::drawWelcomeMessage()
{
	std::cout << TITLE << MAGENTA << "Welcome to ZORP!" << RESET_COLOR << std::endl;
	std::cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << std::endl;
	std::cout << INDENT << "It is definitely not related to any other text-based adventure game." << std::endl << std::endl;
}

void Game::drawMap()
{
	Point2D position = { 0, 0 };

	std::cout << RESET_COLOR;
	for (position.y = 0; position.y < MAZE_HEIGHT; position.y++)
	{
		std::cout << INDENT;
		for (position.x = 0; position.x < MAZE_WIDTH; position.x++)
		{
			m_map[position.y][position.x].draw();
		}
		std::cout << std::endl;
	}
}

void Game::drawValidDirections()
{
	Point2D position = m_player.getPosition();

	std::cout << RESET_COLOR;
	std::cout << CSI << MOVEMENT_DESC_Y + 1 << ";" << 0 << "H";
	std::cout << INDENT << "You can see paths leading to the " <<
		((position.x > 0) ? "west, " : "") <<
		((position.x < MAZE_WIDTH - 1) ? "east, " : "") <<
		((position.y > 0) ? "north, " : "") <<
		((position.y < MAZE_HEIGHT - 1) ? "south, " : "") << std::endl;
}

int Game::getCommand()
{
	char input[50] = "\0";

	std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";

	std::cout << CSI << "5M";
	std::cout << CSI << "5L";

	std::cout << INDENT << "Enter a command:";

	std::cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;

	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	std::cin >> input;
	std::cout << RESET_COLOR;

	bool bMove = false;
	bool bPickup = false;
	while (input)
	{
		if (strcmp(input, "move") == 0)
		{
			bMove = true;
		}
		else if (bMove == true)
		{
			if (strcmp(input, "north") == 0)
				return NORTH;
			if (strcmp(input, "south") == 0)
				return SOUTH;
			if (strcmp(input, "east") == 0)
				return EAST;
			if (strcmp(input, "west") == 0)
				return WEST;
		}
		if (strcmp(input, "look") == 0)
		{
			return LOOK;
		}
		if (strcmp(input, "fight") == 0)
		{
			return FIGHT;
		}
		if (strcmp(input, "pick") == 0)
		{
			bPickup = true;
		}
		if (strcmp(input, "exit") == 0)
		{
			return QUIT;
		}
		else if (bPickup == true)
		{
			if (strcmp(input, "up") == 0)
				return PICKUP;
		}

		char next = std::cin.peek();
		if (next == '\n' || next == EOF)
			break;
		std::cin >> input;
	}

	return 0;
}

void Game::update() 
{
	Point2D playerPos = m_player.getPosition();

	if (m_map[playerPos.y][playerPos.x].getType() == EXIT)
	{
		m_gameOver = true;
		return;
	}

	int command = getCommand();

	if (command == QUIT)
	{
		m_gameOver = true;
		return;
	}

	m_player.executeCommand(command, &m_map[playerPos.y][playerPos.x]);
		
	for (int i = 0; i < m_enemyCount; i++)
	{
		if (m_enemies[i].isAlive() == false)
		{
			Point2D pos = m_enemies[i].getPosition();
			m_map[pos.y][pos.x].setEnemy(nullptr);
		}
	}
}

void Game::draw()
{
	Point2D playerPos = m_player.getPosition();
	m_map[playerPos.y][playerPos.x].drawDescription();
	drawValidDirections();
	drawMap();
	m_player.draw();
	
}