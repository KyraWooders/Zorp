#pragma once

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