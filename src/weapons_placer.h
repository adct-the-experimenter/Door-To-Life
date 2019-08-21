#ifndef WEAPONS_PLACER_H
#define WEAPONS_PLACER_H

#include "labyrinth.h"
#include "weapons.h"

class WeaponsPlacer()
{
public:

	WeaponsPlacer();
	~WeaponsPlacer();
	
	//function to set pointer to Labyrinth tiles
	void setPointerToLabyrinthTiles(std::vector <DungeonTile*> *tilesVectorPtr);
	
	//function place weapon on random labyrinth node floor tile
	void placeWeaponOnRandomNodeOnFloor(Weapon* thisWeapon);
	
	//function to place weapon on random floor tile
	void placeWeaponOnRandomFloorTile(Weapon* thisWeapon);
	
private:
	
	//Pointer to vector of dungeon tiles
	std::vector <DungeonTile*> *labyrinthTilesVectorPtr;

};

#endif
