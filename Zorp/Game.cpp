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

