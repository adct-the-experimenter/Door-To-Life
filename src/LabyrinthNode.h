#ifndef LABYRINTHNODE_H
#define LABYRINTHNODE_H

#include "globalvariables.h"
#include <vector>


#include "LTimer.h"
#include "gamestate.h"

#include "Dungeon_Tile.h"
#include "dot_final.h"

#include "key.h"
#include "door.h"

#include "enemy.h"

class LabyrinthNode : public GameState
{
    //friend bool checkCollision(SDL_Rect a, SDL_Rect b);
   
public:


    //constructor to load resources
    LabyrinthNode();

    //destructor to free resources
    ~LabyrinthNode();
    
   
    
    //function to load dungeon media outside of LabyrinthNode object
    friend bool loadLabyrinthMedia(SDL_Renderer* gRenderer,LTexture* tileMap,ALuint* source,ALuint* buffer);
    //function to free dungeon media outside of LabyrinthNode object
    friend void freeLabyrinthMedia();
    
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

    //randomly generate tiles in dungeon
    void randomGeneration(RNGType& rngData, boost::random::uniform_int_distribution <> zero2twelve);
	void generateMapDrunkardWalk(RNGType& rngSeed,std::int16_t& numTiles);
	void setTileTypesRandom(RNGType& rngSeed);

    //random generation rules

    //function to decrease floor walls in map
    void genRuleWall(RNGType& rngData, boost::random::uniform_int_distribution <> zero2twelve);


    //limit number of exit tiles to a certain number. change exits not allowed into wall tiles
    void genRuleLimitExits(int exitMax,int exitMin, RNGType& rngData, boost::random::uniform_int_distribution <> zero2twelve);

//set image clips for tiles
    // set tiles after finishing randomGeneration and its rules or loading tiles
    void setTiles();

    //delete the tiles created by createBlankTiles
    void deleteTiles();

/** Dot Functions **/

    void setLabyrinthNodeCameraForDot(std::int16_t& screenWidth, std::int16_t& screenHeight,
                            SDL_Rect& camera);
                            
    void moveMainDot(float& timeStep);


/** Item Functions **/

    //setup vector for keys and doors
    void setupDoorsAndKeys(std::int8_t& numDoors,
                            std::int8_t& numKeys,
                            LTexture& keyTexture,
                            ALuint& keySource,
                            ALuint& keyBuffer,
                            LTexture& doorTexture,
                            ALuint& doorSource,
                            ALuint& doorOpenSound,
                            ALuint& doorFailSound,
                            std::vector <SDL_Rect> *doorClips                
                            );

     //exit by opening a door
    void exitByDoor();

    //checks if door was tried to be open with wrong key
    void checkWrongDoor();

    //place key randomly on a wall tile
    void placeKeyRandom(RNGType& rngData);

    void placeKeyRandomVector(RNGType& rngData);

    //place doors at floor tiles
    void placeDungeonDoors(RNGType& rngSeed);

    //delete door and key objects
    void freeDoorsAndKeys();
    
    void placeEnemies(std::vector <Enemy*> &enemy_vector,
                        size_t& startIterator, size_t& endIterator,
                        RNGType& rngSeed);

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
    virtual void sound();
    virtual void render(SDL_Renderer* gRenderer);

    //exit by only touching the tile
    void exitByTile();


    int getDotTileNumber();

    //returns a number of a tile that has the x and y coordinates inputed
    int getTileNumberFromPosition(int x, int y);

    SDL_Rect getTileBox_under_dot();

    void countNumberOfExits();

    int getNumberOfExits();
    
    //functions to set walls on sides of labyrinth node
    void setWallTopSide();
    void setWallLeftSide();
    void setWallRightSide();
    void setWallBottomSide();
    
    //function to set certain kinds of wall in a certain row or column
    void setTopWallOnThisRow(size_t& rowNum);
    void setLeftWallOnThisColumn(size_t& colNum);
    void setRightWallOnThisColumn(size_t& colNum);
    void setBottomWallOnThisRow(size_t& rowNum);
    
    //functions to set invisible walls 
    //Use to give illusion that nodes are different dimensions
    void setInvisibleWallOnThisRow(size_t& rowNum);
    void setInvisibleWallOnThisColumn(size_t& colNum);
    
    friend class LabyrinthMap;

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
    
    int numberOfExits;


/** Beings in Dungeon**/
    //main dot
    Dot* mainDotPointer;

/** Items in Dungeon **/

    //vector of pointers to key objects
    std::vector <Key*> dungeonKeys;
    
    //vector of pointers to door objects
    std::vector <Door*> dungeonDoors;
    
    //vector of pointers to enemy objects
    std::vector <Enemy*> dungeonEnemies; 
    
    bool keyDisappear;

    //number of times all SFX can be looped
    int loopSFX;

    //function to place 1 dungeon door
    void placeThisOneDungeonDoor(RNGType& rngSeed,Door* thisDoor);
    
    void setTilesAroundCenterToFloor(size_t& xCol,size_t& yRow,size_t& xEndCol, size_t& yEndRow );
    
    //function to place 1 enemy in node
    void placeThisOneEnemy(RNGType& rngSeed,Enemy* thisEnemy);
    
    std::vector <CollisionObject> hole_tiles_vector;
    void initializeHoleTileVector();
};

#endif
