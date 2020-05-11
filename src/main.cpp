
#include "globalvariables.h"

#include <stdio.h>
#include <stdint.h> //header for integer types

#include <string>
#include <iostream>
#include <sstream> //header for string stream processing
#include <memory> //for unique pointers
#include <vector>
#include <stack>

#include "pause_menu.h"
#include "title.h"


#include "player.h"
#include "healthbar.h"

#include "collisionhandler.h"
#include "event_handler.h"

#include "frame_rate_cap.h" // for frame rate cap class 
#include "submap.h"

#include "enemy_media_loader.h" //for loading media for enemies
#include "enemy_inventory.h" // for handling enemies in world
#include "weapons_loader.h" //for loading media for weapons
#include "game_inventory.h" //for weapons and items in game world 
#include "player_media_loader.h" //for loading media for player

/** Constants and Global Variables**/

std::int16_t SCREEN_X_START = 0;
std::int16_t SCREEN_Y_START = 0;
std::int16_t SCREEN_WIDTH = 640;
std::int16_t SCREEN_HEIGHT = 480;

std::int16_t LEVEL_WIDTH = SCREEN_WIDTH * 2;
std::int16_t LEVEL_HEIGHT = SCREEN_HEIGHT * 2;


//The window we'll be rendering to
SDL_Window* gWindow = nullptr;
//The window renderer
SDL_Renderer* gRenderer = nullptr;
//Globally used font
TTF_Font* gFont = nullptr;

//renderer driver to use
int num_render_driver = -1;
bool use_software_fallback = false;
int checkForRendererDriverInput(int& argc, char* argv[]);

//Set text color as gray
SDL_Color textColor = {96,96,96 };



// Game Over

//Game over texture
LTexture gameOverTexture;
//sound effect for game over
ALuint gameOverMusicSource;
ALuint gameOverMusicBuffer;
bool loadMedia_gameover();

//Win Game
LTexture gameWonTexture;

ALuint winMusicSource;
ALuint winMusicBuffer;
bool loadMedia_gamewin();
void GameWon();

//Main Game

//The camera
SDL_Rect camera = { 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT  };
//Timer for frame rate
LTimer stepTimer; //keeps track of time between steps
int loop = 0;

//Pointer to main sprite object pointer
std::unique_ptr <Dot> mainDotPointer;
bool initMainChar();
Player* mainPlayer = nullptr;


/** Functions **/
//intializes and loads resources
bool init();
//initialize SDL 2
bool initSDL2();
//initializes and loads resources not from SDL, e.g openal,sdl_mixer,
bool initExtLibs();



//loads files and other resources
bool loadMedia();
bool loadMedia_score();

#include "dungeon_media_loader.h" //for doors,keys,dungeon music
                            
//frees and closes resources
void close();

/** Stack Functions **/
//Structure for function pointer to point to states
struct StateStruct
{
    void(*StatePointer)();
};

//Pointer to base class GameState to use for polymorphism
GameState* baseGameState = NULL;

// stack of structure stateStruct
std::stack<StateStruct> state_stack;

bool pauseStack = false;

//Runs a loop of functions for the game like event handling, logic, rendering
void GameLoop();
void DungeonGameLoop();

//class object to limit frame rate
FrameRateCap frameRateCap;

//class object to display relative position of main char
SubMap subMap;

/**States **/

void NodeGeneration();
StateStruct NodeGenStateStructure;

 
void Dungeon1();
StateStruct gDungeon1StateStructure; //declare StateStruct for game loop
//function to setup labyrinth and return a bool to tell if sucess or not 
bool setupLabyrinth(Labyrinth& thisLabyrinth);

void Dungeon2();
StateStruct gDungeon2StateStructure; //declare StateStruct for game loop

            
//Title
std::unique_ptr <Title> gTitle;
void TitleState();
StateStruct gTitleStateStructure;
bool initTitleState();

//Load game Resources
void LoadGameResourcesState();
StateStruct LoadGameResourcesStateStructure;


//helper function to show game over screen
void GameOver();
//helper function to show transition screen
void Transition();

/** Random Set up **/
typedef boost::mt19937_64 RNGType;
RNGType rng( std::time(0) );
boost::random::uniform_int_distribution <int> zero_to_twelve( 0, 12 );


//OpenAL Soft sound
ALCdevice* gAudioDevice = nullptr; //audio device to be used
ALCcontext* alContext = nullptr; //context of where audio is played
bool initOpenALSoft();
void cleanup_openALSoft();
//renderer that plays audio
AudioRenderer gAudioRenderer;

//Menu
std::unique_ptr <PauseMenu> gPauseMenu;
void runMenuState();
void MenuState();
bool quitGame = false;
//single state structure for pause menu
StateStruct gMenuStateStructure;
bool initPauseMenu();



//Health bar
HealthBar playerHealthBar;
//friend function to setup a texture for health bar
bool loadMedia_HealthBar(LTexture* healthTex,SDL_Renderer* gRenderer);
//friend function to free a texture for health bar
void freeMedia_HealthBar(LTexture* healthTex); 
LTexture healthBarTexture;

std::unique_ptr <CollisonHandler> collisionHandler;
std::unique_ptr <GameInventory> gameInventory;

std::unique_ptr <PlayerInventory> playerInventory;



int main(int argc, char* args[])
{
    //std::cout << args[0];
    if(checkForRendererDriverInput(argc,args) != 0)
    {
		return -1;
	}
    //Start up SDL and create window

	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
        NodeGenStateStructure.StatePointer = NodeGeneration;
        gDungeon1StateStructure.StatePointer = Dungeon1;
        //gDungeon2StateStructure.StatePointer = Dungeon2;
        LoadGameResourcesStateStructure.StatePointer = LoadGameResourcesState;
        
        /**Push first state in stack **/
        //Start off by pushing function GameLoop pointer to the stack

        state_stack.push(gTitleStateStructure); //push game title to stack

        while(!quitGame) //while state_stack is not empty, terminates if game_intro is popped off
        {
            //call the function pointer of the StateStruct on top of the stack
            if(!pauseStack){state_stack.top().StatePointer();}
        }
        
        //empty stack
        while(!state_stack.empty()){state_stack.pop(); }

        //When while loop ends

        //Set pointers to sprite object to nullptr
        mainDotPointer = nullptr;
        
        close();
        return 0;
        
    
    }
}

void DungeonGameLoop()
{
    //start cap timer
    frameRateCap.startCapTimer();
    
    //Handle events
    run_event_handler();
    
    //while event queue is not empty
    while( !isEventQueueEmpty() )
    {
        baseGameState->handle_events(getEventInstanceFront());
        //pop element in front of event queue
        popEventInstanceFromFront();
    }
    
    baseGameState->handle_events_RNG(rng);
    collisionHandler->run_collision_handler(); //run collision handler to update collision states
    
    //calculate FPS 
    frameRateCap.calculateFPS();
    
    //Logic
    
    baseGameState->logic(); //run logic module
    
    gameInventory->checkWeaponsOnGround_Collision(playerInventory.get()); //check if weapon is picked up from ground
    playerHealthBar.updateHealthBar(mainPlayer->getHealthAddress()); //update player health
    
    //play audio
    baseGameState->sound(&gAudioRenderer);

    //clear screen
     SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
     SDL_RenderClear( gRenderer );

    //Render
    baseGameState->render(gRenderer);
    
    //render fps
    //frameRateCap.renderFrameRate(SCREEN_WIDTH,SCREEN_HEIGHT,gFont,gRenderer);
    //render health bar
    playerHealthBar.render(SCREEN_WIDTH,SCREEN_Y_START,gRenderer);
    //render sub map
    subMap.renderSubMapAndDot(mainDotPointer.get(),gRenderer);
    
    //update screen
    SDL_RenderPresent(gRenderer);
    
    //count this frame
    frameRateCap.countFrame();
    //delay if frame finished early
    frameRateCap.delayForEarlyFrameFinish();
}

void GameLoop()
{
    //Handle events
    run_event_handler();
    
    //while event queue is not empty
    while( !isEventQueueEmpty() )
    {
        baseGameState->handle_events(getEventInstanceFront());
        //pop element in front of event queue
        popEventInstanceFromFront();
    }
    
    //Logic
    
    baseGameState->logic(); //run logic module
    //play audio
    baseGameState->sound(&gAudioRenderer);

    //clear screen
    SDL_RenderClear(gRenderer);

    //Render
    baseGameState->render(gRenderer);

    //update screen
    SDL_RenderPresent(gRenderer);

}



/** States Implementation**/
void NodeGeneration()
{
    Labyrinth labyrinth;
    
    labyrinth.setPointerToMainDot(mainDotPointer.get());
    
    //set dimenstions of grid labyrinth will use for generating map
    std::int16_t x = 20;
    std::int16_t y = 20;
    std::int16_t w = 400;
    std::int16_t h = 400;
    labyrinth.setGridDimensions(x,y,w,h);
    labyrinth.randomlySetNumberOfNodesToGenerate(rng);
    
    //bool to restart state to generate new maze
    bool generateNewMazeBool = false;
    
    if(labyrinth.generateLabyrinth(rng))
    {
        labyrinth.generateDungeonsInLabyrinth_Debug_Gen(rng);

        labyrinth.setupDotInLabyrinth(SCREEN_WIDTH, SCREEN_HEIGHT,
                                      &camera);
                                      
        labyrinth.randomlySetExitForMaze(rng);
        
        
        std::int8_t state = 1;
        //state 
        /*
         *  0 = Blank
            1 = Render Empty Grid
            2 = Render Empty Grid + Temp Nodes
            3 = Render Empty Grid + Temp + Kept Nodes
            4 = Render maze
        */
        std::cout << "Generated Maze! \n";
        
        bool quit = false;
        
        while(!quit)
        {
            
             //Handle events
            run_event_handler();
            
            //while event queue is not empty
            while( !isEventQueueEmpty() )
            {
                switch(getEventInstanceFront())
                {
                    case Event::ESCAPE:{ quit = true; break;}
                    case Event::G:{ state = 1; break;}
                    case Event::V:{ state = 2; break;}
                    case Event::B:{ state = 3; break;}
                    case Event::N:{ state = 4; break;}
                    case Event::R:{ quit = true; generateNewMazeBool = true; break;}
                    default:{ break;}
                }
                //pop element in front of event queue
                popEventInstanceFromFront();
            }
            
            //render
             SDL_SetRenderDrawColor(gRenderer,
                               0,
                               0,
                               0,
                               50);
            SDL_RenderClear(gRenderer);
            
            if(state == 1){labyrinth.getNodeGenerator().renderEmptyGrid(gRenderer);}
            else if(state == 2){labyrinth.getNodeGenerator().renderTempNodes(gRenderer);}
            else if(state == 3){labyrinth.getNodeGenerator().renderKeptNodes(gRenderer);}
            else if(state == 4)
            {
                labyrinth.renderMazeGeneration(gRenderer);
                labyrinth.renderDotInMazeGeneration(gRenderer);
                labyrinth.renderExitInMazeGeneration(gRenderer);
            }
            
            SDL_RenderPresent(gRenderer);
        }
        
        //free labyrinth resources
        labyrinth.freeResources();
         
         //if not generating new maze 
         if(!generateNewMazeBool){quitGame = true;}
        //state_stack.pop();
    }
}

void Dungeon1()
{
    
	std::unique_ptr <Labyrinth> labyrinthUPtr(new Labyrinth() );
	
    
    std::unique_ptr <CollisonHandler> ptrToCollisionHandler(new CollisonHandler());
    if(!ptrToCollisionHandler){return;}
    else
    {
        collisionHandler = std::move(ptrToCollisionHandler);
    }
    
    std::unique_ptr <GameInventory> ptrToGameInventory(new GameInventory());
    if(!ptrToGameInventory){return;}
	else
	{
		gameInventory = std::move(ptrToGameInventory);
		gameInventory->SetPointerToCollisionHandler(collisionHandler.get());
	}
	

	
	std::unique_ptr <PlayerInventory> ptrToPlayerInventory(new PlayerInventory());
    if(!ptrToPlayerInventory){return;}
	else
	{
		playerInventory = std::move(ptrToPlayerInventory);
	}
	
	//add player to collision system
	collisionHandler->addPlayerToCollisionSystem( mainPlayer->getCollisionObjectPtr() );
	//pass pointer to player to player inventory
	playerInventory->SetPointerToPlayer(mainPlayer);
	//pass pointer to player inventory to game inventory
	gameInventory->SetPointerToPlayerInventory(playerInventory.get());
	//add player height to audio renderer
	int pHeight = mainPlayer->getPlayerHeight();
	gAudioRenderer.SetPlayerHeight(pHeight);
	
	//reset player attributes
	std::int16_t initialHealth = 100;
	mainPlayer->setHealth(initialHealth);
	mainPlayer->setPlayerState(Player::PlayerState::NORMAL);
	
	playerInventory->unequipWeaponFromPlayer();
	collisionHandler->EmptyPlayerEquippedWeapon();
	
	
    //if setup labyrinth was successful
    if(setupLabyrinth(*labyrinthUPtr.get()))
    {
		   
        /** GameLoop **/
        //set base game state to gDungeon1
        baseGameState = labyrinthUPtr.get();
        baseGameState->setState(GameState::State::RUNNING);
        //start timers 
        stepTimer.start();
        frameRateCap.startFrameCount();
        
        
        bool quit = false;
        
        while(!quit)
        {
            //call game loop function
            DungeonGameLoop();
            

            if(baseGameState->getState() == GameState::State::EXIT 
                || baseGameState->getState() == GameState::State::NEXT
                || baseGameState->getState() == GameState::State::GAME_OVER)
            {
                stepTimer.stop();
                quit = true;
            }
            else if(baseGameState->getState() == GameState::State::PAUSE)
            {
                //stop timer
                
                stepTimer.stop();
                runMenuState();
                //restart timer
                stepTimer.start();
            }

        }
        
        collisionHandler->EmptyCollisionObjectVector();
		gameInventory->freeWeapons();
		
        //delete doors and keys
		//delete tiles
		labyrinthUPtr->freeResources();
		
        if(baseGameState->getState() == GameState::State::EXIT )
        {
            
            
            baseGameState = nullptr;

            quitGame = true;
        }
        else if(baseGameState->getState() == GameState::State::GAME_OVER )
        {	
            baseGameState = nullptr;
            GameOver();
        }

        else if(baseGameState->getState() == GameState::State::NEXT)
        {
            //go to next dungeon
            baseGameState = nullptr;
            
            GameWon();
            
            quitGame = true;
        }

        loop += 1;
        std::cout << "Loop: " <<loop << std::endl;
    }
    //else do nothing
    else{std::cout << "Failed to setup labyrinth! \n";}
	
}

bool setupLabyrinth(Labyrinth& thisLabyrinth)
{
    thisLabyrinth.setTimerPointer(&stepTimer);
    thisLabyrinth.setPointerToMainDot(mainDotPointer.get());
    thisLabyrinth.setPointerToMainPlayer(mainPlayer);
    thisLabyrinth.setPointersToMedia(&dungeonTilesTexture,&dungeonMusicSource,&dungeonMusicBuffer);
	thisLabyrinth.SetPointerToGameInventory(gameInventory.get());
	
    //set dimenstions of grid labyrinth will use for generating map
    std::int16_t x = 0;
    std::int16_t y = 0;
    std::int16_t w = 400;
    std::int16_t h = 400;
    thisLabyrinth.setGridDimensions(x,y,w,h);
    thisLabyrinth.randomlySetNumberOfNodesToGenerate(rng);
   
    
    //if able to generate labyrinth
    if( thisLabyrinth.generateLabyrinth(rng) )
    {
        
       
        //Setup world of labyrinth
        thisLabyrinth.generateDungeonsInLabyrinth(rng,
                                          keyTexture, keySource,keyBuffer,
                                          doorTexture,doorSource,doorBufferOpen,doorBufferFail, &doorClips);

        thisLabyrinth.setupDotInLabyrinth(SCREEN_WIDTH, SCREEN_HEIGHT,
                                      &camera);
        
        thisLabyrinth.randomlySetExitForMaze(rng);
        thisLabyrinth.randomlySetLabyrinthDoors(rng);
        
        thisLabyrinth.setTiles();
        
        
        
        //setup weapons in labyrinth
        
        //setup default weapon for player
        std::int16_t xPosPlayer = mainPlayer->getCollisionBox().x - 3 * mainPlayer->getCollisionBox().w;
        std::int16_t yPosPlayer = mainPlayer->getCollisionBox().y;
        gameInventory->setupDefaultGunForPlayer(xPosPlayer, yPosPlayer);
        
        
        //initialize sub map
        subMap.initParametersFromLabyrinth(thisLabyrinth);
        subMap.setPosition(0,0);
        //thisLabyrinth.setDebugBool(true);
        
        //Setup camera for collision system
        collisionHandler->setCameraForCollisionSystem(&camera);
        
        //setup camera for audio renderer
        gAudioRenderer.SetPointerToCamera(&camera);
        
        //setup fps timer
        std::int16_t frame_rate = 60;
        frameRateCap.setFrameRate(frame_rate);
        
         //set camera for labyrinth 
        thisLabyrinth.setCamera(&camera);
        
        //add enemy collision objects to collision handler
        for(size_t i = 0; i < thisLabyrinth.GetEnemiesInLabyrinthVector()->size(); i++)
        {
			if(collisionHandler->repeatPlay)
			{
				std::cout << " ";
			}
			Enemy* thisEnemy = thisLabyrinth.GetEnemiesInLabyrinthVector()->at(i);
			collisionHandler->addObjectToCollisionSystem(thisEnemy->getCollisionObjectPtr());
			collisionHandler->addObjectToCollisionSystem(thisEnemy->GetLineOfSightCollisionObject());
		}
		
		//add hole tile collision objects to collision handler
		for(size_t i=0; i < thisLabyrinth.GetCollisionObjectsOfHoleTiles()->size(); ++i)
		{
		    collisionHandler->addObjectToCollisionSystem( &thisLabyrinth.GetCollisionObjectsOfHoleTiles()->at(i) );
		}
        
        return true;
    }
    
    return false;
}




void GameOver()
{
    //restart the timer
    stepTimer.start();

     //clear screen
    SDL_RenderClear(gRenderer);
    
    ALint musicState;

    while( stepTimer.getTicks() <= 2000  )
    {
         //play sound from winMusicSource
        alGetSourcei(gameOverMusicSource, AL_SOURCE_STATE, &musicState);
        
        if (musicState == AL_STOPPED || musicState == AL_INITIAL){ alSourcePlay(gameOverMusicSource);}
        //else{alSourceStop(gameOverMusicSource);}

        //render game over screen
        gameOverTexture.render(0,0,gRenderer);

        //update screen
        SDL_RenderPresent(gRenderer);

    }
    
    //pause the state stack operations 
    pauseStack = true;
    
    //empty stack
    while(!state_stack.empty()){state_stack.pop(); }
	
	//go to game intro
	state_stack.push(gTitleStateStructure); //push game title to stack
	
	
	
	pauseStack = false;
	
	collisionHandler->repeatPlay = true;

}

void GameWon()
{
    //restart the timer
    stepTimer.start();

     //clear screen
    SDL_RenderClear(gRenderer);
    
    ALint musicState;

    while( musicState != AL_STOPPED )
    {
         //play sound from winMusicSource
        alGetSourcei(winMusicSource, AL_SOURCE_STATE, &musicState);
        
        if (musicState == AL_STOPPED || musicState == AL_INITIAL){ alSourcePlay(winMusicSource);}

        //render game win screen
        gameWonTexture.render(0,0,gRenderer);

        //update screen
        SDL_RenderPresent(gRenderer);

    }
}

void Transition()
{
     //clear screen
    SDL_RenderClear(gRenderer);
    //stop the timer
    stepTimer.stop();
    //update screen
    SDL_RenderPresent(gRenderer);
}

void runMenuState()
{ //push menu state into stack
    MenuState();
}

void MenuState()
{
    gPauseMenu->pushState(Menu::MenuState::DEFAULT_MENU);

    bool quit = false;

    //while game menu is not in exit state
    while(!quit)
    {
        //Handle events
        run_event_handler();
        //while event queue is not empty
        while( !isEventQueueEmpty() )
        {
            gPauseMenu->handle_events(getEventInstanceFront());
            //pop element in front of event queue
            popEventInstanceFromFront();
        }
        
        gPauseMenu->logic();

        SDL_RenderClear(gRenderer);
        gPauseMenu->render(gRenderer);
        SDL_RenderPresent(gRenderer);

        gPauseMenu->sound(&gAudioRenderer);

        if(gPauseMenu->getCurrentMenuState() == Menu::MenuState::NOT_RUNNING
                || gPauseMenu->getCurrentMenuState() == Menu::MenuState::QUIT)
        {
            quit = true;
        }
    }

   if(gPauseMenu->getCurrentMenuState() == Menu::MenuState::NOT_RUNNING)
    {
        //start timer again
        stepTimer.start();
        //set basegamestate to running state
        baseGameState->setState(GameState::State::RUNNING);
    }
   else if(gPauseMenu->getCurrentMenuState() == Menu::MenuState::QUIT)
    {
        //quit game
        quitGame = true;
        baseGameState->setState(GameState::State::EXIT);
    }
}

void TitleState()
{
    baseGameState = gTitle.get();
    
    baseGameState->setState(GameState::State::RUNNING);
    
    bool quit = false;
    
    while(!quit)
    {
        //call game loop function
        GameLoop();

        if(baseGameState->getState() == GameState::State::EXIT 
            || baseGameState->getState() == GameState::State::NEXT)
        {
            quit = true;
        }
    }
    
    if(baseGameState->getState() == GameState::State::EXIT )
    {
        baseGameState = nullptr;
        quitGame = true;
    }

    else if(baseGameState->getState() == GameState::State::NEXT)
    {
        if( gTitle.get()->getTitleMenuOptionSelect() 
                == TitleMenu::TitleOptions::NODE_GEN_DEBUG)
        {
            state_stack.push(NodeGenStateStructure);
        }
        else
        {
            //go to next dungeon
            baseGameState = nullptr;
            //push load game resources state into game
            state_stack.push(LoadGameResourcesStateStructure); 
        }
    }

}

void LoadGameResourcesState()
{
    //load media
    if(!loadMedia())
    {
        printf("Failed to load media! \n");
        quitGame = true;
    }
    else
    {
        //if media successfully loaded
        //push dungeon 1 state into stack
        state_stack.push(gDungeon1StateStructure);
    }
}


//function to initialize main character
bool initMainChar()
{
    bool success = true;
    
    //make hero
    std::unique_ptr <Dot> ptrToMC(new Player(10,30,15,20) );

    if(!ptrToMC)
    {
        printf("Failed to initialize Hero. \n");
        return false;
    }
    else
    {
        
         //define dot object that will be in the states, allocate memory for it in heap
         //set speed to 
        float speed = 80 * 3;
        ptrToMC->setSpeed(speed);

        mainDotPointer = std::move(ptrToMC);
        //set pointer to main player
        mainPlayer = dynamic_cast<Player*>(mainDotPointer.get());
    }
    
    return success;
}

/** Setup **/

bool init()
{
	//Initialization flag
	bool success = true;


	if(!initSDL2())
    {
        printf("Failed to initialize SDL2! \n");
        success = false;
    }
    else
    {
        if(!initExtLibs())
        {
            printf("failed to initialize external libraries! \n");
            success = false;
        }
        else
        {
            if(!initPauseMenu())
            {
                success = false;
                printf("Failed to initialize pause menu! \n");
            }
            else if(!initTitleState())
            {
                success = false;
                printf("Failed to initialize title state! \n");
            }
            else if(!initMainChar())
            {
                success = false;
                printf("Failed to initialize main character! \n");
            }
            //Open the font
			std::string fontFilePath = DATADIR_STR + std::string("/Fonts/daemones.ttf");
            gFont = TTF_OpenFont( fontFilePath.c_str(), 18 );

            if( gFont == nullptr )
            {
                printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
                success = false;
            }
        }
    }
	
	return success;
}

bool initSDL2()
{
    bool success = true;
    
    //Initialize SDL video for images and audio for music
	if( SDL_Init( SDL_INIT_VIDEO  | SDL_INIT_AUDIO) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Enable VSync
		//if( !SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1" ) )
		//{
		//	printf( "Warning: VSync not enabled!" );
		//}

		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

        //Seed random for timer
		srand( SDL_GetTicks() );

		//Create window
		gWindow = SDL_CreateWindow( "Door To Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == nullptr )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			
			if(use_software_fallback)
			{
				gRenderer = SDL_CreateRenderer( gWindow, num_render_driver, SDL_RENDERER_SOFTWARE);
				std::cout << "\nRenderer created with software fallback! \n";
			}
			else
			{
				gRenderer = SDL_CreateRenderer( gWindow, num_render_driver, SDL_RENDERER_ACCELERATED);
				std::cout << "\nRenderer created with hardware acceleration enabled! \n";
			}
			
			if( gRenderer == nullptr )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0);
            }
        }
    }
    
    return success;
}

bool initExtLibs()
{
    bool success = true;
    
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        success = false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }

    //initialize SDL_mixer
    if(Mix_OpenAudio(48000, AUDIO_S16SYS, 1, 1024) == -1) //args: sound frequency,default format, 2 channels,sample size
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    //if sdl_mixer initialized successfully
    else{if(!initOpenALSoft() ){ success = false;}}
    
    return success;
}

//function to initializer openal soft
bool initOpenALSoft()
{
    bool success = true;
    
    //use default audio device
    gAudioDevice = alcOpenDevice(NULL);
    if(gAudioDevice == nullptr){return false;}
    
    //create context
    alContext = alcCreateContext(gAudioDevice, NULL);
    if(alContext == nullptr){return false;}
	
	alcMakeContextCurrent(alContext);
    
    //define listener, what is hearing the sound
	//For 2D sound, we tell openAL soft that listener
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);//is at the origin
	alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);//is not moving in 3d space
	
	ALenum test_error_flag = alGetError();
	if(test_error_flag != AL_NO_ERROR)
	{
		std::cout << "\nError found in setting listener properties" << ": " << alGetString(test_error_flag) << "\n";
		return false;
	}
	
	//initialize audio renderer
    if(!gAudioRenderer.InitSourcePool())
    {
		std::cout << "Could not initialze source pool of audio renderer!\n";
		cleanup_openALSoft();
		return false;
	}
    
    return success;
}

void cleanup_openALSoft()
{
    alcDestroyContext(alContext);	//delete context
	alcCloseDevice(gAudioDevice);	//close device
}

bool initPauseMenu()
{
    bool success = true;
    
    //initialize pause menu
    std::unique_ptr <PauseMenu> ptrToMenu(new PauseMenu());
    if(!ptrToMenu){success = false;}
    else
    {
        gPauseMenu = std::move(ptrToMenu);
        gMenuStateStructure.StatePointer = MenuState;
    }
    
    return success;
}

bool initTitleState()
{
    bool success = true;
    
    //initialize pause menu
    std::unique_ptr <Title> ptrToTitle(new Title());
    if(!ptrToTitle){success = false;}
    else
    {
        gTitle = std::move(ptrToTitle);
        gTitleStateStructure.StatePointer = TitleState;
        
         //load title media
        if(!gTitle->loadMedia(gRenderer))
        {
            printf("Failed to load title media! \n");
            success = false;
        }
    }
    
    return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;
    
	//load game over resources
	if(!loadMedia_gameover())
    {
        printf("Failed to load game over media! \n");
        success = false;
    }
    
    //load game win resources
    if(!loadMedia_gamewin())
    {
        printf("Failed to load game win media! \n");
        success = false;
    }
    //load pause menu media
    if(!gPauseMenu->loadMedia(gRenderer))
    {
        printf("Failed to load menu media! \n");
        success = false;
    }
   
    //load dungeon door key media
    if(!loadDungeon_Door_Key_Media(gRenderer) )
    {
        printf("Failed to load all dungeon media! \n");
        success = false;
    }
    //load health bar media
    if(!loadMedia_HealthBar(&healthBarTexture,gRenderer))
    {
        printf("Failed to load health bar media! \n");
        success = false;
    }
    else
    {
        playerHealthBar.setPointerToHealthTexture(&healthBarTexture);
        //initialize health bar
        //container dimensions
        std::int16_t contX = 31; std::int16_t contY = 16; 
        std::int16_t contW = 131; std::int16_t contH = 52;
        playerHealthBar.setContainerRectClip(contX,contY,contW,contH);
        //health dimensions
        std::int16_t healthX = 37; std::int16_t healthY = 94; 
        std::int16_t healthW = 119;  std::int16_t healthH = 40;
        playerHealthBar.setHealthRectClip(healthX,healthY,healthW,healthH);
    }
    //load main player media
    if(!setup_loadPlayerMedia(mainPlayer,gRenderer) )
    {
		printf("Failed to load player media! \n");
		success = false;
	}
	//alGetError();
    //load enemy media
    if(!loadEnemyMedia(gRenderer))
    {
        printf("Failed to load enemy media! \n");
        success = false;
    }
    
    //load weapons media
    if(!loadWeaponsMedia(gRenderer))
    {
        printf("Failed to load weapons media! \n");
        success = false;
    }
    
	return success;
}


bool loadMedia_gameover()
{
    bool success = true;
    
    std::string gameOverTexFilePath = DATADIR_STR + std::string("/Graphics/game_over_screen.png");
    if(!gameOverTexture.loadFromFile( gameOverTexFilePath.c_str(),gRenderer) )
	{
	    printf("Failed to load game over texture! %s\n", SDL_GetError() );
	    success = false;
	}

    std::string path = ("/Sound/Evil_Laugh_8-Bit.wav");
    if(!LoadBuffer(&gameOverMusicBuffer,path))
    {
        std::cout << "Failed to load evil laugh 8 bit theme! \n";
        success = false;
    }
    else
    {
        //setup source of dungeon music
        alGenSources(1, &gameOverMusicSource); //allocate source 
		
        alSource3f(gameOverMusicSource, AL_POSITION, 0.0f, 0.0f, 0.0f); //source position is at the origin
        alSource3f(gameOverMusicSource, AL_VELOCITY, 0.0f, 0.0f, 0.0f); //source is not moving
        alSourcei(gameOverMusicSource, AL_LOOPING, AL_FALSE); //loop the audio that source is playing
        
        //setup buffer of dungeon music
        
        //attach buffer to source that is playing sound
        alSourcei(gameOverMusicSource, AL_BUFFER, gameOverMusicBuffer);
    }

    return success;
}

bool loadMedia_gamewin()
{
    bool success = true;
    
    std::string gameWonTexFilePath = DATADIR_STR + std::string("/Graphics/congratulations-screen.png");
    if(!gameWonTexture.loadFromFile(gameWonTexFilePath.c_str(),gRenderer) )
    {
        printf("Failed to load game win screen! %s\n",SDL_GetError() );
        success = false;
    
    }
    
    std::string path = ("/Sound/victory-theme-mono.ogg");
    if(!LoadBuffer(&winMusicBuffer,path))
    {
		std::cout << "Failed to load victory theme! \n";
		return false;
	}
    else
    {
        //setup source of dungeon music
        alGenSources(1, &winMusicSource); //allocate source 
		
		//attach buffer to source that is playing sound
        alSourcei(winMusicSource, AL_BUFFER, winMusicBuffer);
        
        alSource3f(winMusicSource, AL_POSITION, 0.0f, 0.0f, 0.0f); //source position is at the origin
        alSource3f(winMusicSource, AL_VELOCITY, 0.0f, 0.0f, 0.0f); //source is not moving
        alSourcei(winMusicSource, AL_LOOPING, AL_FALSE); //loop the audio that source is playing
        
    }
    return success;
}


void close()
{
    
    freeEnemyMedia();
    freeWeaponsMedia();
    
    freeDungeon_Door_Key_Media();
    //free health bar texture
    freeMedia_HealthBar(&healthBarTexture);
    
    //free source
    alDeleteSources(1, &gameOverMusicSource); // delete source
    alDeleteSources(1, &winMusicSource);
    //free buffer
	alDeleteBuffers(1, &gameOverMusicBuffer); //delete buffer
    alDeleteBuffers(1, &winMusicBuffer);
    
    //free game over texture
    gameOverTexture.free();
    
    gameWonTexture.free();
    
    //free global font
    TTF_CloseFont( gFont );
	gFont = NULL;
    
    //destroy audio renderer
    gAudioRenderer.FreeSourcePool();
    
    //close OpenAL Soft
    cleanup_openALSoft();

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int checkForRendererDriverInput(int& argc, char* argv[])
{
	//return 0 if want program to continue
	//return -1 if want program to not continue
	int status = 0;
	
	if(argc == 1)
	{
		return 0;
	}
	else
	{
		std::vector <std::string> sources;
		std::string destination;
		for (int i = 1; i < argc; ++i) 
		{
			if(std::string(argv[i]) == "--help")
			{
				std::cout << "\n Usage: \n--renderer-software-fallback Forces program to use software fallback instead of hardware acceleration. \n--renderer-driver NUM Choses renderer driver(NUM) to use. \n--show-renderer-drivers-info Shows info on drivers especially NUM place of driver. \n--show-video-drivers-info Shows info on video cards to use. \n";
				return -1;
			}
			
			if (std::string(argv[i]) == "--renderer-driver") 
			{
				if (i + 1 < argc) 
				{ 
					// Make sure we aren't at the end of argv!
					num_render_driver = std::stoi( std::string(argv[i+1]) ); // Increment 'i' so we don't get the argument as the next argv[i].
					std::cout << "num_renderer_driver:" << num_render_driver << std::endl;
					
					SDL_RendererInfo drinfo;
					SDL_GetRenderDriverInfo (num_render_driver, &drinfo);
					std::cout << "\n\n" << drinfo.name << " is being used." << std::endl;
					return 0;
				} 
				else 
				{ 
					// Uh-oh, there was no argument to the destination option.
					std::cerr << "--renderer-driver option requires one argument." << std::endl;
					return -1;
				}  
			} 
			
			if(std::string(argv[i]) == "--show-renderer-drivers-info")
			{
				
				int numdrivers = SDL_GetNumRenderDrivers ();
				
				std::cout << "Render driver count: " << numdrivers << std::endl;
				
				for (int i=0; i<numdrivers; i++) 
				{
					SDL_RendererInfo drinfo;
					SDL_GetRenderDriverInfo (i, &drinfo);
					std::cout << "Renderer Driver name ("<<i<<"): " << drinfo.name << std::endl;
					
					//check if renderer driver is a software fallback, and create a renderer that uses software if so
					if (drinfo.flags & SDL_RENDERER_SOFTWARE)
					{
						std::cout << " the renderer is a software fallback" << std::endl;
					} 
					//check if renderer driver supports hardware acceleration, create a renderer that uses hardware acceleration if so
					if (drinfo.flags & SDL_RENDERER_ACCELERATED)
					{
						std::cout << " the renderer uses hardware acceleration" << std::endl;
					} 
					if (drinfo.flags & SDL_RENDERER_PRESENTVSYNC)
					{
						std::cout << " present is synchronized with the refresh rate" << std::endl;
					} 
					if (drinfo.flags & SDL_RENDERER_TARGETTEXTURE)
					{
						std::cout << " the renderer supports rendering to texture" << std::endl;
					}
				}
				
				return -1;
				 
			}
			
			if(std::string(argv[i]) == "--show-video-drivers-info")
			{
				std::cout << "Render driver count: " << SDL_GetNumVideoDrivers() << std::endl;
				
				//display all video drivers available
				for(int i=0; i < SDL_GetNumVideoDrivers(); ++i)
				{
					//display video driver
					std::cout << "Video Driver" << "(" << i << "):" << SDL_GetVideoDriver(i) << std::endl;
				}
				
				return -1;
			}
			
			if(std::string(argv[i]) == "--renderer-software-fallback")
			{
				std::cout << "\nSoftware fallback forced! \n";
				use_software_fallback = true;
				return 0;
			}
			
		}
	}
	
	
	return status;
}
