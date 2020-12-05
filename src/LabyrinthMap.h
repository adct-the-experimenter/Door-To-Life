#ifndef LABYRINTHMAP_H
#define LABYRINTHMAP_H

#include "weapon.h"
#include "LabyrinthNode.h"
#include <array>
#include <algorithm>    // std::random_shuffle
#include <ctime>

#include "DrawingManager.h"
#include "player_manager.h"

//class to contain graphical part of labyrinth

class LabyrinthMap
{
public:
    LabyrinthMap();
    ~LabyrinthMap();
    
    //function to pass objects of DungeonNode to LabyrinthMap 
    void loadMapFromLabyrinthNodes(std::vector <LabyrinthNode> &LabyrinthNodes);
    
    //function to pass tiles of LabyrinthNodes to LabyrinthMap
    void loadTilesFromLabyrinthNodes(std::vector <LabyrinthNode> &LabyrinthNodes);
    //function to pass doors of LabyrinthNodes to LabyrinthMap
    void loadDoorsFromLabyrinthNodes(std::vector <LabyrinthNode> &LabyrinthNodes);
    
    
    //function to set tile clips for tiles in LabyrinthMap
    void setClipsForTiles();
    
    //function to free tiles of LabyrinthMap
    void freeTiles();
    
    void setLabyrinthCameraForDot(Dot* mainDotPointer, 
                                std::int16_t& screenWidth, std::int16_t& screenHeight);
    //Door
    //function to create doors
    void createDoorsInLabyrinthMap(std::int8_t& numberDoors,
                                    LTexture* doorTexture,
                                    ALuint* source,
                                    ALuint* doorBufferOpen, 
                                    ALuint* doorBufferFail);
                                    
    //function to place doors
    void randomlyPlaceLabyrinthDoors(RNGType& rngSeed);
    
    //function to push dot back if collide with door
    void doorToDot_Logic(Dot* mainDotPointer,float& timeStep,SDL_Rect* thisCmaera);
    
    //function to do door handle events 
    void door_handle_events(Event& thisEvent,SDL_Rect* thisCamera);
    
    //function to play sounds 
    void play_door_sounds();
    
    //function to transport dot through door
    //bool is true if going from one to two, false for two to one
    void transferDotThroughDoor(Dot* mainDotPointer, Door* thisDoor, bool One_To_Two);
    
    //function to free doors and keys of LabyrinthMap
    void freeDoorsAndKeys();
    
//Game loop functions

    //function to move main dot on tiles in LabyrinthMap
    void moveMainDot(Dot* mainDotPointer,float& timeStep,SDL_Rect* thisCamera);

    //function to render tiles
    void renderTiles(SDL_Renderer* gRenderer,LTexture* tileTextureMap);
    
    void renderTiles(PlayerManager* playerManager,DrawingManager* gDrawManager,LTexture* tileTextureMap);

    void renderDotInLabyrinthMap(SDL_Renderer* gRenderer,Dot* mainDotpointer,SDL_Rect* thisCamera);
    
    void renderDoors(SDL_Renderer* gRenderer);
    
    void renderDoors(PlayerManager* playerManager,DrawingManager* gDrawManager);
    

    friend class Labyrinth;
    
private:
    //vector of tiles in Labyrinth map
    std::vector <DungeonTile*> labyrinthTilesVector;
    
    //camera for dungeon map
    SDL_Rect* lCamera;

    //dungeon keys
    std::vector <Key*> labyrinthKeysVector;
    //dungeon doors
    std::vector <Door*> labyrinthDoorsVector;
    
    //pointer to vector of enemy pointers
    std::vector <Enemy*> *labyrinthEnemiesVector;
    
    //pointer to array of weapon pointers
    std::array <Weapon*,1> *labyrinthWeaponsArray;
    
    //vector for collision objects for hole tiles
    std::vector <CollisionObject> labyrinth_hole_tiles_vector;
};

#endif
