
#pragma once
#define WALL_H
#include"BaseObject.h"

#define MAX_TILES 31

class TileMat : public BaseObject
{
public:
	TileMat() { ; }
	~TileMat() { ; }
};

class GameMap
{
public:
	GameMap() {;}
	~GameMap() {;}

	void LoadMap( string name);
	void LoadTiles(SDL_Renderer* screen);
	void DrawMap(SDL_Renderer* screen);
	Map getMap() const { return game_map_; };

private:
	Map game_map_;
	TileMat tile_mat[MAX_TILES];
};

