#pragma once
#include "Point2D.h"
#include <vector>

class Room;
class Powerup;
class Enemy;

class Player
{
public:
	Player();
	Player(int x, int y);
	~Player();

	void addPowerup(Powerup* powerup);
	void setPosition(const Point2D& position);
	Point2D getPosition();

	void executeCommand(int command, Room* room);
	void draw();

private:
	void pickup(Room* room);
	void attack(Enemy* enemy);

private:
	Point2D m_mapPosition;

	std::vector<Powerup*> m_powerups;

	int m_healthPoints;
	int m_attackPoints;
	int m_defendPoints;
};