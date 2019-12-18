// Zorp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <random>
#include <time.h>
#include "Point2D.h"

const char* const INDENT = "\t";
const char* const EMPTY_TITLE = "[ \xb0 ]";
const char* const ENEMY_TITLE = "[ \x94 ]";
const char* const TREASURE_TITLE = "[ $ ]";
const char* const FOOD_TITLE = "[ \xcf ]";
const char* const ENTRANCE_TITLE = "[ \x9d ]";
const char* const EXIT_TITLE = "[ \xFE ]";
const char* const PLAYER_TILE = "[ X ]";

const int EMPTY = 0;
const int ENEMY = 1;
const int TREASURE = 2;
const int FOOD = 3;
const int ENTRANCE = 4;
const int EXIT = 5;
const int MAX_RANDOM_TYPE = FOOD + 1;

const int MAZE_WIDTH = 10;
const int MAZE_HEIGHT = 6;

const int WEST = 4;
const int EAST = 6;
const int NORTH = 8;
const int SOUTH = 2;
const int LOOK = 9;
const int FIGHT = 10;


void initialize(int map[MAZE_HEIGHT][MAZE_WIDTH])
{
	srand(time(nullptr));

	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			int type = rand() % (MAX_RANDOM_TYPE * 2);
			if (type < MAX_RANDOM_TYPE)
			{
				map[y][x] = type;
			}

			map[y][x] = EMPTY;
		}
	}

	map[0][0] = ENTRANCE;
	map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1] = EXIT;
}

void drawWelcomeMessage()
{
	std::cout << INDENT << INDENT << "Welcome to ZORP!" << std::endl;
	std::cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << std::endl;
	std::cout << INDENT << "It is definitely not related to any other text-based adventure game." << std::endl << std::endl;
}

void drawMap(int map[MAZE_HEIGHT][MAZE_WIDTH], Point2D position)
{
	std::cout << std::endl;
	std::cout << std::endl;
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		std::cout << INDENT;
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			if (position.x == x && position.y == y)
			{
				std::cout << PLAYER_TILE;
				continue;
			}
			switch (map[y][x])
			{
			case EMPTY:
				std::cout << EMPTY_TITLE;
				break;
			case ENEMY:
				std::cout << ENEMY_TITLE;
				break;
			case TREASURE:
				std::cout << TREASURE_TITLE;
				break;
			case FOOD:
				std::cout << FOOD_TITLE;
				break;
			case ENTRANCE:
				std::cout << ENTRANCE_TITLE;
				break;
			case EXIT:
				std::cout << EXIT_TITLE;
				break;
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void drawRoomDesription(int roomType)
{
	switch (roomType)
	{
	case EMPTY:
		std::cout << INDENT << "You are in an empty meadow. There is nothing of note here." << std::endl;
		break;
	case ENEMY:
		std::cout << INDENT << "Beware. An enemy is approaching." << std::endl;
		break;
	case TREASURE:
		std::cout << INDENT << "Your journey has been rewarded. You have found some treasure" << std::endl;
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

void drawVaildDirections(Point2D position)
{
	std::cout << INDENT << "You can see paths leading to the " <<
		((position.x > 0) ? "west, " : "") <<
		((position.x < MAZE_WIDTH - 1) ? "east, " : "") <<
		((position.y > 0) ? "north, " : "") <<
		((position.y < MAZE_HEIGHT - 1) ? "south, " : "") << std::endl;
}

int getCommand()
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

void waitForInput()
{
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
}

int main()
{ 
	int rooms[MAZE_HEIGHT][MAZE_WIDTH];

	bool gameOver = false;
	Point2D player = { 0, 0 };

	initialize(rooms);

	while (!gameOver)
	{
		system("cls");

		drawWelcomeMessage();
		
		drawMap(rooms, player);

		drawRoomDesription(rooms[player.y][player.x]);
		if (rooms[player.y][player.x] == EXIT)
		{
			gameOver = true;
			break;
		}
		
		drawVaildDirections(player);
		std::cout << INDENT << "Where to now?" << std::endl;

		int direction = getCommand();

		switch (direction)
		{
		case EAST:
			if (player.x < MAZE_WIDTH - 1)
				player.x++;
			break;
		case WEST:
			if (player.x > 0)
				player.x--;
			break;
		case NORTH:
			if (player.y < MAZE_HEIGHT - 1)
				player.y++;
			break;
		case SOUTH:
			if (player.y > 0)
				player.y--;
			break;
		case LOOK:
			std::cout << INDENT << "You look around, but see nothing worth mentioning" << std::endl;
			std::cout << INDENT << "Press 'Enter' to continue.";
			waitForInput();
			break;
		case FIGHT:
			std::cout << INDENT << "You could try to fight, but yyou don't have a weapon" << std::endl;
			std::cout << INDENT << "Press 'Enter' to continue.";
			waitForInput();
			break;
		default:
			std::cout << INDENT << "You try, but you just can't do it." << std::endl;
			std::cout << INDENT << "Press 'Enter' to continue.";
			waitForInput();
			break;
		}
	}
	std::cout << std::endl << INDENT << "Press 'Enter' to exit the program." << std::endl;
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
