#ifndef DUNGEON_TILE_H
#define DUNGEON_TILE_H

#include "globalvariables.h"

#include <stdio.h>
#include <string>

#include <iostream>
#include <fstream>
#include <vector>

#include "LTexture.h"
#include "TileMapDimensions.h"

#include <cstdint>

#include "collisionobject.h"

//The tile
class DungeonTile
{
 

    public:

		//Constructor to initialize resources
		DungeonTile( std::int16_t& x, std::int16_t& y, 
                    std::int16_t& width, std::int16_t& height,
                    std::int16_t& tileNumber);
        //Destructor to free resources
		~DungeonTile();

/** Tile Attributes**/

        //enum class for type
        enum class TileType : std::int8_t { //floor tiles
                                            RED = 0,GREEN,BLUE,
                                            //wall tiles
                                            TOP_LEFT,LEFT,BOTTOM_LEFT,
                                            TOP,CENTER,BOTTOM,
                                            TOP_RIGHT,RIGHT,BOTTOM_RIGHT,
                                            INVISIBLE_WALL,
                                            //exit tile
                                            EXIT,
                                            //empty tile
                                            EMPTY,
                                            //door tile
                                            DOOR,
                                            //occupied, something is already on it like enemy
                                            OCCUPIED,
                                            DUNGEON_ENTRANCE
                                            };

        //Set tile type
        //void setType(int tileType);
        void setType(DungeonTile::TileType tileType);
		//Get the tile type
		DungeonTile::TileType getType();
        //int getType();
        
       //friend function to return bool if box collides with a wall type tile
        friend bool touchesDungeonWallVector(SDL_Rect& box, std::vector<DungeonTile*> &dungeonTiles);

        //friend function to return tile type of what box collides with in a vector of tiles
        friend DungeonTile::TileType touchesDungeonTile(SDL_Rect& box, 
                                                        std::vector<DungeonTile*> &dungeonTiles);
        
        friend SDL_Rect* getTileBoxPointer(DungeonTile* thisTile);
        
        //Get bools for whether tile is floor tile or wall tile
		bool getTypeFloor();
		bool getTypeWall();
		bool getTypeExit();
		bool getTypeEmpty();
        //set tile type
        
        //function to set tile type to empty
        void setTileEmpty();
        
		//get the number of total tiles
		int getTotalTiles();

		//Get the collision box
		SDL_Rect& getBox();

		int getXPosition(); 
		int getYPosition(); //get x and y position of collision box

		int getTileNumber();


/** Setup Fuctions**/

        //set individual tile clip for each tile that is contrustucted. Don't want or need vector of tile clips for each tile made.
        void setTileClips();

        //friend function to determine tile type for a dungeon tile from a value read from a file
        friend bool readLoadTiles(std::string path,int numberBytes,int totalTiles);
        
        //friend function to write vector of tile types to file
        bool writeOutTilesToFile();

/** Make functions**/


        // get random numbers from main and use rules to set tile type plus  output to file
        void randomGenerateTile(int randomNumber);


    //functions to limit the number of exits in map.
        //use randomnumber to decide whether to allow exit or not. return true if yes, return false if no
        void genRuleAllowExit( int randomNumber );

        //bool to allow exit
        bool exitAllowed;

        //turn exit tiles not allowed to be exits into wall tiles
        void genRuleChangeExitTile();


/** Save Function**/
        //use standard c++ file reading and output to save tile info
        bool writeSaveTiles(std::string path,int numberBytes, int totalTiles);

        //use SDL file read write for cross platform  file reading and writing
        bool writeSaveTiles_SDLRW();

/** Rendering**/
		//Shows the tile
		void render( LTexture* tileTextureMap,SDL_Rect& camera,SDL_Renderer* lRenderer);

/** Static Constants for Tiles**/
        //Tile constants
        static const int TOTAL_TILE_SPRITES = 13;

		

    private:

        //Tile dimensions and number
        std::int16_t TILE_WIDTH;
        std::int16_t TILE_HEIGHT;


		//The attributes of the tile
		SDL_Rect mBox;

		//The tile type
		DungeonTile::TileType mType;

        // bool to see what tile is
		bool floorTileBool;
		bool wallTileBool;
		bool exitTileBool;
        bool emptyTileBool;
		//the number of the tile
		std::int16_t mNumber;

        //tile clip
        SDL_Rect dTileClip;
};

#endif // TILE_H
