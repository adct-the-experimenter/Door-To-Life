#ifndef DUNGEON_H
#define DUNGEON_H

#include "globalvariables.h"
#include <vector>


#include "LTimer.h"
#include "gamestate.h"

#include "Dungeon_Tile.h"
#include "dot_final.h"

#include "key.h"
#include "door.h"

#include "enemy.h"
#include "enemy_inventory.h"
#include "player.h"


class Dungeon : public GameState
{
    
public:


    //constructor to load resources
    Dungeon();

    //destructor to free resources
    ~Dungeon();
    
   
    
    //function to load dungeon media outside of Dungeon object
    friend bool loadDungeonMedia(SDL_Renderer* gRenderer,LTexture* tileMap,ALuint* source,ALuint* buffer);
    //function to free dungeon media outside of Dungeon object
    friend void freeDungeonMedia();
    
    //function to generate empty dungeon without tile clip set
    void GenerateEmptyDungeonForXMLLoad();
    
    //function to generate plain base dungeon with tile clip set.
    void GenerateBaseDungeon();
    
    
    void setLevelDimensions(std::int16_t& levelWidth, std::int16_t& levelHeight);
    
    void setPointerToMainDot(Dot* thisDot);
    void setPointerToTimer(LTimer* thisTimer);
    
    //function to set pointers to media
    void setPointersToMedia( LTexture* tileMap,ALuint* source,ALuint* buffer);

/** Tile Functions**/
    //create blank tiles for dungeonTileSet
    void createBlankTiles(std::int16_t &start_x, std::int16_t &start_y,
                          std::int16_t &tileWidth, std::int16_t &tileHeight,
                          std::int16_t& numTiles);

    
//set image clips for tiles
    // set tiles after finishing randomGeneration and its rules or loading tiles
    void setTiles();

    //delete the tiles created by createBlankTiles
    void deleteTiles();

/** Dot Functions **/

    void setDungeonCameraForDot(std::int16_t& screenWidth, std::int16_t& screenHeight,
                            SDL_Rect& camera);
                            
    void moveMainDot(float& timeStep);
    
    void PlaceDotInThisLocation(float& x, float& y);


/** Item Functions **/


     //exit by opening a door
    void exitByDoor();

    //checks if door was tried to be open with wrong key
    void checkWrongDoor();


    //delete door and key objects
    void freeDoorsAndKeys();
    

    //logic

    //checks for collision with key(s) and main dot
    void checkKeyAndDot();

    void doorCollision(float timeStep);

    /** GameState Functions**/

    //set state
    virtual void setState(GameState::State thisState);
    virtual GameState::State getState();

    
    //Game loop functions
    virtual void handle_events(Event& thisEvent);
    virtual void handle_events_RNG(RNGType& rngSeed);
    virtual void logic();
    virtual void sound(AudioRenderer* gAudioRenderer);
    virtual void render(SDL_Renderer* gRenderer);

    //exit by only touching the tile
    void exitByTile();


    int getDotTileNumber();

    //returns a number of a tile that has the x and y coordinates inputed
    int getTileNumberFromPosition(int x, int y);

    SDL_Rect getTileBox_under_dot();

    
    
    void freeResources();
    
    friend class DungeonCreator;
    friend class DungeonXMLCreator;
    friend class DungeonXMLReader;

private:

//members not inherited from GameState class


/** Dungeon Setup**/

    //start coordinates of node
    std::int16_t NODE_X;
    std::int16_t NODE_Y;
    
    //Tile width and height
    std::int16_t TILE_WIDTH;
    std::int16_t TILE_HEIGHT;

    //level dimensions
    std::int16_t LEVEL_WIDTH;
    std::int16_t LEVEL_HEIGHT;
    
    
    //pointer to texture that has tile map
    LTexture* tileTextureMap;

    //pointer to camera
    SDL_Rect lCamera;

    //pointer to timer in main
    LTimer* timer;

    //pointer to music played in dungeon
    ALuint* dgmBuffer; //buffer for dungeon music 
    ALuint* dgmSource;//source, what is playing dungeon music
    ALint musicState;
    
    //vector of DungeonTile pointers
    std::vector <DungeonTile*> dungeonTileSet;
    
    //look up table for Dungeon Tiles
    std::vector <std::vector <DungeonTile*> > dungeon_tile_look_up;
    std::int16_t numXNodeColumns;
    std::int16_t numYNodeRows;
    
    //function to return pointer to dungeon tile based on x position and y position
    DungeonTile* getDungeonTileFromPosition(int x, int y); 
    void getXColYRowFromPosition(int x, int y,size_t& xCol, size_t& yRow);
   

/** Beings in Dungeon**/
    //main character
    Dot* mainDotPointer;
    Player* mainPlayerPointer;

/** Items in Dungeon **/

    
    EnemyInventory m_enemy_inventory;
    
    void setTilesAroundCenterToFloor(size_t& xCol,size_t& yRow,size_t& xEndCol, size_t& yEndRow );
    
    std::vector <Door> dungeonDoorsVector;
    
};

#endif
