#ifndef LABYRINTH_DUNGEON_MANAGER_H
#define LABYRINTH_DUNGEON_MANAGER_H

#include "Dungeon.h"
#include "labyrinth.h"

class LabyrinthDungeonManager : public GameState
{
public:
	LabyrinthDungeonManager();
	~LabyrinthDungeonManager();
	
	//Game loop functions
	
	virtual void handle_events(Event& thisEvent) = 0;
	virtual void handle_events_RNG(RNGType& rngSeed) = 0;
	virtual void logic() = 0;
	virtual void sound(AudioRenderer* gAudioRenderer) = 0;
	virtual void render(SDL_Renderer* gRenderer) = 0;
	
	virtual void render(DrawingManager* gDrawManager) = 0;
	
private:

	PlayerManager* m_player_manager_ptr;
	
};

#endif
