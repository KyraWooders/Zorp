#pragma once
#include "Point2D.h"
#include <vector>
#include "Character.h"

class Room;
//class Powerup;
class Enemy;

class Player : public Character
{
public:
	Player();
	Player(int x, int y);
	~Player();

	void executeCommand(int command, Room* room);
	void draw();
	void drawDescription();
	void lookAt();

private:
	void pickup(Room* room);
	void attack(Enemy* enemy);

};