#pragma once
#include "Point2D.h"

class Powerup;
class Player;
class Enemy;
class Food;

class Room
{
public:
	Room();
	~Room();

	void setPosition(Point2D position);
	void setType(int type);
	void setEnemy(Enemy* enemy) { m_enemy = enemy; }
	void setPowerup(Powerup* powerup) { m_powerup = powerup; }
	void setFood(Food* food) { m_food = food; }

	int getType();
	Enemy* getEnemy() { return m_enemy; }
	Powerup* getPowerup() { return m_powerup; }
	Food* getFood() { return m_food; }

	void draw();
	void drawDescription();

	/*bool executeCommand(int command, Player* player);

private:
	bool pickup(Player* player);*/

private:
	Point2D m_mapPosition;
	int m_type;

	Powerup* m_powerup;
	Enemy* m_enemy;
	Food* m_food;
};

