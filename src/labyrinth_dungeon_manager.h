#ifndef LABYRINTH_DUNGEON_MANAGER_H
#define LABYRINTH_DUNGEON_MANAGER_H

#include <memory> //for unique_ptr
#include "globalvariables.h"
#include "Dungeon.h"
#include "labyrinth.h"

class LabyrinthDungeonManager : public GameState
{
public:
	LabyrinthDungeonManager();
	~LabyrinthDungeonManager();
	
	void SetPointerToPlayerManager(PlayerManager* pm);
	
	//labyrinth specific functions
	bool setupLabyrinth(PlayerManager* mainPlayerManager, GameInventory* gameInventory,
											DungeonXMLRegistry* dungeon_xml_reg, RNGType& rngSeed,
											LTimer* stepTimer, Dot* mainDotPointer,
											std::int16_t SCREEN_WIDTH , std::int16_t SCREEN_HEIGHT,
											LTexture& dungeonTilesTexture, ALuint& dungeonMusicSource, ALuint& dungeonMusicBuffer,
											LTexture& keyTexture, ALuint& keySource,ALuint& keyBuffer,
											LTexture& doorTexture, ALuint& doorSource, ALuint& doorBufferOpen, ALuint& doorBufferFail,
											std::vector <SDL_Rect> &doorClips);
	Labyrinth* GetPointerToLabyrinth();
	
	bool GetLabyrinthCreatedBool();

	
	//dungeon specific functions
	
	//Game loop functions
	virtual void setState(GameState::State thisState);
    virtual GameState::State getState();
        
	virtual void handle_events(Event& thisEvent);
	virtual void handle_events_RNG(RNGType& rngSeed);
	virtual void logic();
	virtual void sound(AudioRenderer* gAudioRenderer);
	virtual void render(SDL_Renderer* gRenderer);
	
	virtual void render(DrawingManager* gDrawManager);
	
private:
	
	PlayerManager* m_player_manager_ptr;
	
	std::unique_ptr <Labyrinth> m_labyrinth;
	bool labyrinthCreated;
};

#endif
