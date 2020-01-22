#pragma once
#include "Point2D.h"

class Powerup;
class GameObject;
class Enemy;
class Food;

class Room
{
public:
	Room();
	~Room();

	void setPosition(Point2D position);
	void setType(int type);
	
	int getType() { return m_type; }
	Enemy* getEnemy();
	Powerup* getPowerup();
	Food* getFood();

	void addGameObject(GameObject* object);
	void removeGameObject(GameObject* object);

	void draw();
	void drawDescription();
	void lookAt(); 

	/*bool executeCommand(int command, Player* player);

private:
	bool pickup(Player* player);*/

private:
	Point2D m_mapPosition;
	int m_type;

	std::vector < GameObject*> m_objects;
};

