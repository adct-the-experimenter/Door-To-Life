#ifndef WINNER_DECISION_ROOM_H
#define WINNER_DECISION_ROOM_H

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

#include "game_inventory.h"

#include "player_manager.h"

#include "winner_judge.h"

class WinnerDecisionRoom : public GameState
{
    
public:

    //constructor to load resources
    WinnerDecisionRoom();

    //destructor to free resources
    ~WinnerDecisionRoom();
    
    //function to load dungeon media outside of WinnerDecisionRoom object
    friend bool loadWinnerDecisionRoomMedia(SDL_Renderer* gRenderer,LTexture* tileMap,
											LTexture* wnjudge1_texture,LTexture* wnjudge2_texture,LTexture* wnjudge3_texture,LTexture* wnjudge4_texture,
											ALuint* source,ALuint* buffer);
											
    //function to free dungeon media outside of WinnerDecisionRoom object
    friend void freeWinnerDecisionRoomMedia(LTexture* tileMap,
											LTexture* wnjudge1_texture,LTexture* wnjudge2_texture,LTexture* wnjudge3_texture,LTexture* wnjudge4_texture,
											ALuint* source,ALuint* buffer);
    
    //function to generate plain base dungeon with tile clip set.
    void GenerateBaseRoom();
    
    void setLevelDimensions(std::int16_t& levelWidth, std::int16_t& levelHeight);
    
    void setPointerToTimer(LTimer* thisTimer);
    
    //function to set pointers to media
    void setPointersToMedia( LTexture* tileMap,
							LTexture* winner_judge1,LTexture* winner_judge2,LTexture* winner_judge3,LTexture* winner_judge4,
							ALuint* source,ALuint* buffer);

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

    void SetPointerToMainPlayer(Player* player);
                            
    void moveMainDot(float& timeStep);
    
    void moveMainDot(Player* thisPlayer,float &timeStep,SDL_Rect* thisCamera);
    
    void PlaceDotInThisLocation(float& x, float& y);
    
    void PlacePlayerInLocationNearEntrance(Player* thisPlayer);

	void PlacePlayerInThisLocation(Player* thisPlayer, float& x, float& y);

/** Item Functions **/

    //logic

    //checks for collision with key(s) and main dot
    void checkKeyAndDot();

    /** GameState Functions**/

    //set state
    virtual void setState(GameState::State thisState);
    virtual GameState::State getState();

    
    //Game loop functions
    virtual void handle_events(Event& thisEvent);
    virtual void handle_events_RNG(RNGType& rngSeed);
    
    void logic_alt(float& timeStep);
    virtual void logic();
    
    virtual void sound(AudioRenderer* gAudioRenderer);
    virtual void render(SDL_Renderer* gRenderer);
	virtual void render(DrawingManager* gDrawManager);


    int getDotTileNumber();

    //returns a number of a tile that has the x and y coordinates inputed
    int getTileNumberFromPosition(int x, int y);

    SDL_Rect getTileBox_under_dot();
    
    void freeResources();
    
    
    void SetPointerToPlayerManager(PlayerManager* pm);
	void SetPointerToGameInventory(GameInventory* thisInventory);
	
		
private:

//members not inherited from GameState class


/** Room Setup**/
	
		
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

    //pointer to timer in main
    LTimer* timer;

    //pointer to music played in dungeon
    ALuint* roomBuffer; //buffer for dungeon music 
    ALuint* roomSource;//source, what is playing dungeon music
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
    
    //main player that dungeon revolves around. Each player has a dungeon 
    Player* mainPlayer;
    
    PlayerManager* m_player_manager_ptr;
    

/** Items in Dungeon **/
	
	GameInventory* mainInventoryPtr;
    
    //pointer to winner decision room exit
    DungeonTile* exitTilePtr;
    
    WinnerJudge one_player_winner_judge;
    WinnerJudge two_player_winner_judge;
    WinnerJudge three_player_winner_judge;
    WinnerJudge four_player_winner_judge;
};

#endif
