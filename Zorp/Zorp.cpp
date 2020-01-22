// Zorp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <random>
#include <time.h>
#include "Point2D.h"
#include "GameDefines.h"
#include "Game.h"
#include <Windows.h>
#include "Room.h"
#include "Player.h"


int main()
{ 
	/*int rooms[MAZE_HEIGHT][MAZE_WIDTH];

	bool gameOver = false;
	Point2D player = { 0, 0 };

	initialize(rooms);*/
	Game game;
	if (game.startup() == false)
		return 0;

	while (!game.isGameOver())
	{
		game.draw();
		game.update();
	}
	std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
	std::cout << std::endl << INDENT << "Press 'Enter' to exit the program.";
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
