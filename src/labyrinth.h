#ifndef LABYRINTH
#define LABYRINTH

#include <array>
#include "MazeGenerator.h"
#include "NodeGenerator.h"
#include "LabyrinthMap.h"
#include "gamestate.h"
#include <cmath>
#include "player.h"

#include "enemy_inventory.h" // for running enemy handle_events, logic, rendering, sound 

class Labyrinth : public GameState
{
public:
    
    Labyrinth();
    ~Labyrinth();
    
    //function to set camera
    void setCamera(SDL_Rect* thisCamera);
    
    //function to set number of nodes to generate randomly
    void randomlySetNumberOfNodesToGenerate(RNGType& rngSeed);
    
    //function to set dimensions of grid labyrinth will use.
    void setGridDimensions(std::int16_t& x,std::int16_t& y,std::int16_t& w,std::int16_t& h);
    
    //function to generate nodes and maze for labyrinth
    bool generateLabyrinth(RNGType& rngSeed);
    
    //function to setup dungeon map 
    void generateDungeonsInLabyrinth(RNGType& rngSeed,
                                     LTexture& keyTexture,
                                    ALuint& keySource,
                                    ALuint& keyBuffer,
                                    LTexture& doorTexture,
                                    ALuint& doorSource,
                                    ALuint& doorOpenSound,
                                    ALuint& doorFailSound,
                                    std::vector <SDL_Rect> *doorClips);

    //function to setup dungeon map only for debug purposes
    void generateDungeonsInLabyrinth_Debug_Gen(RNGType& rngSeed);
    
    
    //function to set pointer to timer
    void setTimerPointer(LTimer* timer);
    void setPointerToMainDot(Dot* mainDot);
    void setPointerToMainPlayer(Player* mainPlayer);
    
    //function to set pointers to media
    void setPointersToMedia(LTexture* tileMap,ALuint* source,ALuint* buffer);
    
    //function to set Dot in labyrinth
    void setupDotInLabyrinth(std::int16_t& screenWidth, std::int16_t& screenHeight,
                                SDL_Rect* camera);
                                
   //function to setup exit in maze based on dot position in maze                             
    void randomlySetExitForMaze(RNGType& rngSeed);                             
    
    //function to swap collision boxes of doors in dungeon map
    void randomlySetLabyrinthDoors(RNGType& rngSeed);
    
    
    
    //function to set tiles in dungeon
    void setTiles();
    
    //function to return pointer to vector of enemies
    std::vector <Enemy*> *GetEnemiesInLabyrinthVector();
    
//Game Loop
    virtual void setState(GameState::State thisState);
    virtual GameState::State getState();

    //Game loop functions
    virtual void handle_events(Event& thisEvent);
    virtual void handle_events_RNG(RNGType& rngSeed);
    
    virtual void logic();
    virtual void sound();
    virtual void render(SDL_Renderer* gRenderer);
    
    
    void renderNodeGeneration(SDL_Renderer* gRenderer);
    void renderMazeGeneration(SDL_Renderer* gRenderer);
    void renderDotInMazeGeneration(SDL_Renderer* gRenderer);
    void renderExitInMazeGeneration(SDL_Renderer* gRenderer);
    
    void freeResources();
    
    void setDebugBool(bool state);
    bool getDebugBool();
    
    NodeGenerator& getNodeGenerator();
    
    friend class SubMap;
    
    std::vector <CollisionObject> *GetCollisionObjectsOfHoleTiles();
    
private:
    
    //Generator for nodes
    NodeGenerator nodesGen;
    
    //Grid Dimensions for node generator and maze generator
    std::int16_t GRID_X;
    std::int16_t GRID_Y;
    std::int16_t GRID_WIDTH;
    std::int16_t GRID_HEIGHT;
    
    //number of nodes to generate in nodes gen
    std::int16_t numberNodesToGenerate; 
    void setNumberNodesToGenerate(std::int16_t& num);
    std::int16_t& getNumberNodesToGenerate();
    
    //Generator for maze
    MazeGenerator mazeGen;
    
    //function to generate nodes
    bool generateLabyrinthNodes(RNGType& rngSeed);
    //function to generate maze
    void generateLabyrinthMaze(RNGType& rngSeed);
    
//Dungeon Map

    SDL_Rect* labyrinthCamera;

    LabyrinthMap labyrinthMap;
    LTimer* labyrinthTimer;
    
    //function to setup tiles for dungeonmap from tiles from dungeon nodes
    void setupLabyrinthMapTiles(RNGType& rngSeed,std::vector <LabyrinthNode> &labyrinthNodesVector);
    //function to setup doors for dungeon map from doors in dungeon nodes
    void setupLabyrinthDoors(RNGType& rngSeed,std::vector <LabyrinthNode> &labyrinthNodesVector,
                            LTexture& keyTexture,
                            ALuint& keySource,
                            ALuint& keyBuffer,
                            LTexture& doorTexture,
                            ALuint& doorSource,
                            ALuint& doorOpenSound,
                            ALuint& doorFailSound,
                            std::vector <SDL_Rect> *doorClips);
                            
    //function to place enemies in labyrinth
    void placeEnemiesInLabyrinth(RNGType& rngSeed,
                                std::vector <LabyrinthNode> &labyrinthNodes, 
                                std::vector <Enemy*> &thisEnemiesVector);
    //pointer to vector of enemy pointers
    std::vector <Enemy*> *enemies_vector_ptr;
    
    //pointer to array of weapon pointers
    std::array <Weapon*,1> *weapons_array_ptr;
    
    //main character
    Dot* mainDotPointer;
    Player* mainPlayerPointer;
    
    LTexture* tileTextureMap;
    ALuint* dgmBuffer; //buffer for dungeon music 
    ALuint* dgmSource;//source, what is playing dungeon music
    ALint musicState;
    
    std::int16_t NODE_LEVEL_WIDTH;
    std::int16_t NODE_LEVEL_HEIGHT;
    
    std::int16_t TILE_WIDTH;
    std::int16_t TILE_HEIGHT;
    
    //function to randomly place dot in maze
    void randomlyPlaceDotInMazeNode();
    //pointer to dungeon tile dot starts at
    DungeonTile* dotStartTile;
    
    //where exit is located in maze
    size_t exitCol;
    size_t exitRow;
    //pointer to exit tile
    DungeonTile* exitTile;
    
    //array of doubles for randomly generating dimensions of labyrinth nodes
    std::array <double,5> probabilitiesGenLabyrinthNodeDimensions;
    
    //bool for debug
    bool debug;
    
    //function to set walls of labyrinth same uniform base size
    void setWallsUniformLabyrinthNode(LabyrinthNode& thisLabyrinthNode,
                                        size_t& xNodeCol, size_t& yNodeRow);
                                        
    //function to set walls of labyrinth with different pseudo dimensions
    //does it by putting invisible walls at certain rows and columns
    void setWallsRandomLabyrinthNode(LabyrinthNode& thisLabyrinthNode,
                                        size_t& xNodeCol, size_t& yNodeRow,
                                        std::int8_t& baseNumColumns, std::int8_t& baseNumRows,
                                        RNGType& rngSeed);
	EnemyInventory m_enemy_inventory;
	
};

#endif
