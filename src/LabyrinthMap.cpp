#include "LabyrinthMap.h"

LabyrinthMap::LabyrinthMap()
{
    
}

LabyrinthMap::~LabyrinthMap()
{
    
}

bool checkCollision(SDL_Rect& a, SDL_Rect& b);
    
//function to pass dungeon tiles from LabyrinthNode objects to labyrinthTilesVector 
void LabyrinthMap::loadMapFromLabyrinthNodes(std::vector <LabyrinthNode> &labyrinthNodes)
{
    LabyrinthMap::loadTilesFromLabyrinthNodes(labyrinthNodes);
    LabyrinthMap::loadDoorsFromLabyrinthNodes(labyrinthNodes);
}

void LabyrinthMap::loadTilesFromLabyrinthNodes(std::vector <LabyrinthNode> &labyrinthNodes)
{
    //for every dungeon node element
    for(size_t iNode = 0; iNode < labyrinthNodes.size(); iNode++ )
    {
        
        if(iNode != 0)
        {
            //append at end dungeon tile pointer vector to of labyrinth node to map
            labyrinthTilesVector.insert(labyrinthTilesVector.end(),
                                        labyrinthNodes[iNode].dungeonTileSet.begin(),
                                        labyrinthNodes[iNode].dungeonTileSet.end());
            
            
        }
        //append at beginning
        else
        {
            labyrinthTilesVector.insert(labyrinthTilesVector.begin(),
                                        labyrinthNodes[iNode].dungeonTileSet.begin(),
                                        labyrinthNodes[iNode].dungeonTileSet.end());
                                        
        }
              
    }
}

void LabyrinthMap::loadDoorsFromLabyrinthNodes(std::vector <LabyrinthNode> &labyrinthNodes)
{
    //for every dungeon node element
    for(size_t iNode = 0; iNode < labyrinthNodes.size(); ++iNode )
    {
        if(iNode != 0)
        {
	  //if(labyrinthDoorsVector.size() != 0)
	  //{
                //append at end dungeon tile pointer vector to of dungeon node to map
                labyrinthDoorsVector.insert(labyrinthDoorsVector.end(),
                                        labyrinthNodes[iNode].dungeonDoors.begin(),
                                        labyrinthNodes[iNode].dungeonDoors.end());
		//}
            
            
        }
        //append at beginning
        else
        {
	  //if(labyrinthDoorsVector.size() != 0)
	  //{
                labyrinthDoorsVector.insert(labyrinthDoorsVector.begin(),
                                        labyrinthNodes[iNode].dungeonDoors.begin(),
                                        labyrinthNodes[iNode].dungeonDoors.end());
		//}
        }
                                        
        
    }
    
    
}

void LabyrinthMap::setClipsForTiles()
{
    //Set tile clips
    for(size_t i = 0; i < labyrinthTilesVector.size(); ++i)
    {
        labyrinthTilesVector[i]->setTileClips();
    }
    
}

//function to free resources from tiles
void LabyrinthMap::freeTiles()
{
    for(size_t i = 0; i < labyrinthTilesVector.size(); i++ )
    {
        delete labyrinthTilesVector[i];
        labyrinthTilesVector[i] = nullptr;
    }
}

void LabyrinthMap::setLabyrinthCameraForDot(Dot* mainDotPointer, 
                                        std::int16_t& screenWidth, std::int16_t& screenHeight)
{
    std::int16_t LEVEL_WIDTH = screenWidth;
    std::int16_t LEVEL_HEIGHT = screenHeight;
    //set place for dot to move in
    mainDotPointer->setPlace(screenWidth,screenHeight);

}

void LabyrinthMap::moveMainDot(Dot* mainDotPointer,float &timeStep,SDL_Rect* thisCamera)
{
    //set camera over dot
    //Center the camera over the dot
	thisCamera->x = ( (int)mainDotPointer->getPosX() + mainDotPointer->getWidth() / 2  ) - thisCamera->w / 2;
	thisCamera->y = ( (int)mainDotPointer->getPosY() + mainDotPointer->getHeight() / 2  ) - thisCamera->h / 2;
	
	//Keep the camera in bounds
	if( thisCamera->x < 0 )
	{
		thisCamera->x = 0;
	}
	if( thisCamera->y < 0 )
	{
		thisCamera->y = 0;
	}

//    mainDotPointer->setCamera(*thisCamera);

    //move dot independent of frames, but rather dependent on time. includes collision detection
    mainDotPointer->moveOnTiles_TileType(timeStep, labyrinthTilesVector );

}


void LabyrinthMap::renderTiles(SDL_Renderer* gRenderer,LTexture* tileTextureMap)
{
    for(size_t i = 0; i < labyrinthTilesVector.size(); i++)
    {
        labyrinthTilesVector[i]->render(tileTextureMap,*lCamera,gRenderer);
    }
}

void LabyrinthMap::renderTiles(PlayerManager* playerManager,DrawingManager* gDrawManager,LTexture* tileTextureMap)
{
	int num_players = gDrawManager->GetNumberOfPlayers();
	
	bool p1_in_dungeon,p2_in_dungeon,p3_in_dungeon,p4_in_dungeon;
    playerManager->GetBoolsForPlayersInDungeon(&p1_in_dungeon,&p2_in_dungeon,&p3_in_dungeon,&p4_in_dungeon);
	
    for(size_t i = 0; i < labyrinthTilesVector.size(); i++)
    {
		if(!p1_in_dungeon)
		{
			gDrawManager->SetToRenderViewPortPlayer1();
		
			labyrinthTilesVector[i]->render(tileTextureMap,
										*gDrawManager->GetPointerToCameraOne(),
										gDrawManager->GetPointerToRenderer());
		}
		
		
		if(gDrawManager->GetMultiplePlayersBool())
		{
			if(num_players > 1 && !p2_in_dungeon)
			{
				gDrawManager->SetToRenderViewPortPlayer2();
			
				labyrinthTilesVector[i]->render(tileTextureMap,
												*gDrawManager->GetPointerToCameraTwo(),
												gDrawManager->GetPointerToRenderer());
			}
			
			if(num_players > 2 && !p3_in_dungeon)
			{
				gDrawManager->SetToRenderViewPortPlayer3();
			
				labyrinthTilesVector[i]->render(tileTextureMap,
												*gDrawManager->GetPointerToCameraThree(),
												gDrawManager->GetPointerToRenderer());
			}
			
			if(num_players > 3 && !p4_in_dungeon)
			{
				gDrawManager->SetToRenderViewPortPlayer4();
			
				labyrinthTilesVector[i]->render(tileTextureMap,
												*gDrawManager->GetPointerToCameraFour(),
												gDrawManager->GetPointerToRenderer());
			}
			
		}
										
    }
}

void LabyrinthMap::renderDotInLabyrinthMap(SDL_Renderer* gRenderer, Dot* mainDotPointer, SDL_Rect* thisCamera)
{
    //render dot
    mainDotPointer->render(*thisCamera,gRenderer);
}

void setupNewDoorObject(Door* thisDoor,
                            LTexture* doorTexture,
                            ALuint* source,
                            ALuint* doorBufferOpen, 
                            ALuint* doorBufferFail );


bool checkDotCollidesWithDoor(Door* thisDoor, Dot* mainDot);

void LabyrinthMap::doorToDot_Logic(Dot* mainDotPointer,float& timeStep, SDL_Rect* thisCamera)
{
     if( labyrinthDoorsVector.size() == 1)
    {
        
        checkDotCollidesWithDoor(labyrinthDoorsVector[0],mainDotPointer);
        if(labyrinthDoorsVector[0]->getDoorCollidedState() == Door::DoorCollided::DOT_TO_DOOR1
            || labyrinthDoorsVector[0]->getDoorCollidedState() == Door::DoorCollided::DOT_TO_DOOR2)
        {
            //move dot back
            mainDotPointer->moveBack(timeStep);
        }
    }
     else if( labyrinthDoorsVector.size() > 1 )
    {
        for(size_t i=0; i < labyrinthDoorsVector.size(); ++i)
        {
            //if either of doors are within camera
            if( checkCollision(*thisCamera,labyrinthDoorsVector[i]->getCollisionBoxDoor1())
                || checkCollision(*thisCamera,labyrinthDoorsVector[i]->getCollisionBoxDoor2()))
            {
                //if dot collides with door
                if( checkDotCollidesWithDoor(labyrinthDoorsVector[i],mainDotPointer) )
                {
                    //check if door is open
                     labyrinthDoorsVector[i]->openDoorLogic();
                        
                    //if door is open and oot collides with it
                    if(labyrinthDoorsVector[i]->getDoorCollidedState() == Door::DoorCollided::DOT_TO_DOOR1
                        && labyrinthDoorsVector[i]->getDoorState() == Door::State::DOOR_OPEN)
                    {
                        LabyrinthMap::transferDotThroughDoor(mainDotPointer,labyrinthDoorsVector[i],true);
                        labyrinthDoorsVector[i]->resetDoorsToClose();
                    }
                    else if(labyrinthDoorsVector[i]->getDoorCollidedState() == Door::DoorCollided::DOT_TO_DOOR2
                            && labyrinthDoorsVector[i]->getDoorState() == Door::State::DOOR_OPEN)
                    {
                        LabyrinthMap::transferDotThroughDoor(mainDotPointer,labyrinthDoorsVector[i],false);
                        labyrinthDoorsVector[i]->resetDoorsToClose();
                    }
                    //if door isn't open
                    else if(labyrinthDoorsVector[i]->getDoorState() == Door::State::DOOR_CLOSED)
                    {
                        //if dot is colliding with door
                        if(checkCollision(labyrinthDoorsVector[i]->getCollisionBoxDoor1(), 
                                            mainDotPointer->getCollisionBox())
                            )
                        {
                            mainDotPointer->moveBack(timeStep);
                        }
                        else if( checkCollision(labyrinthDoorsVector[i]->getCollisionBoxDoor2(), 
                                            mainDotPointer->getCollisionBox()) )
                        {
                            mainDotPointer->moveBack(timeStep);
                        }
                    }
                }
            }
        }
    }
}

void LabyrinthMap::renderDoors(SDL_Renderer* gRenderer)
{
    for(size_t i = 0; i < labyrinthDoorsVector.size(); ++i)
    {
        if( checkCollision(*lCamera,labyrinthDoorsVector[i]->getCollisionBoxDoor1())
                || checkCollision(*lCamera,labyrinthDoorsVector[i]->getCollisionBoxDoor2()))
        {
            labyrinthDoorsVector[i]->render(*lCamera,gRenderer);
        }
    }
}


void LabyrinthMap::renderDoors(PlayerManager* playerManager,DrawingManager* gDrawManager)
{
	int num_players = gDrawManager->GetNumberOfPlayers();
	
	bool p1_in_dungeon,p2_in_dungeon,p3_in_dungeon,p4_in_dungeon;
    playerManager->GetBoolsForPlayersInDungeon(&p1_in_dungeon,&p2_in_dungeon,&p3_in_dungeon,&p4_in_dungeon);
	
    for(size_t i = 0; i < labyrinthDoorsVector.size(); ++i)
    {
        if( checkCollision(*gDrawManager->GetPointerToCameraOne(),labyrinthDoorsVector[i]->getCollisionBoxDoor1())
                || checkCollision(*gDrawManager->GetPointerToCameraOne(),labyrinthDoorsVector[i]->getCollisionBoxDoor2()))
        {
			if(!p1_in_dungeon)
			{
				gDrawManager->SetToRenderViewPortPlayer1();
				labyrinthDoorsVector[i]->render(*gDrawManager->GetPointerToCameraOne(),gDrawManager->GetPointerToRenderer());
			}
        }
        
        if(gDrawManager->GetMultiplePlayersBool())
        {
			
			if(num_players > 1 && !p2_in_dungeon)
			{
				if( checkCollision(*gDrawManager->GetPointerToCameraTwo(),labyrinthDoorsVector[i]->getCollisionBoxDoor1())
					|| checkCollision(*gDrawManager->GetPointerToCameraTwo(),labyrinthDoorsVector[i]->getCollisionBoxDoor2()))
				{
					gDrawManager->SetToRenderViewPortPlayer2();
					labyrinthDoorsVector[i]->render(*gDrawManager->GetPointerToCameraTwo(),gDrawManager->GetPointerToRenderer());
				}
			}
			
			if(num_players > 2 && !p3_in_dungeon)
			{
				if( checkCollision(*gDrawManager->GetPointerToCameraThree(),labyrinthDoorsVector[i]->getCollisionBoxDoor1())
					|| checkCollision(*gDrawManager->GetPointerToCameraThree(),labyrinthDoorsVector[i]->getCollisionBoxDoor2()))
				{
					gDrawManager->SetToRenderViewPortPlayer3();
					labyrinthDoorsVector[i]->render(*gDrawManager->GetPointerToCameraThree(),gDrawManager->GetPointerToRenderer());
				}
			}
			
			if(num_players > 3 && !p4_in_dungeon)
			{
				if( checkCollision(*gDrawManager->GetPointerToCameraFour(),labyrinthDoorsVector[i]->getCollisionBoxDoor1())
					|| checkCollision(*gDrawManager->GetPointerToCameraFour(),labyrinthDoorsVector[i]->getCollisionBoxDoor2()))
				{
					gDrawManager->SetToRenderViewPortPlayer4();
					labyrinthDoorsVector[i]->render(*gDrawManager->GetPointerToCameraFour(),gDrawManager->GetPointerToRenderer());
				}
			}
			
		}
        
    }
}

void LabyrinthMap::door_handle_events(Event& thisEvent,SDL_Rect* thisCamera)
{
    //for all doors
    for(size_t i = 0; i < labyrinthDoorsVector.size(); ++i)
    {
        //if door 1 collision box is within camera
        //or door 2 collision box is withing camera
        if(checkCollision( labyrinthDoorsVector[i]->getCollisionBoxDoor1(),*thisCamera)  ||
            checkCollision( labyrinthDoorsVector[i]->getCollisionBoxDoor2(),*thisCamera) )
        {
            labyrinthDoorsVector[i]->handle_event(thisEvent);
        }
        
    }
}


void LabyrinthMap::transferDotThroughDoor(Dot* mainDotPointer, Door* thisDoor, bool One_To_Two)
{
    //make dot exit to right of door
    
    if(One_To_Two)
    {
        //change dot's position to door 2's position
        float x = thisDoor->getCollisionBoxDoor2().x + 
                    thisDoor->getCollisionBoxDoor2().w + 
                    mainDotPointer->getCollisionBox().w;
                    
        float y = thisDoor->getCollisionBoxDoor2().y +
                  mainDotPointer->getCollisionBox().h;
        //set x and y position of dot
        mainDotPointer->setPosX(x);
        mainDotPointer->setPosY(y);
    }
    else
    {
        //change dot's position to door 1's position
        float x = thisDoor->getCollisionBoxDoor1().x +
                    thisDoor->getCollisionBoxDoor1().w +
                    + mainDotPointer->getCollisionBox().w;
                    
        float y = thisDoor->getCollisionBoxDoor1().y + 
                    mainDotPointer->getCollisionBox().h;
        //set x and y position of dot
        mainDotPointer->setPosX(x);
        mainDotPointer->setPosY(y);
    }
}

void LabyrinthMap::randomlyPlaceLabyrinthDoors(RNGType& rngSeed)
{ 
    if(labyrinthDoorsVector.size() > 0)
    {
      std::cout << "Randomly placing doors! \n";
        //last element of dungeon doors vector
        size_t end = labyrinthDoorsVector.size() - 1;
        size_t thisElement = 0;
        size_t nextElement = 0;
        

        
        //initialize vector of iterators
        std::vector <size_t> dungeon_door_iterators_random(labyrinthDoorsVector.size());
        std::iota (std::begin(dungeon_door_iterators_random), 
                    std::end(dungeon_door_iterators_random), 
                    0); // fill from 0 to size of dungeon doors vector
        
        //randomly sort iterators
        //setup rng
        std::srand ( unsigned ( std::time(0) ) );
        // using built-in random generator, shuffle the elements
        std::random_shuffle ( dungeon_door_iterators_random.begin(), 
                                    dungeon_door_iterators_random.end() );
                                    
        //make vector of door pointers
        //with size of dungeon doors vector
        std::vector <Door*> doorPtrVect(labyrinthDoorsVector.size(),nullptr);
        
        //initialize doorPtrVect with pointers from labyrinthDoorsVector with random iterators
        for(size_t i = 0; i < doorPtrVect.size(); i++)
        {
	  //std::cout << "Getting vector of random addresses. \n";
            doorPtrVect[i] = labyrinthDoorsVector.at( dungeon_door_iterators_random[i] );
        }
        
        //for each door element until second to last element
        for(size_t i = 0; i < end; i++)
        {
	  //std::cout << "swapping door collision boxes! \n";
            //swap to next elements door 2 collision box
            thisElement = i;
            nextElement = i + 1;
           
            //make next dungeon door's door2 be this dungeon door's 2
            std::int16_t d2x = doorPtrVect.at(nextElement)->getCollisionBoxDoor2().x;
            std::int16_t d2y = doorPtrVect.at(nextElement)->getCollisionBoxDoor2().y;
            doorPtrVect.at(thisElement)->placeDoor2(d2x,d2y);
            
            //make this dungeon door's door2 be next dungeon door's 2
            std::int16_t d1x = doorPtrVect.at(thisElement)->getCollisionBoxDoor2().x;
            std::int16_t d1y = doorPtrVect.at(thisElement)->getCollisionBoxDoor2().y;
            doorPtrVect.at(nextElement)->placeDoor2(d1x,d1y);

	    //std::cout << "Door placed! \n" << "x1: " << d1x << " y1: " << //d1y << " x2: " << d2x << " y2: " << d2y << std::endl;
        }
    }
}

void LabyrinthMap::freeDoorsAndKeys()
{
    if(labyrinthDoorsVector.size() > 0)
    {
        for(size_t i = 0; i < labyrinthDoorsVector.size(); ++i)
        {
            delete labyrinthDoorsVector[i];
        }
    }
    
    if(labyrinthKeysVector.size() > 0)
    {
        for(size_t i = 0; i < labyrinthKeysVector.size(); ++i)
        {
            delete labyrinthKeysVector[i];
        }
    }
}

void LabyrinthMap::play_door_sounds()
{
    //for all doors
    for(size_t i = 0; i < labyrinthDoorsVector.size(); ++i)
    {
        labyrinthDoorsVector[i]->playSounds();
    }
}
