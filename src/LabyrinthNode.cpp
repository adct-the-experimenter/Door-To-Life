#include "LabyrinthNode.h"

    
bool loadLabyrinthMedia(SDL_Renderer* gRenderer,LTexture* tileMap,
ALuint* source,ALuint* buffer)
{
    bool success = true;
    
    std::string tileFilePath = DATADIR_STR + std::string("/Graphics/tiles-alt.png");
    //load texture for member tileTextureMap
    if(!tileMap->loadFromFile(tileFilePath.c_str(), gRenderer))
    {
        std::cout << "Couldn't load tileTextureMap! \n";
        return false;
    }
    else
    {
        //if tileTextureMap loaded successfully
        
        std::string path = std::string("/Sound/Threshing-Floor-VG-Ambient-Beautiful-Haunting-Remix.ogg");
        if(!LoadBuffer(buffer,path))
        {
			printf("Failed to load dungeon music! \n");
			return false;
		}
        else
        {
            //setup source of dungeon music
            alGenSources(1, source); //allocate source 

            alSource3f(*source, AL_POSITION, 0.0f, 1.0f, 0.0f); //source position is above player(origin)
            alSource3f(*source, AL_VELOCITY, 0.0f, 0.0f, 0.0f); //source is not moving
            
            //attach buffer to source
			alSourcei(*source, AL_BUFFER, (ALint)(*buffer));
            
        }        
    }
    
    return success;
}

void freeLabyrinthMedia(LTexture* tileMap,
                        ALuint* source,ALuint* buffer)
{
    //free source
    alDeleteSources(1, source); // delete source
    
    //free buffer
	alDeleteBuffers(1, buffer); //delete buffer
    
    //free tile texture map
    tileMap->free();
}


LabyrinthNode::LabyrinthNode()
{
    //std::cout << "LabyrinthNode constructor called! \n";
    //start off with running state
    LabyrinthNode::setState(GameState::State::RUNNING);


    loopSFX = 0;

    keyDisappear = false;

}

LabyrinthNode::~LabyrinthNode()
{
    //std::cout << "LabyrinthNode destructor called! \n";

     //Set lCamera values to zero
    lCamera.x =0; lCamera.y=0; lCamera.w=0; lCamera.h=0;

    //set main sprite pointer to NULL
    mainDotPointer = nullptr;
    

    //Set the pointers' adressses to nullptr
    for(size_t i = 0; i < dungeonTileSet.size(); ++i)
    {
        dungeonTileSet[i] = nullptr;
    }
    

}

 void LabyrinthNode::setLevelDimensions(std::int16_t& levelWidth, std::int16_t& levelHeight)
 {
     LEVEL_WIDTH = levelWidth;
     LEVEL_HEIGHT = levelHeight;
 }
    
void LabyrinthNode::setPointerToMainDot(Dot* thisDot){mainDotPointer = thisDot;}
void LabyrinthNode::setPointerToTimer(LTimer* thisTimer){timer = thisTimer;}

void LabyrinthNode::setPointersToMedia(LTexture* tileMap,ALuint* source,ALuint* buffer)
{
    tileTextureMap = tileMap;
    dgmSource = source;
    dgmBuffer = buffer;
}

void LabyrinthNode::createBlankTiles(std::int16_t &start_x, std::int16_t& start_y,
                                    std::int16_t& tileWidth, std::int16_t& tileHeight,
                                    std::int16_t& numTiles)
{
    //resize dungeonTileSet vector to number of tiles
    dungeonTileSet.resize(numTiles);
    
    //Starting position of tiles for mapping
    std::int16_t dTile_X = start_x; 
    std::int16_t dTile_Y = start_y;
    
    NODE_X = start_x;
    NODE_Y = start_y;
    
    TILE_WIDTH = tileWidth;
    TILE_HEIGHT = tileHeight;
    
    numXNodeColumns = LEVEL_WIDTH / tileWidth;
    numYNodeRows = LEVEL_HEIGHT / tileHeight;
   
   //resize node look up vector
   
    //resize node look up x divisions columns
    dungeon_tile_look_up.resize(numXNodeColumns);
    
    for(size_t xCol=0; xCol < numXNodeColumns; xCol++)
    {
        dungeon_tile_look_up[xCol].resize(numYNodeRows);
    }

    size_t xCol = 0;
    size_t yRow = 0;

    for(size_t i = 0; i < dungeonTileSet.size(); ++i)
    {
        std::int16_t tileNumber = i;
        dungeonTileSet[i] = new DungeonTile(dTile_X,dTile_Y,tileWidth,tileHeight,tileNumber);

        dungeon_tile_look_up [xCol] [yRow] = dungeonTileSet[i];
        
        //move to next tile spot
        dTile_X += tileWidth;
        xCol += 1;
        
        //if dTile_x is at end of level width
        if(dTile_X > (start_x + LEVEL_WIDTH ) - tileWidth)
        {
            //move to next row
            dTile_Y += tileHeight;
            yRow += 1;
            //start from beginning
            dTile_X = start_x;
            xCol = 0;
        }
    }

}

void LabyrinthNode::randomGeneration(RNGType& rngData, boost::random::uniform_int_distribution <> zero2twelve)
{
    //initialze random number
    int randNumber = 0;

    for(size_t i = 0; i < dungeonTileSet.size(); ++i)
    {
        //generate random number
        boost::random::variate_generator <RNGType&,boost::random::uniform_int_distribution <> > Die_12(rngData, zero2twelve);
        randNumber = Die_12();

        //std::cout << "DungeonTile Number:" << dungeonTileSet[i]->getTileNumber() << " randNumber:" << randNumber << std::endl;
        dungeonTileSet[i]->setType((DungeonTile::TileType)randNumber);
    }
}

void LabyrinthNode::generateMapDrunkardWalk(RNGType& rngSeed,std::int16_t& numTiles)
{
	//number of empty nodes wanted
	int limitOfEmptyNodes = ((numTiles * 4) / 5) ; //number of empty nodes is 4/5 the number of tiles 
	int countOfEmptyNodes = 0;

	
	//pick a random point on grid

	 //set probablity for each number
	double probabilitiesNumber[] = { 0.2, 0.2, 0.2, 0.2, 0.2 }; // probabilites for 0,1,2,3,4 
	//setup rng with set probablities    
	boost::random::discrete_distribution <int> dist(probabilitiesNumber);
	boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > Die(rngSeed,dist);

    size_t xStartCol,yStartRow;
    
    //assign random number to xstartcol and ystartrow
    xStartCol = Die();
    yStartRow = Die();
    
    //bounds check
    if(xStartCol >= numXNodeColumns){xStartCol = numXNodeColumns - 1;}
    if(yStartRow >= numYNodeRows){yStartRow = numYNodeRows - 1;}
    
    //set random tile as empty
    DungeonTile* randStartTile = dungeon_tile_look_up [xStartCol] [yStartRow];
    randStartTile->setTileEmpty();
    //increment count of empty nodes
    countOfEmptyNodes++;

    //Move to another point 1 space away from current empty tile
    // Direction determined randomly
    //Repeat
    
    //integer for cardinal directions
	int direction;

	//set probability for cardinal direction
	double probabilitiesDirection[] = { 0.2, 0.2, 0.2, 0.2 }; // probabilites for N,E,W,S
	//setup rng with set probablities    
	boost::random::discrete_distribution <int> distDirection(probabilitiesDirection);
	boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > DirectionDie(rngSeed,distDirection);

    size_t xCol = xStartCol;
    size_t yRow = yStartRow;

	//do this until limit of empty nodes is reached
	while(countOfEmptyNodes < limitOfEmptyNodes)
	{	
		//choose a cardinal direction randomly
		direction = DirectionDie();
		
		// NEWS = 0123

        //Out of bounds prevention
		//if node location is on bounds
		if(xCol == 0){ direction = 1;} // if on 0, go east
		else if(xCol == numXNodeColumns - 1){direction = 2;} // if on map_width, go west
		if(yRow == 0){direction = 3;} //if on 0, go south
		else if(yRow == numYNodeRows - 1){direction = 0;} //if on map_height, go north
		
		//increment or decrement x or y based on direction
		switch(direction)
		{
			//go north		
			case 0:{ yRow -= 1; break;}
			//go east
			case 1:{xCol += 1; break;}
			//go west
			case 2:{xCol -= 1; break;}
			//go south
			case 3:{yRow += 1;break;}
		}

        if(xCol >= numXNodeColumns){xCol = numXNodeColumns - 1;}
        if(yRow >= numYNodeRows){yRow = numYNodeRows - 1;}

        //if tile is not empty
        if( !dungeon_tile_look_up [xCol] [yRow]->getTypeEmpty() )
        {
            //set it as empty
            dungeon_tile_look_up [xCol] [yRow]->setTileEmpty();
            //increment count of empty nodes
            countOfEmptyNodes += 1;
        }
	}
}

void LabyrinthNode::setTileTypesRandom(RNGType& rngSeed)
{
	 //set probablity for each number
	double probabilitiesNumber[] = { 0.2, 0.2, 0.2 }; // probabilites for 0,1,2 
	//setup rng with set probablities    
	boost::random::discrete_distribution <int> dist(probabilitiesNumber);
	boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > Die(rngSeed,dist);
    
    //variable for random number
	int randNumber = 0;

	for(size_t i=0; i < dungeonTileSet.size(); ++i)
	{
		//if tile is empty
		if( dungeonTileSet[i]->getTypeEmpty())
		{
            randNumber = Die();
            dungeonTileSet[i]->setType((DungeonTile::TileType)randNumber);
		}
		//if tile is not empty
		else{dungeonTileSet[i]->setType(DungeonTile::TileType::CENTER);}
	}
}


void LabyrinthNode::genRuleWall(RNGType& rngData, boost::random::uniform_int_distribution <> zero2twelve)
{
    //std::cout << "genRuleWall called! \n";
    int randNumber = 0;

     //tile type
    DungeonTile::TileType tileType;

    for(size_t i=0; i < dungeonTileSet.size(); ++i)
    {
        //if tile is a wall or hole
        if( dungeonTileSet[i]->getTypeWall() || 
            dungeonTileSet[i]->getType() == DungeonTile::TileType::CENTER)
        {
            //generate random number
            boost::random::variate_generator <RNGType&,boost::random::uniform_int_distribution <> > Die_12(rngData, zero2twelve);
            randNumber = Die_12();

            //turn into a floor tile if randNumber is less than 8
            if(randNumber <= 8 )
            {
                if(randNumber <= 2)
                {
                    tileType = DungeonTile::TileType::RED;
                }
                else if( randNumber >=3 && randNumber <= 5)
                {
                    tileType = DungeonTile::TileType::BLUE;
                }
                else
                {
                    tileType = DungeonTile::TileType::GREEN;
                }
            }

            //else change it to a tile center
            else
            {
                tileType = DungeonTile::TileType::CENTER;
            }

            dungeonTileSet[i]->setType(tileType);

        }
    }
}

void LabyrinthNode::genRuleLimitExits(int exitMax,int exitMin,RNGType& rngData, boost::random::uniform_int_distribution <> zero2twelve)
{
    //std::cout << "genRuleLimitExits called! \n";
    //change exit tiles into wall tiles
    //  std::cout << "Exit tile rules called in main! \n";
    int randNumber = 0;
    //initialize number of exits
    int numberExits=0;

    //exit limit
    int exitLimit = zero2twelve( rngData);

    if(exitLimit >= exitMax ){exitLimit = exitMax;}
    else if( exitLimit <= exitMin){exitLimit = exitMin;}
    //std::cout << "Exit Limit:" << exitLimit  << std::endl;

    //set which exit tiles are allowed to be exit tiles
    for(size_t i = 0; i < dungeonTileSet.size(); ++i)
    {
        //generate random numbers
        boost::random::variate_generator <RNGType&,boost::random::uniform_int_distribution <> > Die_12(rngData, zero2twelve);
        randNumber = Die_12();

        //check if exit tile
        if( dungeonTileSet[i]->getTypeExit() == true )
        {
              dungeonTileSet[i]->genRuleAllowExit(randNumber);
            if(dungeonTileSet[i]->exitAllowed == true)
            {
                    numberExits += 1;
            }
            //stp loop if
            if( numberExits == exitLimit)
            {
                break;
            }

        }

    }

    //change exit tiles not allowed to wall tiles
    for(size_t i=0; i < dungeonTileSet.size(); ++i)
    {
        dungeonTileSet[i]->genRuleChangeExitTile();
    }

}

void LabyrinthNode::countNumberOfExits()
{
    int exitTiles = 0;

    for(size_t i=0; i < dungeonTileSet.size(); ++i)
    {
        if( dungeonTileSet[i]->getTypeExit() == true )
        {
            exitTiles += 1;
        }
    }

    //assign exitTiles to numberOfExits member
    numberOfExits = exitTiles;
}

int LabyrinthNode::getNumberOfExits(){return numberOfExits;}

void LabyrinthNode::setTiles()
{
    //std::cout << "set tile clips called! \n";
    //Set tile clips
    for(size_t i = 0; i < dungeonTileSet.size(); ++i)
    {
        dungeonTileSet[i]->setTileClips();
    }
}

void LabyrinthNode::deleteTiles()
{
        //free the tiles allocated in bool setTiles
        for(size_t i=0; i < dungeonTileSet.size(); ++i)
        {
            //std::cout << " \n Delete tileSet element:" << i <<" Address:" << &tileSet[i];
            delete dungeonTileSet[i];
        }
}

/** Dot Functions**/

void LabyrinthNode::setLabyrinthNodeCameraForDot(std::int16_t& screenWidth, std::int16_t& screenHeight,
                            SDL_Rect& camera)
{
    //set place for dot to move in
    mainDotPointer->setPlace(screenWidth,screenHeight);

    lCamera = camera;
}


void LabyrinthNode::moveMainDot(float& timeStep)
{
  //  std::cout << "timestep: " << timeStep <<std::endl;

    //set camera over dot
    mainDotPointer->setCamera(lCamera);

    //move dot independent of frames, but rather dependent on time. includes collision detection
    mainDotPointer->moveOnTiles(timeStep, dungeonTileSet );

    //Restart timer
    timer->start();

}

/** Item Functions**/


void LabyrinthNode::placeKeyRandom(RNGType& rngData)
{
    /*
    //initialize random number
    int randomNumber = 0;

    //check for a wall tile
    for(size_t i=0; i < dungeonTileSet.size(); ++i)
    {
        if( dungeonTileSet[i]->getTypeFloor() == true )
        {
            //generate random number
            boost::random::variate_generator <RNGType&,boost::random::uniform_int_distribution <> > Die_12(rngData, zero2twelve);
            randomNumber = Die_12();

            //if randomNumber is between 5 and 8
            if(randomNumber == 12)
            {

                dungeonKey->setKeyPosition( dungeonTileSet[i]->getBox().x , dungeonTileSet[i]->getBox().y );
                std::cout << "key x:" << dungeonKey->getCollisionBox().x
                << "key y:" << dungeonKey->getCollisionBox().y << std::endl;

                break;
            }
        }
    }
    */

}

void LabyrinthNode::placeKeyRandomVector(RNGType& rngData)
{
    std::cout << "PlaceKeyRandomVector called! \n";

    boost::random::uniform_int_distribution <int> zero2twelve( 0, 12 );
    
    //initialize random number
    int randomNumber = 0;

    //initialize count
    int count = 0;

    //element that is on end of vector
    int endElement = (int)(dungeonKeys.size() );
    std::cout << endElement;

    //inititalize total tiles for boundschecking
    int totalTiles = (int)dungeonTileSet.size();
    
    
    while( count < endElement )
        {
             //generate random number
            boost::random::variate_generator <RNGType&,boost::random::uniform_int_distribution <> > Die_12(rngData, zero2twelve);
            randomNumber = Die_12();

            std::cout << "randomNumber:" << randomNumber << std::endl;

            //make randomNumber 1 if it is equal to zero to avoid keys placed in 0,0
            if(randomNumber < 1){ randomNumber = 1;}

            //assign random values to x and y position
            int x = randomNumber * 80;
            int y = (randomNumber + randomNumber - 2) * 40 ;

            std::cout << "x:"<< x << "y:" << y << std::endl;

            //assign tile number returned to element
            int element = (LabyrinthNode::getTileNumberFromPosition(x,y) );

            int elementLeft = element - 1;
            int elementRight = element + 1;
            int elementDown = element + 16;

            //bounds check
            if( elementDown >= totalTiles)
            {
                std::cout << "Warning element Down is out of bounds! \n";
                element = 1;
                elementLeft = 0;
                elementRight = 2;
                elementDown = 17;
            }
            
            //if tile element is a floor tile and below,left,right of it are floor tiles
            if( dungeonTileSet[element]->getTypeFloor() == true
                && dungeonTileSet[elementLeft]->getTypeFloor() == true
                && dungeonTileSet[elementRight]->getTypeFloor() == true
                && dungeonTileSet[elementDown]->getTypeFloor() == true )
            {
                //place key there
                dungeonKeys[count]->setKeyPosition(x,y);

                std::cout << "key" << count << " x:" <<
                dungeonKeys[count]->getCollisionBox().x
                << " y:" << dungeonKeys[count]->getCollisionBox().y << std::endl;

                //increment count
                count += 1;
            }

        }

}


void LabyrinthNode::placeDungeonDoors(RNGType& rngSeed)
{
    //std::cout << "placeDungeonDoors called in Dungeon Node! \n";
    
    if( dungeonDoors.size() == 0)
    {
        LabyrinthNode::placeThisOneDungeonDoor(rngSeed,dungeonDoors[0]);    
    }

    else
    {
        for(size_t i = 0; i < dungeonDoors.size(); ++i)
        {
            LabyrinthNode::placeThisOneDungeonDoor(rngSeed,dungeonDoors[i]);
        }
    }
}

void LabyrinthNode::placeEnemies(std::vector <Enemy*> &enemy_vector, 
                                size_t& startIterator, size_t& endIterator,
                                RNGType& rngSeed)
{
    if( enemy_vector.size() == 0)
    {
        LabyrinthNode::placeThisOneEnemy(rngSeed,enemy_vector[0]);    
    }

    else
    {
        for(size_t i = startIterator; i < endIterator; ++i)
        {
            LabyrinthNode::placeThisOneEnemy(rngSeed,enemy_vector[i]);
        }
    }
}

void LabyrinthNode::placeThisOneDungeonDoor(RNGType& rngSeed,Door* thisDoor)
{
     //set probablity for each number
	double probabilitiesNumber[] = { 0.0, 0.2, 0.2, 0.2, 0.2, 0.2 }; // probabilites for 0,1,2,3,4,5 
	//setup rng with set probablities    
	boost::random::discrete_distribution <int> dist(probabilitiesNumber);
	boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > Die(rngSeed,dist);

    size_t xCol,yRow;
    
    bool door1Placed = false;
    bool door2Placed = false;
    bool bothDoorsPlaced = false;
    
    std::int8_t randNumber = 0;
    
    size_t xEndCol = numXNodeColumns - 1;
    size_t yEndRow = numYNodeRows - 1;
    
    //bounds for area door should be placed in
    size_t xEdge = numXNodeColumns - 3;
    size_t yEdge = numYNodeRows - 3;

    while(!bothDoorsPlaced)
    {
        randNumber = Die();
        //assign random number to xcol and yrow
        if(randNumber >= 0 && randNumber <= 2)
        {
            xCol = numXNodeColumns - Die();
            yRow = numYNodeRows - Die(); 
        }
        else
        {
            xCol = Die();
            yRow = Die(); 
        }
        
        
        //bounds check
        //avoid putting doors in outer edges of node
        if(xCol >= xEdge){xCol = xEdge;}
        if(yRow >= yEdge){yRow = yEdge;}
   
        //if door 1 is not placed yet and dungeon tile is a floor tile
        if( !door1Placed && dungeon_tile_look_up [xCol][yRow]->getTypeFloor() )
        {
        
             //place the door on tile if no door to right of tile
             // and to left of tile
            if(dungeon_tile_look_up [xCol + 1][yRow]->getType() 
                != DungeonTile::TileType::DOOR
                && dungeon_tile_look_up [xCol - 1][yRow]->getType() 
                != DungeonTile::TileType::DOOR)
            {
                //place door  1 on floor tile
                std::int16_t xPos = dungeon_tile_look_up [xCol][yRow]->getBox().x;
                std::int16_t yPos = dungeon_tile_look_up [xCol][yRow]->getBox().y;
                thisDoor->placeDoor1( xPos,yPos);
                door1Placed = true;
                //set tile door is on as door tile type
                dungeon_tile_look_up [xCol][yRow]->setType(DungeonTile::TileType::DOOR);
        
                LabyrinthNode::setTilesAroundCenterToFloor(xCol,yRow,xEndCol,yEndRow);
                  
            }
             
        }
        else
        {
            //if door 2 isn't placed and tile is floor tile
            if(!door2Placed && dungeon_tile_look_up [xCol][yRow]->getTypeFloor())
            {
               //place door 2 on floor tile
                std::int16_t xPos = dungeon_tile_look_up [xCol][yRow]->getBox().x;
                std::int16_t yPos = dungeon_tile_look_up [xCol][yRow]->getBox().y;
                
                 
                 //place the door on tile if no door to right of tile
                if(dungeon_tile_look_up [xCol + 1][yRow]->getType() != DungeonTile::TileType::DOOR
                    && dungeon_tile_look_up [xCol - 1][yRow]->getType() != DungeonTile::TileType::DOOR)
                {
                    thisDoor->placeDoor2( xPos,yPos);
                    door2Placed = true;
                    //set tile door is on as door tile type
                    dungeon_tile_look_up [xCol][yRow]->setType(DungeonTile::TileType::DOOR);
                    
                    LabyrinthNode::setTilesAroundCenterToFloor(xCol,yRow,xEndCol,yEndRow);
                    
                    //set both doors placed as true
                    bothDoorsPlaced = true;
                } 
            }
        }
    }
}

void LabyrinthNode::setTilesAroundCenterToFloor(size_t& xCol,size_t& yRow,size_t& xEndCol, size_t& yEndRow)
{
    //make tiles left,right,above,and below it floor tiles
    //left
    if(xCol - 1 <= xEndCol)
    {
        //if tile isn't wall and is a hole
        if( !dungeon_tile_look_up [xCol - 1][yRow]->getTypeWall() 
            && dungeon_tile_look_up [xCol - 1][yRow]->getType() == DungeonTile::TileType::CENTER)
            {
                dungeon_tile_look_up [xCol - 1][yRow]->setType(DungeonTile::TileType::RED);
            }
    }
    //down left
    if(xCol - 1 <= xEndCol && yRow + 1 <= yEndRow)
    {
        //if tile isn't wall and is a hole
        if( !dungeon_tile_look_up [xCol - 1][yRow + 1]->getTypeWall() 
            && dungeon_tile_look_up [xCol - 1][yRow + 1]->getType() == DungeonTile::TileType::CENTER)
            {
                dungeon_tile_look_up [xCol - 1][yRow + 1]->setType(DungeonTile::TileType::RED);
            }
    }
    //right
    if(xCol + 1 <= xEndCol)
    {
        //if tile right of door is center tile
        if( dungeon_tile_look_up [xCol + 1][yRow]->getType() == DungeonTile::TileType::CENTER)
            {
                dungeon_tile_look_up [xCol + 1][yRow]->setType(DungeonTile::TileType::RED);
            }
    }
    //down right
    if(xCol + 1 <= xEndCol && yRow + 1 <= yEndRow)
    {
        //if tile isn't wall and is a hole
        if( !dungeon_tile_look_up [xCol + 1][yRow + 1]->getTypeWall() 
            && dungeon_tile_look_up [xCol + 1][yRow + 1]->getType() == DungeonTile::TileType::CENTER)
            {
                dungeon_tile_look_up [xCol + 1][yRow + 1]->setType(DungeonTile::TileType::RED);
            }
    }
    //above
    if(yRow - 1 <= yEndRow)
    {
         if(!dungeon_tile_look_up [xCol ][yRow - 1]->getTypeWall() 
            && dungeon_tile_look_up [xCol][yRow - 1]->getType() == DungeonTile::TileType::CENTER)
            {
                dungeon_tile_look_up [xCol][yRow - 1]->setType(DungeonTile::TileType::RED);
            }
    }
    //up left
    if(xCol - 1 <= xEndCol && yRow - 1 <= yEndRow)
    {
        //if tile isn't wall and is a hole
        if( !dungeon_tile_look_up [xCol - 1][yRow - 1]->getTypeWall() 
            && dungeon_tile_look_up [xCol - 1][yRow - 1]->getType() == DungeonTile::TileType::CENTER)
            {
                dungeon_tile_look_up [xCol - 1][yRow - 1]->setType(DungeonTile::TileType::RED);
            }
    }
    //up right
    if(xCol + 1 <= xEndCol && yRow - 1 <= yEndRow)
    {
        //if tile isn't wall and is a hole
        if( !dungeon_tile_look_up [xCol + 1][yRow - 1]->getTypeWall() 
            && dungeon_tile_look_up [xCol + 1][yRow - 1]->getType() == DungeonTile::TileType::CENTER)
            {
                dungeon_tile_look_up [xCol + 1][yRow - 1]->setType(DungeonTile::TileType::RED);
            }
    }
    //below
    if(yRow + 1 <= yEndRow)
    {
        if(!dungeon_tile_look_up [xCol ][yRow + 1]->getTypeWall() 
            && dungeon_tile_look_up [xCol][yRow + 1]->getType() == DungeonTile::TileType::CENTER)
            {
                dungeon_tile_look_up [xCol][yRow + 1]->setType(DungeonTile::TileType::RED);
            }
    }
}

//function to setup door object allocated in heap memory from door class
void setupNewDoorObject(Door** thisDoor,
                            LTexture* doorTexture,
                            ALuint* source,
                            ALuint* doorBufferOpen, 
                            ALuint* doorBufferFail,
                            std::vector <SDL_Rect> *ptrDoorClips);
                            
//function to setup key object allocated in heap memory from key class                            
void setupNewKeyObject(Key** thisKey,LTexture* keyTexture,ALuint* source,ALuint* buffer);

void LabyrinthNode::setupDoorsAndKeys(std::int8_t& numDoors,
                                    std::int8_t& numKeys,
                                LTexture& keyTexture,
                                ALuint& keySource,
                                ALuint& keyBuffer,
                                LTexture& doorTexture,
                                ALuint& doorSource,
                                ALuint& doorBufferOpen,
                                ALuint& doorBufferFail,
                                std::vector <SDL_Rect> *doorClips)
{
   
    
    //std::cout<< "setupDoorsAndKeys called! \n";

    dungeonKeys.resize(numKeys);
    dungeonDoors.resize(numDoors);
    
    //std::cout << "Keys:" << dungeonKeys.size() << "Doors:" << dungeonDoors.size() << std::endl ;
    
    
    //setup keys
    for(size_t i=0; i < dungeonKeys.size(); ++i )
    {
        
        
        setupNewKeyObject(&dungeonKeys[i], &keyTexture,&keySource,&keyBuffer);
    }
    
   //setup doors
    for(size_t i=0; i < dungeonDoors.size(); ++i)
    {
        
        setupNewDoorObject(&dungeonDoors[i],
                            &doorTexture,
                            &doorSource,
                            &doorBufferOpen, 
                            &doorBufferFail,
                            doorClips);
    }
}

void LabyrinthNode::freeDoorsAndKeys()
{
    std::cout << "freeDoorsAndKeys called! \n";

    //free keys
    if( dungeonKeys.size() == 0 )
    {
        delete dungeonKeys[0];
    }
    else
    {
        for(size_t i=0; i < dungeonKeys.size(); ++i )
        {
            delete dungeonKeys[i];
        }
    }

    //free doors
    if( dungeonDoors.size() == 0 )
    {
            delete dungeonDoors[0];
    }

    else
    {
        for(size_t i=0; i < dungeonDoors.size(); ++i )
        {
            delete dungeonDoors[i];
        }
    }
}

void LabyrinthNode::checkKeyAndDot()
{
    if( dungeonKeys.size() == 0 )
    {
        //if dot collides with one of key objects
        if( checkCollision( dungeonKeys[0]->getCollisionBox(), mainDotPointer->getCollisionBox() ) == true)
        {
            //key is picked up
            dungeonKeys[0]->setKeyBool(true);
        }
    }

    else
    {
        //for every key object
        for(size_t i =0; i < dungeonKeys.size() ; ++i )
        {
            //if dot collides with one of key objects
            if( checkCollision( dungeonKeys[i]->getCollisionBox(), mainDotPointer->getCollisionBox() ) == true)
            {
                //key is picked up
                dungeonKeys[i]->setKeyBool(true);
            }
        }
    }


}

//function to place 1 enemy in node
void LabyrinthNode::placeThisOneEnemy(RNGType& rngSeed,Enemy* thisEnemy)
{
      //set probablity for each number
	double probabilitiesNumber[] = { 0.2, 0.2, 0.2, 0.2, 0.2, 0.2 }; // probabilites for 0,1,2,3,4,5 
	//setup rng with set probablities    
	boost::random::discrete_distribution <int> dist(probabilitiesNumber);
	boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > Die(rngSeed,dist);

    size_t xCol,yRow;
    
    size_t xEndCol = numXNodeColumns - 1;
    size_t yEndRow = numYNodeRows - 1;
    
    bool placedOnFloor = false;
    
    std::int8_t randNumber = 0;
    
    while(!placedOnFloor)
    {
        randNumber = Die();
        //assign random number to xcol and yrow
        if(randNumber >= 0 && randNumber <= 2)
        {
            xCol = numXNodeColumns - Die();
            yRow = numYNodeRows - Die(); 
        }
        else
        {
            xCol = Die();
            yRow = Die(); 
        }
        
        if(xCol <= xEndCol && yRow <= yEndRow)
        {
            if(dungeon_tile_look_up [xCol][yRow]->getTypeFloor())
            {
                //get tile position
                float x = dungeon_tile_look_up [xCol][yRow]->getBox().x;
                float y = dungeon_tile_look_up [xCol][yRow]->getBox().y;
                
                //place enemy on tile
                thisEnemy->setPosX(x);
                thisEnemy->setPosY(y);
                //set tile as occupied
                dungeon_tile_look_up [xCol][yRow]->setType(DungeonTile::TileType::OCCUPIED);
                
                placedOnFloor = true;
            }
        }
    }
}

/** Game Loop Functions**/

void LabyrinthNode::handle_events(Event& thisEvent)
{
   // std::cout << "Handle events called! \n";

    //User requests pause by pressing escape
    if( thisEvent.event_id == Event_ID::ESCAPE )
    {
        std::cout<< "Escape key pressed! \n";
        //LabyrinthNode::setEscapeBool(true);
        //set pause state
        LabyrinthNode::setState(GameState::State::PAUSE);
    }
    //User requests quit by X out window
    else if(thisEvent.event_id == Event_ID::QUIT_WINDOW)
    {
        //LabyrinthNode::setEscapeBool(true);
        LabyrinthNode::setState(GameState::State::EXIT);
    }

    mainDotPointer->handleEvent(thisEvent);

/*
    for(size_t i=0; i < (*dungeonDoors).size(); ++i)
    {
        (*dungeonDoors)[i]->handle_event(*event);
    }
*/
}

void LabyrinthNode::handle_events_RNG(RNGType& rngSeed){}

void LabyrinthNode::logic()
{
    //std::cout << "Logic called! \n";
    float timeStep = timer->getTicks() / 1000.f; //frame rate

    //move main dot
    LabyrinthNode::moveMainDot(timeStep);


    //move dot back if collides with door
    LabyrinthNode::doorCollision(timeStep);
/*
     //check if main dot collides with any key while another key hasn't been picked making rest of keys disappear in render
    if(!keyDisappear)
    {
        LabyrinthNode::checkKeyAndDot();
    }


    //check if a key has been picked up
    for(size_t i=0; i < (*dungeonKeys).size(); ++i )
    {
        if( (*dungeonKeys)[i]->getKeyBool() == true )
        {
            keyDisappear = true;
        }
    // Exit State and Next State Conditions


    //exit by door if main dot collides with right key
    LabyrinthNode::checkWrongDoor();
    LabyrinthNode::exitByDoor();
*/
}

void LabyrinthNode::exitByTile()
{
    //if dot collides with an exit tile
    for(size_t i =0; i < dungeonTileSet.size(); ++i)
        {
            if( dungeonTileSet[i]->getTypeExit() == true )
            {
                //make smaller rectangle copy of exit tile
                SDL_Rect smallerExitBox;
                smallerExitBox = dungeonTileSet[i]->getBox();

                smallerExitBox.x= dungeonTileSet[i]->getBox().x + 40; smallerExitBox.y= dungeonTileSet[i]->getBox().y + 40;
                smallerExitBox.w=10; smallerExitBox.h=10;

                if( checkCollision(mainDotPointer->getCollisionBox(), smallerExitBox ) == true 
                /*|| LabyrinthNode::getExitState() == true */)
                {
                    //go to next state
                    LabyrinthNode::setState(GameState::State::NEXT);
                }
            }
        }

}

void LabyrinthNode::exitByDoor()
{
    for(size_t i=0; i < dungeonDoors.size(); ++i)
    {

        //run open door logic
        dungeonDoors[i]->openDoorLogic();

            if( dungeonDoors[i]->getDoorState() == Door::State::DOOR_OPEN)
            {
                //go to next state
                LabyrinthNode::setState(GameState::State::NEXT);
            }
    }

}

void LabyrinthNode::checkWrongDoor()
{
    /*
     //check if any of the doors have tried to been open with wrong key
    for(size_t i=0; i < (*dungeonDoors).size(); ++i)
    {
        //check if dot collides with door
        if( checkCollision(mainDotPointer->getSpaceBox() , (*dungeonDoors)[i]->getCollisionBox() ) )
        {
            //check if space was pressed on door and if door didn't open
            if( (*dungeonDoors)[i]->getKeyInsertStatus() == true 
                && (*dungeonDoors)[i]->getDoorOpenStatus() == false 
                && keyDisappear == true )
            {
                std::cout << "Wrong Door! \n";
                //set door attempt fail to true
                //(*dungeonDoors)[i]->setDoorOpenAttemptFail(true);
                (*dungeonDoors)[i]->setDoorState(Door::State::DOOR_OPEN_FAIL);
            }
            else{(*dungeonDoors)[i]->setDoorState(Door::State::DOOR_CLOSED);}
        }
        else{(*dungeonDoors)[i]->setDoorState(Door::State::DOOR_CLOSED);}
    }
     * */
}

void LabyrinthNode::doorCollision(float timeStep)
{
    
    if( dungeonDoors.size() == 0)
    {
        //if dot collides with door
        if( checkCollision( mainDotPointer->getCollisionBox(), 
                        dungeonDoors[0]->getCollisionBoxDoor1()) )
        {
            //move dot back
            mainDotPointer->moveBack(timeStep);
        }
        else if(checkCollision( mainDotPointer->getCollisionBox(), 
                        dungeonDoors[0]->getCollisionBoxDoor2()))
        {
            //move dot back
            mainDotPointer->moveBack(timeStep);
        }

    }
    else
    {
        for(size_t i=0;i < dungeonDoors.size(); ++i)
        {
            //if dot collides with a door
            if( checkCollision( mainDotPointer->getCollisionBox(), 
                                dungeonDoors[i]->getCollisionBoxDoor1() ) )
            {

                //move dot back
                mainDotPointer->moveBack(timeStep);
            }
            else if(checkCollision( mainDotPointer->getCollisionBox(), 
                                dungeonDoors[i]->getCollisionBoxDoor2() ))
            {
                //move dot back
                mainDotPointer->moveBack(timeStep);
            }
        }
    }
     
}

//play sounds
void LabyrinthNode::sound(AudioRenderer* gAudioRenderer)
{
    
    //play dungeon music
    //play sound from dgmSource
    alGetSourcei(*dgmSource, AL_SOURCE_STATE, &musicState);
    if (musicState == AL_STOPPED || musicState == AL_INITIAL){ alSourcePlay(*dgmSource);}
/*
    //play key sounds
    for(size_t i=0; i < (*dungeonKeys).size(); ++i)
    {
        if( (*dungeonKeys)[i]->getKeyBool() == true  )
        {
            //play just once
            while(loopSFX <= 1)
            {

                std::cout << "count: " << loopSFX <<std::endl;
                //play dungeon key sounds only once
                (*dungeonKeys)[i]->playSound();

                loopSFX += 1;
            }

        }
    }


    //play dungeon door sounds
    for(size_t i=0; i < (*dungeonDoors).size(); ++i)
    {
        //play dungeon door sounds
        (*dungeonDoors)[i]->playSounds();
        //(*dungeonDoors)[i]->setDoorOpenAttemptFail(false);
    }
*/

}

void LabyrinthNode::render(SDL_Renderer* gRenderer)
{
  //  std::cout << "render called! \n";


    //Render level
    for( size_t i = 0; i < dungeonTileSet.size(); ++i )
    {
        dungeonTileSet[i]->render(tileTextureMap,lCamera,gRenderer);
    }

    //render dot
    mainDotPointer->render(lCamera,gRenderer);

/*
    //render keys
    if(!keyDisappear)
    {
        for(size_t i=0; i < (*dungeonKeys).size(); ++i)
        {
            (*dungeonKeys)[i]->render(lCamera,gRenderer);
        }

    }


    //render doors
    for(size_t i=0; i < (*dungeonDoors).size(); ++i)
    {
        (*dungeonDoors)[i]->render(lCamera,gRenderer);
    }
*/

}

void LabyrinthNode::render(DrawingManager* gDrawManager)
{
	
}

//Set States
void LabyrinthNode::setState(GameState::State thisState){GameState::setState(thisState);}
GameState::State LabyrinthNode::getState(){return GameState::getState();}

int LabyrinthNode::getDotTileNumber()
{
    for(size_t i=0; i < dungeonTileSet.size(); ++i )
    {
        if(checkCollision(mainDotPointer->getCollisionBox(), dungeonTileSet[i]->getBox() ) == true)
        {
            return dungeonTileSet[i]->getTileNumber();
        }
    }

}

int LabyrinthNode::getTileNumberFromPosition(int x, int y)
{
    int tileNumber =0;

    std::cout << "previous x:" << x << "previous y:" << y << std::endl;

    if( x % 80 != 0 ){ x = x - (x % 80);}
    if( y % 80 != 0){ y = y  - (y % 80); }


    std::cout << "rounded x:" << x << "rounded  y:" << y << std::endl;
    
    size_t dotXCol = ( x - NODE_X ) / TILE_WIDTH;
    size_t dotYRow = ( y - NODE_Y ) / TILE_HEIGHT;
    
    if(dotXCol >= numXNodeColumns || dotYRow >= numYNodeRows){return 0;}
    else
    {
        tileNumber = dungeon_tile_look_up [dotXCol][dotYRow]->getTileNumber();
        return tileNumber;
    }
}


SDL_Rect LabyrinthNode::getTileBox_under_dot()
{
    for(size_t i=0; i < dungeonTileSet.size(); ++i )
    {
        if( checkCollision(mainDotPointer->getCollisionBox(), dungeonTileSet[i]->getBox() ) == true)
        {
            return dungeonTileSet[i]->getBox();
        }
    }

}

DungeonTile* LabyrinthNode::getDungeonTileFromPosition(int x, int y) 
{
    size_t xCol = ( x - NODE_X ) / TILE_WIDTH;
    size_t yRow = ( y - NODE_Y ) / TILE_HEIGHT;
    
    if(xCol >= numXNodeColumns || yRow >= numYNodeRows){return nullptr;}
    else{ return dungeon_tile_look_up [xCol] [yRow];}
}

void LabyrinthNode::getXColYRowFromPosition(int x, int y,size_t& xCol, size_t& yRow)
{
     xCol= ( x - NODE_X ) / TILE_WIDTH;
     yRow = ( y - NODE_Y   ) / TILE_HEIGHT;
}


void LabyrinthNode::setWallTopSide()
{
    for(size_t xCol = 0; xCol < numXNodeColumns; xCol++)
    {
        if(xCol == 0){dungeon_tile_look_up [xCol][0]->setType(DungeonTile::TileType::TOP_LEFT);}
        else if(xCol == numXNodeColumns - 1){dungeon_tile_look_up [xCol][0]->setType(DungeonTile::TileType::TOP_RIGHT);}
        else{dungeon_tile_look_up [xCol][0]->setType(DungeonTile::TileType::TOP);}
    }
}

void LabyrinthNode::setWallLeftSide()
{
    for(size_t yRow = 0; yRow < numYNodeRows; yRow++)
    {
        if(yRow == 0){dungeon_tile_look_up [0][yRow]->setType(DungeonTile::TileType::TOP_LEFT);}
        else if(yRow == numYNodeRows - 1){dungeon_tile_look_up [0][yRow]->setType(DungeonTile::TileType::BOTTOM_LEFT);}
        else{dungeon_tile_look_up [0][yRow]->setType(DungeonTile::TileType::LEFT);}
    }
}

void LabyrinthNode::setWallRightSide()
{
    for(size_t yRow = 0; yRow < numYNodeRows; yRow++)
    {
        if(yRow == 0){dungeon_tile_look_up [numXNodeColumns - 1][yRow]->setType(DungeonTile::TileType::TOP_RIGHT);}
        else if(yRow == numYNodeRows - 1){dungeon_tile_look_up [numXNodeColumns - 1][yRow]->setType(DungeonTile::TileType::BOTTOM_RIGHT);}
        else{dungeon_tile_look_up [numXNodeColumns - 1][yRow]->setType(DungeonTile::TileType::RIGHT);}
    }
}

void LabyrinthNode::setWallBottomSide()
{
    for(size_t xCol = 0; xCol < numXNodeColumns; xCol++)
    {
        if(xCol == 0){dungeon_tile_look_up [xCol][numYNodeRows - 1]->setType(DungeonTile::TileType::BOTTOM_LEFT);}
        else if(xCol == numXNodeColumns - 1){dungeon_tile_look_up [xCol][numYNodeRows - 1]->setType(DungeonTile::TileType::BOTTOM_RIGHT);}
        else{dungeon_tile_look_up [xCol][numYNodeRows - 1]->setType(DungeonTile::TileType::BOTTOM);}
    }
}

void LabyrinthNode::setTopWallOnThisRow(size_t& rowNum)
{
    //bounds checking
    if(rowNum < numYNodeRows )
    {
        for(size_t xCol = 0; xCol < numXNodeColumns; xCol++)
        {
            if(xCol == 0){dungeon_tile_look_up [xCol][rowNum]->setType(DungeonTile::TileType::TOP_LEFT);}
            else if(xCol == numXNodeColumns - 1){dungeon_tile_look_up [xCol][rowNum]->setType(DungeonTile::TileType::TOP_RIGHT);}
            else{dungeon_tile_look_up [xCol][rowNum]->setType(DungeonTile::TileType::TOP);}
        }
    }
}

void LabyrinthNode::setLeftWallOnThisColumn(size_t& colNum)
{
    if(colNum < numXNodeColumns)
    {
        for(size_t yRow = 0; yRow < numYNodeRows; yRow++)
        {
            if(yRow == 0){dungeon_tile_look_up [colNum][yRow]->setType(DungeonTile::TileType::TOP_LEFT);}
            else if(yRow == numYNodeRows - 1){dungeon_tile_look_up [colNum][yRow]->setType(DungeonTile::TileType::BOTTOM_LEFT);}
            else{dungeon_tile_look_up [colNum][yRow]->setType(DungeonTile::TileType::LEFT);}
        }
    }
    
}

void LabyrinthNode::setRightWallOnThisColumn(size_t& colNum)
{
    if(colNum < numXNodeColumns )
    {
        for(size_t yRow = 0; yRow < numYNodeRows; yRow++)
        {
            if(yRow == 0){dungeon_tile_look_up [colNum][yRow]->setType(DungeonTile::TileType::TOP_RIGHT);}
            else if(yRow == numYNodeRows - 1){dungeon_tile_look_up [colNum][yRow]->setType(DungeonTile::TileType::BOTTOM_RIGHT);}
            else{dungeon_tile_look_up [colNum][yRow]->setType(DungeonTile::TileType::RIGHT);}
        }
    }
    
}

void LabyrinthNode::setBottomWallOnThisRow(size_t& rowNum)
{
    //bounds checking
    if(rowNum < numYNodeRows )
    {
        for(size_t xCol = 0; xCol < numXNodeColumns; xCol++)
        {
            if(xCol == 0){dungeon_tile_look_up [xCol][rowNum]->setType(DungeonTile::TileType::BOTTOM_LEFT);}
            else if(xCol == numXNodeColumns - 1){dungeon_tile_look_up [xCol][rowNum]->setType(DungeonTile::TileType::BOTTOM_RIGHT);}
            else{dungeon_tile_look_up [xCol][rowNum]->setType(DungeonTile::TileType::BOTTOM);}
        }
    }
    
}

void LabyrinthNode::setInvisibleWallOnThisRow(size_t& rowNum)
{
    if(rowNum < numYNodeRows)
    {
        for(size_t xCol = 0; xCol < numXNodeColumns - 1; xCol++)
        {
            dungeon_tile_look_up [xCol][rowNum]->setType(DungeonTile::TileType::INVISIBLE_WALL);
        }
    }
}

void LabyrinthNode::setInvisibleWallOnThisColumn(size_t& colNum)
{
    if(colNum < numXNodeColumns)
    {
        for(size_t yRow = 0; yRow < numYNodeRows - 1; yRow++)
        {
            dungeon_tile_look_up [colNum][yRow]->setType(DungeonTile::TileType::INVISIBLE_WALL);
        }
    }
    
}



/*

 *     std::cout << "In dungeon 1 state! \n";

// Setup for Tiles in Dungeon

    
    std::int16_t numTiles = 0;

    //calculate number of tiles in dungeon
    numTiles = (LEVEL_WIDTH / tileWidth) * (LEVEL_HEIGHT / tileHeight);

    //define LabyrinthNode object
    LabyrinthNode gDungeon1;
    gDungeon1.setLevelDimensions(LEVEL_WIDTH,LEVEL_HEIGHT);
    gDungeon1.setPointerToTimer(&stepTimer);
    gDungeon1.setPointerToMainDot(mainDotPointer.get());
    //set pointers to media
    gDungeon1.setPointersToMedia(&dungeonTilesTexture,&dungeonMusicSource,&dungeonMusicBuffer);
    
    std::cout << "Creating blank tiles... \n";
    //create blank tiles
    std::int16_t startX = 0;
    std::int16_t startY = 0;
    gDungeon1.createBlankTiles(startX,startY,
                            tileWidth,tileHeight,
                            numTiles);

    //randomly generate tiles
    std::cout << "Generating tiles... \n";
    gDungeon1.generateMapDrunkardWalk(rng,numTiles);
    std::cout << "Setting tile types randomly... \n";
    gDungeon1.setTileTypesRandom(rng);
    
    gDungeon1.genRuleWall(rng,zero_to_twelve);
    gDungeon1.setWallTopSide();
    gDungeon1.setWallLeftSide();
    gDungeon1.setWallRightSide();
    gDungeon1.setWallBottomSide();
    //call gen rules

    //limit on number of exits appearing
    int exitMax = 5; int exitMin = 1;

    gDungeon1.genRuleLimitExits(exitMax,exitMin,rng,zero_to_twelve);

    gDungeon1.genRuleExitPath();

    

    


    //gDungeon1.genRuleWall(rng,zero_to_twelve);
    //gDungeon1.genRuleDotStart();
    
    //set tile clips
    gDungeon1.setTiles();

// Setup for doors in dungeon

    gDungeon1.countNumberOfExits();

    int numExits = gDungeon1.getNumberOfExits();

    std::cout << "Exits:" << numExits << std::endl;

    std::vector <Key *> keys(numExits );
    std::vector <Door *> doors(numExits );

    //setup doors and keys
    gDungeon1.setupDoorsAndKeys(keys,doors,
                            keyTexture,
                            keySource,
                            keyBuffer,
                            doorTexture,
                            doorSource,
                            doorBufferOpen,
                            doorBufferFail );
    
    //randomly place keys in dungeon

    gDungeon1.placeKeyRandomVector(rng,zero_to_twelve);

    //place doors
    gDungeon1.placeDungeonDoors();

    //Setup Dungeon Node camera for dot
    gDungeon1.setLabyrinthNodeCameraForDot(SCREEN_WIDTH,SCREEN_HEIGHT,
                                            camera);
    


*/
