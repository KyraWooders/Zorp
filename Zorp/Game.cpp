#include "pch.h"
#include "Game.h"
#include <iostream>
#include <random>
#include <time.h>

Game::Game()
{
	m_gameOver = false;
}

Game::~Game()
{
}

bool Game::startup()
{
	initializeMap();

	m_player.setPosition(Point2D{ 0,0 });

	return true;
}

bool Game::isGameOver() 
{
	return m_gameOver;
}

void Game::initializeMap()
{
	srand(time(nullptr));
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			int type = rand() % (MAX_RANDOM_TYPE * 2);
			if (type < MAX_RANDOM_TYPE)
				m_map[y][x].setType(type);
			else
				m_map[y][x].setType(EMPTY);
			m_map[y][x].setPosition(Point2D{ x, y });
		}
	}
	m_map[0][0].setType(ENTRANCE);
	m_map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1].setType(EXIT);
}

void Game::drawWelcomeMessage()
{
	std::cout << INDENT << INDENT << "Welcome to ZORP!" << std::endl;
	std::cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << std::endl;
	std::cout << INDENT << "It is definitely not related to any other text-based adventure game." << std::endl << std::endl;
}

void Game::drawMap()
{
	Point2D position = m_player.getPosition();

	std::cout << std::endl;
	std::cout << std::endl;
	for (int y = 0; y < MAZE_HEIGHT; y++) 
	{
		std::cout << INDENT;
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			if (position.x == x && position.y == y)
			{
				m_player.draw();
				continue;
			}
			m_map[y][x].draw();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Game::drawValidDirections()
{
	Point2D position = m_player.getPosition();

	std::cout << INDENT << "You can see paths leading to the " <<
		((position.x > 0) ? "west, " : "") <<
		((position.x < MAZE_WIDTH - 1) ? "east, " : "") <<
		((position.y > 0) ? "north, " : "") <<
		((position.y < MAZE_HEIGHT - 1) ? "south, " : "") << std::endl;
}

int Game::getCommand()
{
	char input[50] = "\0";
	std::cout << INDENT << "Enter a command:" << INDENT;
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	std::cin >> input;

	bool bMove = false;
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

	if (m_player.executeCommand(command))
		return;

	m_map[playerPos.y][playerPos.x].executeCommand(command);
}

void Game::draw()
{
	Point2D playerPos = m_player.getPosition();
	system("cls");
	drawWelcomeMessage();
	drawValidDirections();
	m_map[playerPos.y][playerPos.x].drawDescription();
	drawMap();
}