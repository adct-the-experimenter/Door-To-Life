#include "labyrinth.h" 

Labyrinth::Labyrinth()
{
    Labyrinth::setDebugBool(false);
    //initialize array of doubles for generating labyrinth node dimensions
    //probabilites for 0,1,2,3,4
    probabilitiesGenLabyrinthNodeDimensions= {0.3, 0.4,0.0,0.0,0.0};
    
    m_game_inventory_ptr = nullptr; 
        
    hitDungeonEntrace_p1 = false;
	hitDungeonEntrace_p2 = false;
	hitDungeonEntrace_p3 = false;
	hitDungeonEntrace_p4 = false;
	
	hitLabyrinthExit_p1 = false;
	hitLabyrinthExit_p2 = false;
	hitLabyrinthExit_p3 = false;
	hitLabyrinthExit_p4 = false;
}

Labyrinth::~Labyrinth()
{
    //m_enemy_inventory.freeEnemyMedia();
    m_enemy_inventory.freeEnemyVector();
}

void Labyrinth::setCamera(SDL_Rect* thisCamera){labyrinthCamera = thisCamera;}

void Labyrinth::setState(GameState::State thisState){GameState::setState(thisState);}
GameState::State Labyrinth::getState(){return GameState::getState();}

void Labyrinth::setNumberNodesToGenerate(std::int16_t& num){numberNodesToGenerate = num;}
std::int16_t& Labyrinth::getNumberNodesToGenerate(){return numberNodesToGenerate;}

void Labyrinth::setGridDimensions(std::int16_t& x,std::int16_t& y,
                        std::int16_t& w,std::int16_t& h)
{
    GRID_X = x;
    GRID_Y = y;
    GRID_WIDTH = w;
    GRID_HEIGHT = h;
}

void Labyrinth::randomlySetNumberOfNodesToGenerate(RNGType& rngSeed)
{
    // width and height of nodes
    std::int8_t node_w = 20;
    std::int8_t node_h = 20;
    
    //number of nodes in 1 row
    std::int16_t num_node_rows = GRID_WIDTH / node_w;
    //number of nodes in 1 column
    std::int16_t num_node_cols = GRID_HEIGHT / node_h;
    
    //number of nodes in entire grid
    std::int16_t num_nodes_grid = num_node_cols * num_node_rows;
    
    //set number of nodes to generate as 3/4 of total nodes in grid
    std::int16_t num_node_gen = ( num_nodes_grid / 2);
    
    Labyrinth::setNumberNodesToGenerate(num_node_gen);
}



bool Labyrinth::generateLabyrinth(RNGType& rngSeed)
{
    bool success = true;
    
    //if generate labyrint node successful
    if(Labyrinth::generateLabyrinthNodes(rngSeed) )
    {
        //generate maze
        Labyrinth::generateLabyrinthMaze(rngSeed);
    }
    else{success = false;}
    
    return success;
}

bool Labyrinth::generateLabyrinthNodes(RNGType& rngSeed)
{
    bool success = true;
    
    nodesGen.setGridDimensions(GRID_X,GRID_Y,GRID_WIDTH,GRID_HEIGHT);
    nodesGen.setNumberOfNodesInLabyrinth(Labyrinth::getNumberNodesToGenerate());
    
    std::cout << "generating nodes... \n";
    nodesGen.generateNodes(rngSeed);
    
    std::cout << "choosing generated nodes... \n";
    if(!nodesGen.chooseNodesRandomly(rngSeed) ){success = false;}
    
    return success;
}

void Labyrinth::generateLabyrinthMaze(RNGType& rngSeed)
{
    std::cout << "Loading resources for maze generator... \n";
    mazeGen.loadResourcesFromNodeGenerator(&nodesGen);
    
    
    std::cout << "Generating maze... \n";
    mazeGen.generateMaze(rngSeed);
}



void Labyrinth::generateDungeonsInLabyrinth(RNGType& rngSeed, 
                                                LTexture& keyTexture,
                                                ALuint& keySource,
                                                ALuint& keyBuffer,
                                                LTexture& doorTexture,
                                                ALuint& doorSource,
                                                ALuint& doorOpenSound,
                                                ALuint& doorFailSound,
                                                std::vector <SDL_Rect> *doorClips)
{
    //create vector of dungeon nodes with same number of maze nodes
    size_t labyrinthNodesVectorSize = mazeGen.mazeNodesVector.size();
    std::vector <LabyrinthNode> tempLabyrinthNodes;
    tempLabyrinthNodes.resize(labyrinthNodesVectorSize);
    
    std::cout << "Generating map tiles! \n";
    Labyrinth::setupLabyrinthMapTiles(rngSeed,tempLabyrinthNodes);
    std::cout << "Randomly generating doors! \n";
    Labyrinth::setupLabyrinthDoors(rngSeed,tempLabyrinthNodes,
                                 keyTexture,keySource,keyBuffer,
                                 doorTexture,doorSource,doorOpenSound,doorFailSound,
                                 doorClips);
                                
    std::cout << "Placing enemies in Labyrinth! \n";
    m_enemy_inventory.setupEnemyVector();                             
    Labyrinth::placeEnemiesInLabyrinth(rngSeed,tempLabyrinthNodes, *m_enemy_inventory.GetEnemyVector());
    std::cout << "Loading map from nodes generated... \n";
    //create dungeon map and all content(tiles,doors) from vector of dungeon nodes
    labyrinthMap.loadMapFromLabyrinthNodes(tempLabyrinthNodes);
    std::cout << "Finished loading map! \n";
}

void Labyrinth::generateDungeonsInLabyrinth_Debug_Gen(RNGType& rngSeed)
{
    //create vector of dungeon nodes with same number of maze nodes
    size_t labyrinthNodesVectorSize = mazeGen.mazeNodesVector.size();
    std::vector <LabyrinthNode> tempLabyrinthNodes;
    tempLabyrinthNodes.resize(labyrinthNodesVectorSize);
    
    Labyrinth::setupLabyrinthMapTiles(rngSeed,tempLabyrinthNodes);
    
    //create dungeon map and all content(tiles,doors) from vector of dungeon nodes
    labyrinthMap.loadMapFromLabyrinthNodes(tempLabyrinthNodes);
}

void Labyrinth::setTiles()
{
    //set tile clips
    labyrinthMap.setClipsForTiles();
}

void Labyrinth::setupLabyrinthMapTiles(RNGType& rngSeed,std::vector <LabyrinthNode> &labyrinthNodesVector)
{

    bool quit = false;
    
    //dungeon Node
    std::int16_t startTileX = 0;
    std::int16_t startTileY = 0;
    boost::random::uniform_int_distribution <int> zero_to_twelve( 0, 12 );
    size_t iteratorLabyrinthNode = 0;
    
    TILE_WIDTH = globalTileWidth;
    TILE_HEIGHT = globalTileHeight;
    
    //number of rows for a largest base labyrinth node
    std::int8_t baseNumRows = 8;
    //number of columns for a largest base labyrinth node
    std::int8_t baseNumColumns = 10;
    
    NODE_LEVEL_WIDTH = TILE_WIDTH * baseNumRows;
    NODE_LEVEL_HEIGHT = TILE_HEIGHT * baseNumColumns;
    
    
    //number of tiles in labyrinth node
    std::int16_t numTiles = (NODE_LEVEL_WIDTH / TILE_WIDTH) * (NODE_LEVEL_HEIGHT / TILE_HEIGHT);
    
    //maze node
    size_t xCol = 0; size_t yRow = 0;
    size_t endRow = mazeGen.numberXNodeColumns - 1;
    size_t endCol = mazeGen.numberYNodeRows - 1;
    
    //conversion factor from maze node position to screen position
    // every 1 column is size of level width
    std::int16_t x_maze_col_tile_convert =  1 * NODE_LEVEL_WIDTH;
    //every 1 row is size of level height
    std::int16_t y_maze_row_tile_convert = 1 * NODE_LEVEL_HEIGHT;
    
        
    //for each dungeon node
    while(!quit)
    {
        //go through each maze node element to check for wall
        
        //if maze node pointer element is not nullptr 
        if(mazeGen.maze_node_look_up [xCol][yRow] != nullptr)
        {
            //create dungeon node
            LabyrinthNode thisLabyrinthNode;
            
            thisLabyrinthNode.setLevelDimensions(NODE_LEVEL_WIDTH,NODE_LEVEL_HEIGHT);
            //thisLabyrinthNode.setLevelDimensions(randLevelWidth,randLevelHeight);
            
            startTileX = xCol * x_maze_col_tile_convert; 
            startTileY = yRow * y_maze_row_tile_convert;
            
            //create blank tiles
             thisLabyrinthNode.createBlankTiles(startTileX,startTileY,
                                    TILE_WIDTH,TILE_HEIGHT,
                                    numTiles);

            //randomly generate tiles
            //std::cout << "Generating tiles... \n";
            thisLabyrinthNode.generateMapDrunkardWalk(rngSeed,numTiles);
            //std::cout << "Setting tile types randomly... \n";
            thisLabyrinthNode.setTileTypesRandom(rngSeed);
            
            thisLabyrinthNode.genRuleWall(rngSeed,zero_to_twelve);
            
            //set walls 
            
            //set walls uniform labyrinth node stlye
            Labyrinth::setWallsUniformLabyrinthNode(thisLabyrinthNode,xCol,yRow);
            
            /*
            Labyrinth::setWallsRandomLabyrinthNode(thisLabyrinthNode,
                                                xCol,yRow,
                                                baseNumColumns, baseNumRows,
                                                rngSeed);
            */
            
            labyrinthNodesVector[iteratorLabyrinthNode] = thisLabyrinthNode;
            
            //std::cout << "Labyrinth Node " << iteratorLabyrinthNode << " map tiles generated! \n";
            
            iteratorLabyrinthNode++;
            
        }
        
        //if reached last element of maze node vector of maze gen
        if(xCol == endCol && yRow == endRow){quit = true;}
        
        //increment x column
        xCol++;
        //increment y row if at end col, restart xcol
        if(xCol > endCol){xCol = 0; yRow++;}
    }
    
    std::cout << "Finished generating map tiles! \n";
}

void Labyrinth::setWallsUniformLabyrinthNode(LabyrinthNode& thisLabyrinthNode,
                                            size_t& xNodeCol, size_t& yNodeRow)
{
    //check if maze node has walls
    //if yes create wall in dungeon node in that direction
    if(mazeGen.maze_node_look_up [xNodeCol][yNodeRow]->getWallInThisDirection
        (MazeNode::WallDirection::NORTH))
    {
        thisLabyrinthNode.setWallTopSide();
    }
    if(mazeGen.maze_node_look_up [xNodeCol][yNodeRow]->getWallInThisDirection
        (MazeNode::WallDirection::EAST))
    {
        thisLabyrinthNode.setWallRightSide();
    }
    if(mazeGen.maze_node_look_up [xNodeCol][yNodeRow]->getWallInThisDirection
        (MazeNode::WallDirection::SOUTH))
    {
        thisLabyrinthNode.setWallBottomSide();
    }
    if(mazeGen.maze_node_look_up [xNodeCol][yNodeRow]->getWallInThisDirection
        (MazeNode::WallDirection::WEST))
    {
        thisLabyrinthNode.setWallLeftSide();
    }
}

void Labyrinth::setWallsRandomLabyrinthNode(LabyrinthNode& thisLabyrinthNode,
                                        size_t& xNodeCol, size_t& yNodeRow,
                                        std::int8_t& baseNumColumns, std::int8_t& baseNumRows,
                                        RNGType& rngSeed)
{
    //bool to tell if there is a wall in cardinal directions
    bool northWall = false;
    bool southWall = false;
    bool eastWall = false;
    bool westWall = false;
    
    //variable for number of rows to make node 
    //when randomly generating labyrinth node
    std::int8_t pseudoRandNumRows = 0;
    //variable for number of columns to make node 
    //when randomly generating labyrinth node
    std::int8_t pseudoRandNumColumns = 0;
    
    //setup rng with set probablities    
    boost::random::discrete_distribution <int> distDirection(probabilitiesGenLabyrinthNodeDimensions);
    boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > DimensionsDie(rngSeed,distDirection);

    //generate pseudo dimensions for node
    //using random number generated
    pseudoRandNumRows = baseNumRows - 1 - DimensionsDie();
    pseudoRandNumColumns = baseNumColumns - 1 - DimensionsDie();
    
    //check if maze node has walls
    //if yes create wall in dungeon node in that direction
    if(mazeGen.maze_node_look_up [xNodeCol][yNodeRow]->getWallInThisDirection
        (MazeNode::WallDirection::NORTH))
    {
        northWall = true;
    }
    if(mazeGen.maze_node_look_up [xNodeCol][yNodeRow]->getWallInThisDirection
        (MazeNode::WallDirection::EAST))
    {
        eastWall = true;
    }
    if(mazeGen.maze_node_look_up [xNodeCol][yNodeRow]->getWallInThisDirection
        (MazeNode::WallDirection::SOUTH))
    {
        southWall = true;
    }
    if(mazeGen.maze_node_look_up [xNodeCol][yNodeRow]->getWallInThisDirection
        (MazeNode::WallDirection::WEST))
    {
        westWall = true;
    }
    
    //if there is a north wall and south wall
    if(northWall && southWall)
    {
        //take rows out from each side
        
        //number of times to reduce rows
        //Based on difference between base number of rows and pseudo number of rows
        std::int8_t numReductionRows = baseNumRows - pseudoRandNumRows;
        
        if(numReductionRows == 0)
        {
            //just set walls on top side and bottom side
            thisLabyrinthNode.setWallTopSide();
            thisLabyrinthNode.setWallBottomSide();
        }
        else
        {
            //count of reductions
            std::int8_t countReduction = 0;
            
            //variable for south row to reduce
            //initialize at very bottom row
            size_t southRowToReduce = baseNumRows - 1;
            //variable for north row to reduce
            //initialize at very top row
            size_t northRowToReduce = 0;
            
            while(countReduction <= numReductionRows)
            {
                //reduce south side first
                thisLabyrinthNode.setInvisibleWallOnThisRow(southRowToReduce);
                //increment reduction count
                countReduction++;
                
                //if reduction count is equal to number of rows to reduce
                if(countReduction == numReductionRows)
                {
                    southRowToReduce--; //decrement south row to reduce
                    //set bottom wall at new south row
                    thisLabyrinthNode.setBottomWallOnThisRow(southRowToReduce);
                    //set top wall at current north row
                    thisLabyrinthNode.setTopWallOnThisRow(northRowToReduce);
                    //end the loop
                    break;
                }
                // else reduce north side
                else
                {
                    //reduce north side
                    thisLabyrinthNode.setInvisibleWallOnThisRow(northRowToReduce);
                    //increment reduction count
                    countReduction++;
                    
                    //if reduction count is equal to number of rows to reduce
                    if(countReduction == numReductionRows)
                    {
                        northRowToReduce++; //decrement south row to reduce
                        //set top wall at new north row
                        thisLabyrinthNode.setBottomWallOnThisRow(southRowToReduce);
                        //set top wall at current north row
                        thisLabyrinthNode.setTopWallOnThisRow(northRowToReduce);
                        //end the loop
                        break;
                    }
                    //else decrement south row and increment north row
                    else{southRowToReduce--; northRowToReduce++;}
                }
            }
        }
        
    }
    //else if only north wall
    else if(northWall)
    {
        //take rows out from only north
        
        //number of times to reduce rows
        //Based on difference between base number of rows and pseudo number of rows
        std::int8_t numReductionRows = baseNumRows - pseudoRandNumRows;
        
        if(numReductionRows == 0)
        {
            //just set wall on top side 
            thisLabyrinthNode.setWallTopSide();
        }
        else
        {
            //count of reductions
            std::int8_t countReduction = 0;

            //variable for north row to reduce
            //initialize at very top row
            size_t northRowToReduce = 0;
            
            while(countReduction <= numReductionRows)
            {
                //reduce north side 
                thisLabyrinthNode.setInvisibleWallOnThisRow(northRowToReduce);
                //increment reduction count
                countReduction++;
                
                //if reduction count is equal to number of rows to reduce
                if(countReduction == numReductionRows)
                {
                    northRowToReduce++; //increment north row to reduce
                    //set top wall at new north row
                    thisLabyrinthNode.setTopWallOnThisRow(northRowToReduce);
                    //end the loop
                    break;
                }
                //else increment north row to reduce
                else{northRowToReduce++;}
            }
        }
    }
    //else if only south wall
    else if(southWall)
    {
        //take rows out from only south
        
        //number of times to reduce rows
        //Based on difference between base number of rows and pseudo number of rows
        std::int8_t numReductionRows = baseNumRows - pseudoRandNumRows;
        
        if(numReductionRows == 0)
        {
            //just set walls on  bottom side
            thisLabyrinthNode.setWallBottomSide();
        }
        else
        {
            //count of reductions
            std::int8_t countReduction = 0;

            //variable for south row to reduce
            //initialize at very bottom row
            size_t southRowToReduce = baseNumRows - 1;
            
            while(countReduction <= numReductionRows)
            {
                //reduce north side 
                thisLabyrinthNode.setInvisibleWallOnThisRow(southRowToReduce);
                //increment reduction count
                countReduction++;
                
                //if reduction count is equal to number of rows to reduce
                if(countReduction == numReductionRows)
                {
                    southRowToReduce--; //decrement south row to reduce
                    //set top wall at new north row
                    thisLabyrinthNode.setBottomWallOnThisRow(southRowToReduce);
                    //end the loop
                        break;
                }
                //else increment north row to reduce
                else{southRowToReduce--;}
            }
        }
    }
    
    //if there is a east wall and west wall
    if(eastWall && westWall)
    {
        //take rows out from each side
        
        //number of times to reduce rows
        //Based on difference between base number of rows and pseudo number of rows
        std::int8_t numReductionColumns = baseNumColumns - pseudoRandNumColumns;
        
        if(numReductionColumns == 0)
        {
            //just set walls on top side and bottom side
            thisLabyrinthNode.setWallLeftSide();
            thisLabyrinthNode.setWallRightSide();
        }
        else
        {
            //count of reductions
            std::int8_t countReduction = 0;
            
            //variable for south row to reduce
            //initialize at very bottom row
            size_t eastRowToReduce = baseNumColumns - 1;
            //variable for north row to reduce
            //initialize at very top row
            size_t westRowToReduce = 0;
            
            while(countReduction <= numReductionColumns)
            {
                //reduce east side first
                thisLabyrinthNode.setInvisibleWallOnThisColumn(eastRowToReduce);
                //increment reduction count
                countReduction++;
                
                //if reduction count is equal to number of rows to reduce
                if(countReduction == numReductionColumns)
                {
                    eastRowToReduce--; //decrement east row to reduce
                    //set east wall at new east row
                    thisLabyrinthNode.setRightWallOnThisColumn(eastRowToReduce);
                    //set west wall at current west row
                    thisLabyrinthNode.setLeftWallOnThisColumn(westRowToReduce);
                    //end the loop
                        break;
                }
                // else reduce west side
                else
                {
                    //reduce west side
                    thisLabyrinthNode.setInvisibleWallOnThisColumn(westRowToReduce);
                    //increment reduction count
                    countReduction++;
                    
                    //if reduction count is equal to number of rows to reduce
                    if(countReduction == numReductionColumns)
                    {
                        westRowToReduce++; //decrement south row to reduce
                        //set east wall at current east row
                        thisLabyrinthNode.setRightWallOnThisColumn(eastRowToReduce);
                        //set west wall at new west row
                        thisLabyrinthNode.setLeftWallOnThisColumn(westRowToReduce);
                        //end the loop
                        break;
                    }
                    //else decrement east row and increment west row
                    else{eastRowToReduce--; westRowToReduce++;}
                }
            }
        }
        
    }
    //else if only west wall
    else if(westWall)
    {
        //take rows out from only north
        
        //number of times to reduce rows
        //Based on difference between base number of rows and pseudo number of rows
        std::int8_t numReductionColumns = baseNumColumns - pseudoRandNumColumns;
        
        if(numReductionColumns == 0)
        {
            //just set wall on top side 
            thisLabyrinthNode.setWallLeftSide();
        }
        else
        {
            //count of reductions
            std::int8_t countReduction = 0;

            //variable for north row to reduce
            //initialize at very top row
            size_t westRowToReduce = 0;
            
            while(countReduction <= numReductionColumns)
            {
                //reduce north side 
                thisLabyrinthNode.setInvisibleWallOnThisColumn(westRowToReduce);
                //increment reduction count
                countReduction++;
                
                //if reduction count is equal to number of rows to reduce
                if(countReduction == numReductionColumns)
                {
                    westRowToReduce++; //increment north row to reduce
                    //set top wall at new north row
                    thisLabyrinthNode.setLeftWallOnThisColumn(westRowToReduce);
                    //end the loop
                        break;
                }
                //else increment north row to reduce
                else{westRowToReduce++;}
            }
        }
    }
    //else if only south wall
    else if(eastWall)
    {
        //take rows out from only south
        
        //number of times to reduce rows
        //Based on difference between base number of rows and pseudo number of rows
        std::int8_t numReductionColumns = baseNumColumns - pseudoRandNumColumns;
        
        if(numReductionColumns == 0)
        {
            //just set walls on  bottom side
            thisLabyrinthNode.setWallRightSide();
        }
        else
        {
            //count of reductions
            std::int8_t countReduction = 0;

            //variable for south row to reduce
            //initialize at very bottom row
            size_t eastRowToReduce = baseNumColumns - 1;
            
            while(countReduction <= numReductionColumns)
            {
                //reduce north side 
                thisLabyrinthNode.setInvisibleWallOnThisColumn(eastRowToReduce);
                //increment reduction count
                countReduction++;
                
                //if reduction count is equal to number of rows to reduce
                if(countReduction == numReductionColumns)
                {
                    eastRowToReduce--; //decrement south row to reduce
                    //set top wall at new north row
                    thisLabyrinthNode.setRightWallOnThisColumn(eastRowToReduce);
                    //end the loop
                        break;
                }
                //else increment north row to reduce
                else{eastRowToReduce--;}
            }
        }
    }
}


void Labyrinth::setupLabyrinthDoors(RNGType& rngSeed,
                                    std::vector <LabyrinthNode> &labyrinthNodesVector,
                                    LTexture& keyTexture,
                                    ALuint& keySource,
                                    ALuint& keyBuffer,
                                    LTexture& doorTexture,
                                    ALuint& doorSource,
                                    ALuint& doorOpenSound,
                                    ALuint& doorFailSound,
                                    std::vector <SDL_Rect> *doorClips)
{
    
    //maze node
    size_t xCol = 0; size_t yRow = 0;
    size_t endRow = mazeGen.numberXNodeColumns - 1;
    size_t endCol = mazeGen.numberYNodeRows - 1;
    
    size_t iteratorLabyrinthNode = 0;
    
    //number of doors
    std::int8_t numDoors = 1;
    std::int8_t numKeys = 0;
    
    std::int8_t limit_numDoorsInMap = labyrinthNodesVector.size() / 3;
    std::int8_t count_doors = 0;
    
   //Setup RNG
    std::array <double,4> probabilitiesDirection;
    probabilitiesDirection = {0.3, 0.2,0.3,0.4}; // No Door, Yes Door, No Door, No Door
        
    //setup rng with set probablities    
    boost::random::discrete_distribution <int> distDirection(probabilitiesDirection);
    boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > Die(rngSeed,distDirection);

    bool quit = false;
    
    //for each dungeon node
    while(!quit)
    {
        //if maze node pointer element is not nullptr 
        if(mazeGen.maze_node_look_up [xCol][yRow] != nullptr)
        {
            //if maze node is not in exit maze node
            if(xCol != exitCol && yRow != exitRow)
            {
                //if count of doors is less than limit of doors in map
                if(count_doors < limit_numDoorsInMap)
                {
                    //if die is 1, yes door
                    if(Die() == 1)
                    {
                        //setup doors and keys
                        labyrinthNodesVector[iteratorLabyrinthNode].setupDoorsAndKeys(
                                        numDoors,
                                        numKeys,
                                        keyTexture,
                                        keySource,
                                        keyBuffer,
                                        doorTexture,
                                        doorSource,
                                        doorOpenSound,
                                        doorFailSound,
                                        doorClips);
                                        
                        //place doors in dungeon node
                        labyrinthNodesVector[iteratorLabyrinthNode].placeDungeonDoors(rngSeed);
                        //increment count of dungeon dor
                        count_doors++;
                        
                    }
                    
                    //increment iterator dungeon node
                    iteratorLabyrinthNode++;
                    //reset if past last element
                    if(iteratorLabyrinthNode >= labyrinthNodesVector.size()){iteratorLabyrinthNode = 0;}
                }
                //else quit
                else{quit = true;}
            }
        }
        
        //if reached last element of maze node vector of maze gen
        //restart
        if(xCol == endCol && yRow == endRow){xCol = 0; yRow = 0;}
        
        //increment x column
        xCol++;
        //increment y row if at end col, restart xcol
        if(xCol > endCol){xCol = 0; yRow++;}
    }
}


void Labyrinth::setTimerPointer(LTimer* timer){labyrinthTimer = timer;}
void Labyrinth::setPointerToMainDot(Dot* mainDot){mainDotPointer = mainDot;}
void Labyrinth::setPointerToPlayerManager(PlayerManager* pm){m_player_manager_ptr = pm;}

void Labyrinth::setPointersToMedia(LTexture* tileMap,ALuint* source,ALuint* buffer)
{
    tileTextureMap = tileMap;
    dgmSource = source;
    dgmBuffer = buffer;
}

void Labyrinth::setupDotInLabyrinth(std::int16_t& screenWidth, std::int16_t& screenHeight, RNGType& rngSeed)
{
    if(m_player_manager_ptr)
    {
		labyrinthMap.setLabyrinthCameraForDot(m_player_manager_ptr->GetPointerToPlayerOne(),
                                            screenWidth,screenHeight);
        
        Labyrinth::randomlyPlaceDotInMazeNode(m_player_manager_ptr->GetPointerToPlayerOne(),rngSeed);
                                            
		if(m_player_manager_ptr->GetMultiplePlayersBool())
		{
			int num_players = m_player_manager_ptr->GetNumberOfPlayers();
			
			if(num_players > 1)
			{
				labyrinthMap.setLabyrinthCameraForDot(m_player_manager_ptr->GetPointerToPlayerTwo(),
                                            screenWidth,screenHeight);
                                            
				Labyrinth::randomlyPlaceDotInMazeNode(m_player_manager_ptr->GetPointerToPlayerTwo(),rngSeed);
			}
			else
			{
				std::cout << "Player2 ptr null!\n";
			}
			
			
			if(num_players > 2)
			{
				labyrinthMap.setLabyrinthCameraForDot(m_player_manager_ptr->GetPointerToPlayerThree(),
                                            screenWidth,screenHeight);
                                            
				Labyrinth::randomlyPlaceDotInMazeNode(m_player_manager_ptr->GetPointerToPlayerThree(),rngSeed);
			}
			else
			{
				std::cout << "Player3 ptr null!\n";
			}
			
			
			if(num_players > 3)
			{
				labyrinthMap.setLabyrinthCameraForDot(m_player_manager_ptr->GetPointerToPlayerFour(),
                                            screenWidth,screenHeight);
                                            
				Labyrinth::randomlyPlaceDotInMazeNode(m_player_manager_ptr->GetPointerToPlayerFour(),rngSeed);
			}
			else
			{
				std::cout << "Player4 ptr null!\n";
			}
			
		}
	}
	
    
}

void Labyrinth::setupDotInLabyrinth_Debug(Dot* thisDot,std::int16_t& screenWidth, std::int16_t& screenHeight,RNGType& rngSeed)
{
	labyrinthMap.setLabyrinthCameraForDot(thisDot,
                                            screenWidth,screenHeight);
        
    Labyrinth::randomlyPlaceDotInMazeNode(thisDot,rngSeed);
}

void Labyrinth::handle_events(Event& thisEvent)
{
    if( thisEvent.event_id == Event_ID::QUIT_WINDOW || thisEvent.event_id == Event_ID::ESCAPE )
    {
        Labyrinth::setState(GameState::State::PAUSE);
    }
    
    if(m_player_manager_ptr)
    {
		
		PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
		m_player_manager_ptr->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);
		
		if(p1_loc == PlayerManager::PlayerLocation::LABYRINTH && thisEvent.player_num == 1)
		{
			labyrinthMap.door_handle_events(thisEvent,m_player_manager_ptr->GetPointerToCameraOne());
		}
		
		if(m_player_manager_ptr->GetMultiplePlayersBool())
		{
			int num_players = m_player_manager_ptr->GetNumberOfPlayers();
			
			if(num_players > 1 && p2_loc == PlayerManager::PlayerLocation::LABYRINTH
				&& thisEvent.player_num == 2)
			{
				labyrinthMap.door_handle_events(thisEvent,m_player_manager_ptr->GetPointerToCameraTwo());
			}
			
			if(num_players > 2 && p3_loc == PlayerManager::PlayerLocation::LABYRINTH
				&& thisEvent.player_num == 3)
			{
				labyrinthMap.door_handle_events(thisEvent,m_player_manager_ptr->GetPointerToCameraThree());
			}
			
			if(num_players > 3 && p4_loc == PlayerManager::PlayerLocation::LABYRINTH 
				&& thisEvent.player_num == 4)
			{
				labyrinthMap.door_handle_events(thisEvent,m_player_manager_ptr->GetPointerToCameraFour());
			}
		}
		
	}
    
}

void Labyrinth::handle_events_RNG(RNGType& rngSeed)
{
    
    if(m_player_manager_ptr)
    {
		PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
		m_player_manager_ptr->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);
		
		if(p1_loc == PlayerManager::PlayerLocation::LABYRINTH)
		{
			m_enemy_inventory.run_enemies_handle_events(rngSeed, *m_player_manager_ptr->GetPointerToCameraOne());
		}
		
		if(m_player_manager_ptr->GetMultiplePlayersBool())
		{
			int num_players = m_player_manager_ptr->GetNumberOfPlayers();
			
			if(num_players > 1 && p2_loc == PlayerManager::PlayerLocation::LABYRINTH)
			{
				m_enemy_inventory.run_enemies_handle_events(rngSeed, *m_player_manager_ptr->GetPointerToCameraTwo());
			}
			
			if(num_players > 2 && p3_loc == PlayerManager::PlayerLocation::LABYRINTH)
			{
				m_enemy_inventory.run_enemies_handle_events(rngSeed, *m_player_manager_ptr->GetPointerToCameraThree());
			}
			
			if(num_players > 3 && p4_loc == PlayerManager::PlayerLocation::LABYRINTH)
			{
				m_enemy_inventory.run_enemies_handle_events(rngSeed, *m_player_manager_ptr->GetPointerToCameraFour());
			}
		}
		
	}
    
    
}


void Labyrinth::logic()
{
    //create timestep for moving objects
    float timeStep = labyrinthTimer->getTicks() / 1000.f; //frame rate
    
    Labyrinth::logic_alt(timeStep);
    
    //Restart timer
    labyrinthTimer->start();
}

void Labyrinth::logic_alt(float& timeStep)
{
	int num_players = m_player_manager_ptr->GetNumberOfPlayers();
    
    //logic for player
    if(m_player_manager_ptr != nullptr)
    {
		PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
		m_player_manager_ptr->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);
		        
        //if main player collides with exit tile
        if( checkCollision(exitTile->getBox(),m_player_manager_ptr->GetPointerToPlayerOne()->getCollisionBox() ) 
			&& p1_loc == PlayerManager::PlayerLocation::LABYRINTH)
        {
			if(m_player_manager_ptr->GetPointerToPlayerOne()->getHealth() > 1)
			{
				m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::LABYRINTH_2_WINNER_ROOM,1); 
			}
			//Labyrinth::setPlayerHitLabyrinthExitBool(true,1);
		}
		
		if(num_players > 1 && checkCollision(exitTile->getBox(),m_player_manager_ptr->GetPointerToPlayerTwo()->getCollisionBox() ) 
			&& p2_loc == PlayerManager::PlayerLocation::LABYRINTH)
		{
			if(m_player_manager_ptr->GetPointerToPlayerTwo()->getHealth() > 1)
			{
				m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::LABYRINTH_2_WINNER_ROOM,2); 
			}
			//Labyrinth::setPlayerHitLabyrinthExitBool(true,2);
		}
		
		if(num_players > 2 && checkCollision(exitTile->getBox(),m_player_manager_ptr->GetPointerToPlayerThree()->getCollisionBox() ) 
			&& p3_loc == PlayerManager::PlayerLocation::LABYRINTH)
		{
			if(m_player_manager_ptr->GetPointerToPlayerThree()->getHealth() > 1)
			{
				m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::LABYRINTH_2_WINNER_ROOM,3); 
			}
			//Labyrinth::setPlayerHitLabyrinthExitBool(true,3);
		}
		
		if(num_players > 3 && checkCollision(exitTile->getBox(),m_player_manager_ptr->GetPointerToPlayerFour()->getCollisionBox() ) 
			&& p4_loc == PlayerManager::PlayerLocation::LABYRINTH)
		{
			if(m_player_manager_ptr->GetPointerToPlayerFour()->getHealth() > 1)
			{
				m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::LABYRINTH_2_WINNER_ROOM,4);
			}
			 
		}
        
        Labyrinth::DungeonEntranceHitOperations();
        
       
        
        //move main dot within dungeon map
		if(p1_loc == PlayerManager::PlayerLocation::LABYRINTH)
		{
			labyrinthMap.moveMainDot(m_player_manager_ptr->GetPointerToPlayerOne(),timeStep,m_player_manager_ptr->GetPointerToCameraOne());
		}
		
		if(m_player_manager_ptr->GetMultiplePlayersBool())
		{
			if(num_players > 1 && p2_loc == PlayerManager::PlayerLocation::LABYRINTH)
			{
				labyrinthMap.moveMainDot(m_player_manager_ptr->GetPointerToPlayerTwo(),timeStep,m_player_manager_ptr->GetPointerToCameraTwo());
			}
			if(num_players > 2 && p3_loc == PlayerManager::PlayerLocation::LABYRINTH)
			{
				labyrinthMap.moveMainDot(m_player_manager_ptr->GetPointerToPlayerThree(),timeStep,m_player_manager_ptr->GetPointerToCameraThree());
			}
			if(num_players > 3 && p4_loc == PlayerManager::PlayerLocation::LABYRINTH)
			{
				labyrinthMap.moveMainDot(m_player_manager_ptr->GetPointerToPlayerFour(),timeStep,m_player_manager_ptr->GetPointerToCameraFour());
			}
			
			
		}
		
		
		//push back dot if collide with door
		if(p1_loc == PlayerManager::PlayerLocation::LABYRINTH )
		{
			labyrinthMap.doorToDot_Logic(m_player_manager_ptr->GetPointerToPlayerOne(),timeStep,m_player_manager_ptr->GetPointerToCameraOne());
		}
		
		if(m_player_manager_ptr->GetMultiplePlayersBool())
		{
			if(num_players > 1 && p2_loc == PlayerManager::PlayerLocation::LABYRINTH)
			{
				labyrinthMap.doorToDot_Logic(m_player_manager_ptr->GetPointerToPlayerTwo(),timeStep,m_player_manager_ptr->GetPointerToCameraTwo());
			}
			if(num_players > 2 && p3_loc == PlayerManager::PlayerLocation::LABYRINTH)
			{
				labyrinthMap.doorToDot_Logic(m_player_manager_ptr->GetPointerToPlayerThree(),timeStep,m_player_manager_ptr->GetPointerToCameraThree());
			}
			if(num_players > 3 && p4_loc == PlayerManager::PlayerLocation::LABYRINTH)
			{
				labyrinthMap.doorToDot_Logic(m_player_manager_ptr->GetPointerToPlayerFour(),timeStep,m_player_manager_ptr->GetPointerToCameraFour());
			}
			
		}
		
		//move enemies 
		if(p1_loc == PlayerManager::PlayerLocation::LABYRINTH)
		{
			m_enemy_inventory.run_enemies_logic(timeStep,*m_player_manager_ptr->GetPointerToCameraOne(), 
							labyrinthMap.labyrinthTilesVector);
		}
							
		if(m_player_manager_ptr->GetMultiplePlayersBool())
		{
			if(num_players > 1 && p2_loc == PlayerManager::PlayerLocation::LABYRINTH)
			{
				m_enemy_inventory.run_enemies_logic(timeStep,*m_player_manager_ptr->GetPointerToCameraTwo(), 
							labyrinthMap.labyrinthTilesVector);
			}
			
			if(num_players > 2  && p3_loc == PlayerManager::PlayerLocation::LABYRINTH)
			{
				m_enemy_inventory.run_enemies_logic(timeStep,*m_player_manager_ptr->GetPointerToCameraThree(), 
							labyrinthMap.labyrinthTilesVector);
			}
			
			if(num_players > 3 && p4_loc == PlayerManager::PlayerLocation::LABYRINTH)
			{
				m_enemy_inventory.run_enemies_logic(timeStep,*m_player_manager_ptr->GetPointerToCameraFour(), 
							labyrinthMap.labyrinthTilesVector);
			}
			
		}
		
		//check for and remove dead enemeies
		if(p1_loc == PlayerManager::PlayerLocation::LABYRINTH)
		{
			m_enemy_inventory.checkAndRemoveDeadEnemies(*m_player_manager_ptr->GetPointerToCameraOne());
		}
		
		if(m_player_manager_ptr->GetMultiplePlayersBool())
		{
			if(num_players > 1 && p2_loc == PlayerManager::PlayerLocation::LABYRINTH)
			{
				m_enemy_inventory.checkAndRemoveDeadEnemies(*m_player_manager_ptr->GetPointerToCameraTwo());
			}
			
			if(num_players > 2 && p3_loc == PlayerManager::PlayerLocation::LABYRINTH)
			{
				m_enemy_inventory.checkAndRemoveDeadEnemies(*m_player_manager_ptr->GetPointerToCameraThree());
			}
			
			if(num_players > 3 && p4_loc == PlayerManager::PlayerLocation::LABYRINTH)
			{
				m_enemy_inventory.checkAndRemoveDeadEnemies(*m_player_manager_ptr->GetPointerToCameraFour());
			}
			
		}
        
    }
}


void Labyrinth::render(SDL_Renderer* gRenderer)
{
    //render tiles in map
    labyrinthMap.renderTiles(gRenderer,tileTextureMap);
    
    //render doors
    labyrinthMap.renderDoors(gRenderer);
    
    //render enemies
    m_enemy_inventory.run_enemies_render(*labyrinthCamera,gRenderer );
    
    //render weapons
    m_game_inventory_ptr->run_weapons_render(gRenderer,*labyrinthCamera);
    
    //if debug bool is on
    if(Labyrinth::getDebugBool())
    {
        Labyrinth::renderMazeGeneration(gRenderer);
        Labyrinth::renderDotInMazeGeneration(gRenderer);
        Labyrinth::renderExitInMazeGeneration(gRenderer);
    }
    
    //render dot
    labyrinthMap.renderDotInLabyrinthMap(gRenderer,mainDotPointer,labyrinthCamera);
}

void Labyrinth::render(DrawingManager* gDrawManager)
{
	int num_players = gDrawManager->GetNumberOfPlayers();
	
	//render tiles in map
    labyrinthMap.renderTiles(m_player_manager_ptr,gDrawManager,tileTextureMap);
    
    //render doors
    labyrinthMap.renderDoors(m_player_manager_ptr,gDrawManager);
    
    PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
	m_player_manager_ptr->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);
    
    if(p1_loc == PlayerManager::PlayerLocation::LABYRINTH)
    {
		 //render enemies
		gDrawManager->SetToRenderViewPortPlayer1();
		m_enemy_inventory.run_enemies_render(*gDrawManager->GetPointerToCameraOne(),gDrawManager->GetPointerToRenderer() );
	}
    
    if(gDrawManager->GetMultiplePlayersBool())
    {
		if(num_players > 1  && p2_loc == PlayerManager::PlayerLocation::LABYRINTH)
		{
			gDrawManager->SetToRenderViewPortPlayer2();
			m_enemy_inventory.run_enemies_render(*gDrawManager->GetPointerToCameraTwo(),gDrawManager->GetPointerToRenderer() );
			
		}
		
		if(num_players > 2 && p3_loc == PlayerManager::PlayerLocation::LABYRINTH)
		{
			gDrawManager->SetToRenderViewPortPlayer3();
			m_enemy_inventory.run_enemies_render(*gDrawManager->GetPointerToCameraThree(),gDrawManager->GetPointerToRenderer() );
		}
		
		if(num_players > 3 && p4_loc == PlayerManager::PlayerLocation::LABYRINTH)
		{
			gDrawManager->SetToRenderViewPortPlayer4();
			m_enemy_inventory.run_enemies_render(*gDrawManager->GetPointerToCameraFour(),gDrawManager->GetPointerToRenderer() );
		}
	}
				
    //render weapons
    
    if(p1_loc == PlayerManager::PlayerLocation::LABYRINTH)
    {
		gDrawManager->SetToRenderViewPortPlayer1();
		m_game_inventory_ptr->run_weapons_render(gDrawManager->GetPointerToRenderer(),*gDrawManager->GetPointerToCameraOne());
	}
    
    if(gDrawManager->GetMultiplePlayersBool())
    {
		if(num_players > 1 && p2_loc == PlayerManager::PlayerLocation::LABYRINTH)
		{
			gDrawManager->SetToRenderViewPortPlayer2();
			m_game_inventory_ptr->run_weapons_render(gDrawManager->GetPointerToRenderer(),*gDrawManager->GetPointerToCameraTwo());
		}
		
		if(num_players > 2 && p3_loc == PlayerManager::PlayerLocation::LABYRINTH)
		{
			gDrawManager->SetToRenderViewPortPlayer3();
			m_game_inventory_ptr->run_weapons_render(gDrawManager->GetPointerToRenderer(),*gDrawManager->GetPointerToCameraThree());
			
		}
		
		if(num_players > 3 && p4_loc == PlayerManager::PlayerLocation::LABYRINTH)
		{
			gDrawManager->SetToRenderViewPortPlayer4();
			m_game_inventory_ptr->run_weapons_render(gDrawManager->GetPointerToRenderer(),*gDrawManager->GetPointerToCameraFour());
		}
		
	}
    
    //if debug bool is on
    if(Labyrinth::getDebugBool())
    {
        Labyrinth::renderMazeGeneration(gDrawManager->GetPointerToRenderer());
        Labyrinth::renderDotInMazeGeneration(gDrawManager->GetPointerToRenderer());
        Labyrinth::renderExitInMazeGeneration(gDrawManager->GetPointerToRenderer());
    }
    
    //render dot
    
    //render players
    if(m_player_manager_ptr)
    {
		bool player1_active = false;
		bool player2_active = false;
		bool player3_active = false;
		bool player4_active = false;
		

		if(m_player_manager_ptr->GetPointerToPlayerOne())
		{
			if(m_player_manager_ptr->GetPointerToPlayerOne()->getHealth() > 0
				&& p1_loc == PlayerManager::PlayerLocation::LABYRINTH)
			{
				player1_active = true;
			}
		}
		
		if(m_player_manager_ptr->GetPointerToPlayerTwo())
		{
			if(m_player_manager_ptr->GetPointerToPlayerTwo()->getHealth() > 0
				&& p2_loc == PlayerManager::PlayerLocation::LABYRINTH)
			{
				player2_active = true;
			}
		}
		
		if(m_player_manager_ptr->GetPointerToPlayerThree())
		{
			if(m_player_manager_ptr->GetPointerToPlayerThree()->getHealth() > 0
			&& p3_loc == PlayerManager::PlayerLocation::LABYRINTH)
			{
				player3_active = true;
			}
		}
		
		if(m_player_manager_ptr->GetPointerToPlayerFour())
		{
			if(m_player_manager_ptr->GetPointerToPlayerFour()->getHealth() > 0
			&& p4_loc == PlayerManager::PlayerLocation::LABYRINTH)
			{
				player4_active = true;
			}
		}
		
		if(player1_active)
		{
			gDrawManager->SetToRenderViewPortPlayer1();
			labyrinthMap.renderDotInLabyrinthMap(gDrawManager->GetPointerToRenderer(),
											m_player_manager_ptr->GetPointerToPlayerOne(),
											m_player_manager_ptr->GetPointerToCameraOne());
											
			if(player2_active)
			{
				//render player 2 in player 1 viewport
				gDrawManager->SetToRenderViewPortPlayer1();
				labyrinthMap.renderDotInLabyrinthMap(gDrawManager->GetPointerToRenderer(),
												m_player_manager_ptr->GetPointerToPlayerTwo(),
												m_player_manager_ptr->GetPointerToCameraOne());
			}
			
			if(player3_active)
			{
				//render player 3 in player 1 viewport
				gDrawManager->SetToRenderViewPortPlayer1();
				labyrinthMap.renderDotInLabyrinthMap(gDrawManager->GetPointerToRenderer(),
												m_player_manager_ptr->GetPointerToPlayerThree(),
												m_player_manager_ptr->GetPointerToCameraOne());
			}
			
			if(player4_active)
			{
				//render player 4 in player 1 viewport
				gDrawManager->SetToRenderViewPortPlayer1();
				labyrinthMap.renderDotInLabyrinthMap(gDrawManager->GetPointerToRenderer(),
												m_player_manager_ptr->GetPointerToPlayerFour(),
												m_player_manager_ptr->GetPointerToCameraOne());
			}
		}
										
		if(player2_active)
		{
			//render player 2 in player 2 view port										
			gDrawManager->SetToRenderViewPortPlayer2();
			labyrinthMap.renderDotInLabyrinthMap(gDrawManager->GetPointerToRenderer(),
												m_player_manager_ptr->GetPointerToPlayerTwo(),
												m_player_manager_ptr->GetPointerToCameraTwo());
			
			if(player1_active)
			{
													
				//render player 1 in player 2 viewport
				gDrawManager->SetToRenderViewPortPlayer2();
				labyrinthMap.renderDotInLabyrinthMap(gDrawManager->GetPointerToRenderer(),
													m_player_manager_ptr->GetPointerToPlayerOne(),
													m_player_manager_ptr->GetPointerToCameraTwo());
				
			}
			
			if(player3_active)
			{
													
				//render player 3 in player 2 viewport
				gDrawManager->SetToRenderViewPortPlayer2();
				labyrinthMap.renderDotInLabyrinthMap(gDrawManager->GetPointerToRenderer(),
													m_player_manager_ptr->GetPointerToPlayerThree(),
													m_player_manager_ptr->GetPointerToCameraTwo());
				
			}	
			
			if(player4_active)
			{
													
				//render player 4 in player 2 viewport
				gDrawManager->SetToRenderViewPortPlayer2();
				labyrinthMap.renderDotInLabyrinthMap(gDrawManager->GetPointerToRenderer(),
													m_player_manager_ptr->GetPointerToPlayerFour(),
													m_player_manager_ptr->GetPointerToCameraTwo());
				
			}					
			
			
		}
		
		if(player3_active)
		{
			//render player 3 in player 3 view port										
			gDrawManager->SetToRenderViewPortPlayer3();
			labyrinthMap.renderDotInLabyrinthMap(gDrawManager->GetPointerToRenderer(),
												m_player_manager_ptr->GetPointerToPlayerThree(),
												m_player_manager_ptr->GetPointerToCameraThree());
			
			if(player1_active)
			{
													
				//render player 1 in player 3 viewport
				gDrawManager->SetToRenderViewPortPlayer3();
				labyrinthMap.renderDotInLabyrinthMap(gDrawManager->GetPointerToRenderer(),
													m_player_manager_ptr->GetPointerToPlayerOne(),
													m_player_manager_ptr->GetPointerToCameraThree());
				
			}
			
			if(player2_active)
			{
													
				//render player 2 in player 3 viewport
				gDrawManager->SetToRenderViewPortPlayer3();
				labyrinthMap.renderDotInLabyrinthMap(gDrawManager->GetPointerToRenderer(),
													m_player_manager_ptr->GetPointerToPlayerTwo(),
													m_player_manager_ptr->GetPointerToCameraThree());
				
			}	
			
			if(player4_active)
			{
													
				//render player 4 in player 3 viewport
				gDrawManager->SetToRenderViewPortPlayer3();
				labyrinthMap.renderDotInLabyrinthMap(gDrawManager->GetPointerToRenderer(),
													m_player_manager_ptr->GetPointerToPlayerFour(),
													m_player_manager_ptr->GetPointerToCameraThree());
				
			}					
			
			
		}
		
		if(player4_active)
		{
			//render player 4 in player 4 view port										
			gDrawManager->SetToRenderViewPortPlayer4();
			labyrinthMap.renderDotInLabyrinthMap(gDrawManager->GetPointerToRenderer(),
												m_player_manager_ptr->GetPointerToPlayerFour(),
												m_player_manager_ptr->GetPointerToCameraFour());
			
			if(player1_active)
			{
													
				//render player 1 in player 4 viewport
				gDrawManager->SetToRenderViewPortPlayer4();
				labyrinthMap.renderDotInLabyrinthMap(gDrawManager->GetPointerToRenderer(),
													m_player_manager_ptr->GetPointerToPlayerOne(),
													m_player_manager_ptr->GetPointerToCameraFour());
				
			}
			
			if(player3_active)
			{
													
				//render player 3 in player 4 viewport
				gDrawManager->SetToRenderViewPortPlayer4();
				labyrinthMap.renderDotInLabyrinthMap(gDrawManager->GetPointerToRenderer(),
													m_player_manager_ptr->GetPointerToPlayerThree(),
													m_player_manager_ptr->GetPointerToCameraFour());
				
			}	
			
			if(player2_active)
			{
													
				//render player 4 in player 4 viewport
				gDrawManager->SetToRenderViewPortPlayer4();
				labyrinthMap.renderDotInLabyrinthMap(gDrawManager->GetPointerToRenderer(),
													m_player_manager_ptr->GetPointerToPlayerTwo(),
													m_player_manager_ptr->GetPointerToCameraFour());
				
			}					
			
			
		}
		
	}
    
    
}

void Labyrinth::renderMazeGeneration(SDL_Renderer* gRenderer)
{
    mazeGen.render(gRenderer);
}

void Labyrinth::renderNodeGeneration(SDL_Renderer* gRenderer)
{
    nodesGen.render(gRenderer);
}

void Labyrinth::renderDotInMazeGeneration(SDL_Renderer* gRenderer)
{
    if(mainDotPointer != nullptr)
    {
        unsigned int r = 200; unsigned int g = 0; unsigned int b = 0;
        
        size_t xColDot = mainDotPointer->getCollisionBox().x / NODE_LEVEL_WIDTH;
        size_t yRowDot = mainDotPointer->getCollisionBox().y / NODE_LEVEL_HEIGHT;
        mazeGen.renderSquareInMazeNode(gRenderer,xColDot,yRowDot,r,g,b);
    }
    
}

void Labyrinth::renderExitInMazeGeneration(SDL_Renderer* gRenderer)
{
     unsigned int r = 200; unsigned int g = 150; unsigned int b = 100;
     mazeGen.renderSquareInMazeNode(gRenderer,exitCol,exitRow,r,g,b);
}

void Labyrinth::sound(AudioRenderer* gAudioRenderer)
{
   //play dungeon music
    //play sound from dgmSource
    alGetSourcei(*dgmSource, AL_SOURCE_STATE, &musicState);
    //if music state is stopped or started, play it
    if(Labyrinth::getState() == GameState::State::RUNNING )
    {
        if (musicState == AL_STOPPED || musicState == AL_INITIAL){ alSourcePlay(*dgmSource);}
    }
    else{alSourceStop(*dgmSource);}

    //labyrinthMap.play_door_sounds();
        
    PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
	m_player_manager_ptr->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);
    
    if(p1_loc == PlayerManager::PlayerLocation::LABYRINTH)
    {
		SDL_Rect* thisCamera = m_player_manager_ptr->GetPointerToCameraOne();
		m_enemy_inventory.run_enemies_sound(*thisCamera,gAudioRenderer);
	}
    
    if(p2_loc == PlayerManager::PlayerLocation::LABYRINTH)
    {
		SDL_Rect* thisCamera = m_player_manager_ptr->GetPointerToCameraTwo();
		m_enemy_inventory.run_enemies_sound(*thisCamera,gAudioRenderer);
	}
	
	if(p3_loc == PlayerManager::PlayerLocation::LABYRINTH)
    {
		SDL_Rect* thisCamera = m_player_manager_ptr->GetPointerToCameraThree();
		m_enemy_inventory.run_enemies_sound(*thisCamera,gAudioRenderer);
	}
	
	if(p4_loc == PlayerManager::PlayerLocation::LABYRINTH)
    {
		SDL_Rect* thisCamera = m_player_manager_ptr->GetPointerToCameraFour();
		m_enemy_inventory.run_enemies_sound(*thisCamera,gAudioRenderer);
	}
    
    m_player_manager_ptr->sound(gAudioRenderer);
    
}

void Labyrinth::StopPlayingTheme()
{
	
    alSourceStop(*dgmSource);
}

void Labyrinth::freeResources()
{
    labyrinthMap.freeTiles();
    labyrinthMap.freeDoorsAndKeys();
    m_enemy_inventory.freeEnemyVector();
}

void Labyrinth::randomlyPlaceDotInMazeNode(Dot* thisDot,RNGType& rngSeed)
{
	//Setup RNG
	std::array <double,4> probabilitiesDirection;
	 
	probabilitiesDirection = {0.3, 0.4,0.2,0.4};
		
	//setup rng with set probablities    
	boost::random::discrete_distribution <int> distDirection(probabilitiesDirection);
	boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > DirectionDie(rngSeed,distDirection);
    
    double divider = 1.5;
    double prevDie = 0;
    
    for(size_t i = 0; i < 10; i++)
    {
		switch(DirectionDie())
		{
			case 0:{ divider += 0.014; divider -= prevDie; prevDie = 0.018; break;} 
			case 1:{ divider += 0.023; divider -= prevDie; prevDie = 0.01; break;} 
			case 2:{ divider += 0.031; divider -= prevDie; prevDie = 0.013; break;} 
			case 3:{ divider += 0.043; divider -= prevDie; prevDie = 0.022; break;} 
		}
	}
    
    
    
    size_t start = double( double(labyrinthMap.labyrinthTilesVector.size()) / divider);
    
    //1st maze node that isn't nullptr
    for(size_t i = start; i > 0; i--)
    {
        if(labyrinthMap.labyrinthTilesVector[i] != nullptr)
        {
            if(labyrinthMap.labyrinthTilesVector[i]->getTypeFloor())
            {
                float newX = labyrinthMap.labyrinthTilesVector[i]->getXPosition() + thisDot->getCollisionBox().w;
                float newY = labyrinthMap.labyrinthTilesVector[i]->getYPosition() + thisDot->getCollisionBox().h;
                thisDot->setPosX(newX);
                thisDot->setPosY(newY);
                
                //assign dot start tile to tile chosen
                dotStartTile = labyrinthMap.labyrinthTilesVector[i];
                break;
            }
        }
    }
}

void Labyrinth::randomlySetExitForMaze(RNGType& rngSeed)
{
    //if main dot pointer isn't nullptr
    if(mainDotPointer != nullptr)
    {
        //get dot position in maze
        std::int16_t dotScreenX = mainDotPointer->getCollisionBox().x;
        std::int16_t dotScreenY = mainDotPointer->getCollisionBox().y;
        
        double xColDot = size_t( dotScreenX / NODE_LEVEL_WIDTH );
        double yRowDot = size_t( dotScreenY / NODE_LEVEL_HEIGHT );
        
        //get number of columns and rows in maze
        size_t numXCol = mazeGen.numberXNodeColumns;
        size_t numYRow = mazeGen.numberYNodeRows;
        
        //setup distance exit should be from dot
        std::int16_t distanceBetweenDotAndExit =  (numXCol / 2) + (numYRow / 2) - (numYRow / 4) - (numXCol / 4);
        
        //Setup RNG
        std::array <double,4> probabilitiesDirection;
         
        probabilitiesDirection = {0.3, 0.4,0.2,0.4};
            
        //setup rng with set probablities    
        boost::random::discrete_distribution <int> distDirection(probabilitiesDirection);
        boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > DirectionDie(rngSeed,distDirection);

        
        
        double xCol = 1;
        double yRow = 1;
        double currentDistance = 0;
        double xDistance = 0;
        double yDistance = 0;
        bool quit = false;
        
        while(!quit)
        {
            xDistance = abs( xColDot - xCol );
            yDistance = abs( yRowDot - yRow );
            currentDistance = sqrt( pow(xDistance,2) + pow(yDistance,2) );
            
            if( currentDistance >= distanceBetweenDotAndExit
                &&
                mazeGen.maze_node_look_up [size_t(xCol)][size_t(yRow)] != nullptr)
            {
                exitCol = xCol;
                exitRow = yRow;
                quit = true;
            }
            
            probabilitiesDirection = {0.3, 0.4,0.2,0.4};
            
            //randomly choose which way to go
            switch(DirectionDie())
            {
                case 0:{ if(yRow > 0){yRow -= 1;}else{probabilitiesDirection[0] = 0;} break;} //go up
                case 1:{ if(xCol < numXCol - 1){xCol += 1;}else{probabilitiesDirection[1] = 0;} break;} //go right
                case 2:{ if(yRow < numYRow - 1){yRow += 1;}else{probabilitiesDirection[2] = 0;} break;} // go down
                case 3:{ if(xCol > 0){xCol -= 1;}else{probabilitiesDirection[3] = 0;} break;} // go left
            }
            
            //setup rng with set probablities    
            boost::random::discrete_distribution <int> distDirection(probabilitiesDirection);
            boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > DirectionDie(rngSeed,distDirection);
        }
        
        //starts at 5 tiles right and 5 tiles down from beginning tile of maze node 
        std::int16_t exitScreenX = (exitCol * NODE_LEVEL_WIDTH) + (5 * TILE_WIDTH);
        std::int16_t exitScreenY = exitRow * NODE_LEVEL_HEIGHT + (5 * TILE_HEIGHT);
        
        //look through all tiles for one that matches position
        for(size_t i = 0; i < labyrinthMap.labyrinthTilesVector.size(); ++i)
        {
            SDL_Rect tileBox = labyrinthMap.labyrinthTilesVector[i]->getBox();
            if(tileBox.x == exitScreenX && tileBox.y == exitScreenY)
            {
                labyrinthMap.labyrinthTilesVector[i]->setType(DungeonTile::TileType::EXIT);
                exitTile = labyrinthMap.labyrinthTilesVector[i];
            }
        }
    }
}

void Labyrinth::randomlySetDungeonEntrancesinMaze(RNGType& rngSeed, DungeonXMLRegistry* dungeon_xml_reg)
{
	//if main dot pointer isn't nullptr
    if(mainDotPointer != nullptr)
    {
		
		size_t numTotalEntries = dungeon_xml_reg->GetSizeOfDungeonXMLEntriesVector();
		
		//for each dungeon xml entry
		for(size_t iterator_entry = 0; iterator_entry < numTotalEntries; iterator_entry++)
		{
			bool entranceSet = false;
			
			while(!entranceSet)
			{
				 //get number of columns and rows in maze
				size_t numXCol = mazeGen.numberXNodeColumns;
				size_t numYRow = mazeGen.numberYNodeRows;
				
				//setup distance entrance should be from dot
				std::int16_t distanceBetweenDotAndEntrance =  (numXCol / 2) + (numYRow / 2) - (numYRow / 2) - (numXCol / 3);
				
				//Setup RNG
				std::array <double,4> probabilitiesDirection;
				 
				probabilitiesDirection = {0.3, 0.4,0.2,0.4};
					
				//setup rng with set probablities    
				boost::random::discrete_distribution <int> distDirection(probabilitiesDirection);
				boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > DirectionDie(rngSeed,distDirection);

				size_t xColDot = mainDotPointer->getCollisionBox().x / NODE_LEVEL_WIDTH;
				size_t yRowDot = mainDotPointer->getCollisionBox().y / NODE_LEVEL_HEIGHT;
				
				double xCol = 1;
				double yRow = 1;
				double currentDistance = 0;
				double xDistance = 0;
				double yDistance = 0;
				bool quit = false;
				
				while(!quit)
				{
					xDistance = abs( xColDot - xCol );
					yDistance = abs( yRowDot - yRow );
					currentDistance = sqrt( pow(xDistance,2) + pow(yDistance,2) );
					
					if( currentDistance >= distanceBetweenDotAndEntrance
						&&
						mazeGen.maze_node_look_up [size_t(xCol)][size_t(yRow)] != nullptr)
					{
						exitCol = xCol;
						exitRow = yRow;
						quit = true;
					}
					
					probabilitiesDirection = {0.3, 0.4,0.2,0.4};
					
					//randomly choose which way to go
					switch(DirectionDie())
					{
						case 0:{ if(yRow > 0){yRow -= 1;}else{probabilitiesDirection[0] = 0;} break;} //go up
						case 1:{ if(xCol < numXCol - 1){xCol += 1;}else{probabilitiesDirection[1] = 0;} break;} //go right
						case 2:{ if(yRow < numYRow - 1){yRow += 1;}else{probabilitiesDirection[2] = 0;} break;} // go down
						case 3:{ if(xCol > 0){xCol -= 1;}else{probabilitiesDirection[3] = 0;} break;} // go left
					}
					
					//setup rng with set probablities    
					boost::random::discrete_distribution <int> distDirection(probabilitiesDirection);
					boost::random::variate_generator <RNGType&, boost::random::discrete_distribution <> > DirectionDie(rngSeed,distDirection);
				}
				
				//starts at 5 tiles right and 5 tiles down from beginning tile of maze node 
				std::int16_t entranceScreenX = (xCol * NODE_LEVEL_WIDTH) + (1 * TILE_WIDTH);
				std::int16_t entranceScreenY = (yRow * NODE_LEVEL_HEIGHT) + (1 * TILE_HEIGHT);
				
				//look through all tiles for one that matches position
				for(size_t i = 0; i < labyrinthMap.labyrinthTilesVector.size(); ++i)
				{
					SDL_Rect tileBox = labyrinthMap.labyrinthTilesVector[i]->getBox();
					if(tileBox.x == entranceScreenX && tileBox.y == entranceScreenY)
					{
						DungeonTile* dungeonEntranceTile = labyrinthMap.labyrinthTilesVector[i];
						
						if(dungeonEntranceTile != exitTile)
						{
							dungeonEntranceTile->setType(DungeonTile::TileType::DUNGEON_ENTRANCE);
						
							DungeonEntrance entrance;
							
							entrance.tile_ptr = dungeonEntranceTile;
							entrance.xml_entry = dungeon_xml_reg->GetReferenceToDungeonXMLEntry(iterator_entry);
							
							dungeonEntrances.push_back(entrance);
							
							entranceSet = true;
							
						}
						
						
					}
				}
			}
			
			
		}
       
    }
}

void Labyrinth::randomlySetLabyrinthDoors(RNGType& rngSeed)
{
    labyrinthMap.randomlyPlaceLabyrinthDoors(rngSeed);
}

void Labyrinth::setDebugBool(bool state){debug = state;}
bool Labyrinth::getDebugBool(){return debug;}

void Labyrinth::placeEnemiesInLabyrinth(RNGType& rngSeed,
                                        std::vector <LabyrinthNode> &labyrinthNodes, 
                                        std::vector <Enemy*> &thisEnemiesVector)
{
    
    size_t startIterator = 0;
    size_t endIterator = 0;
    
    size_t iteratorIncrement; 
    size_t labyrinthNodeSize = labyrinthNodes.size();  
    size_t enemySize = thisEnemiesVector.size();
    
    if(enemySize > labyrinthNodeSize){iteratorIncrement = enemySize / labyrinthNodeSize;}
    else{iteratorIncrement = labyrinthNodeSize / enemySize;}
    
    if(iteratorIncrement == 0 ){iteratorIncrement = 1;}
    if(iteratorIncrement > enemySize){ iteratorIncrement = enemySize / 2;}
    
    //for each dungeon node
    for(size_t i = 0; i < labyrinthNodes.size(); ++i)
    {
        //set end iterator
        endIterator = startIterator + iteratorIncrement;
        
        //if start iterator is less than last element
        if(startIterator < enemySize - 1 && endIterator >= enemySize){ endIterator = enemySize - 1;}
        else if(startIterator >= enemySize - 1){break;}
        //place enemy
        labyrinthNodes[i].placeEnemies(thisEnemiesVector,startIterator,endIterator,rngSeed);
        //set new start iterator 
        startIterator += iteratorIncrement;
        
    }
}

NodeGenerator& Labyrinth::getNodeGenerator()
{
    return nodesGen;
}

std::vector <Enemy*> * Labyrinth::GetEnemiesInLabyrinthVector()
{
	return m_enemy_inventory.GetEnemyVector();
}

void Labyrinth::SetPointerToGameInventory(GameInventory* thisInventory)
{
	m_game_inventory_ptr = thisInventory;
}

void Labyrinth::DungeonEntranceHitOperations()
{
	for(size_t i = 0; i < dungeonEntrances.size(); i++)
	{
		DungeonTile* dungeonEntranceTile = dungeonEntrances[i].tile_ptr;
	    
	    PlayerManager::PlayerLocation p1_loc, p2_loc, p3_loc, p4_loc;
		m_player_manager_ptr->GetLocationEnumOfPlayers(&p1_loc,&p2_loc,&p3_loc,&p4_loc);
	    
		if( p1_loc == PlayerManager::PlayerLocation::LABYRINTH && 
			checkCollision(dungeonEntranceTile->getBox(),m_player_manager_ptr->GetPointerToPlayerOne()->getCollisionBox() ) )
		{
			Labyrinth::setPlayerHitDungeonEntranceBool(true,1);
			
			Labyrinth::SetIndexMiniDungeonEntered(dungeonEntrances[i].xml_entry.id_number);
			
			m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::LABYRINTH_2_DUNGEON,1);
			m_player_manager_ptr->SetDungeonEnteredForPlayer(dungeonEntrances[i].xml_entry.id_number,1);
		}
		
		int num_players = m_player_manager_ptr->GetNumberOfPlayers();
		
		if(num_players > 1)
		{
			if( p2_loc == PlayerManager::PlayerLocation::LABYRINTH && checkCollision(dungeonEntranceTile->getBox(),m_player_manager_ptr->GetPointerToPlayerTwo()->getCollisionBox() ) )
			{
				Labyrinth::setPlayerHitDungeonEntranceBool(true,2);
				
				Labyrinth::SetIndexMiniDungeonEntered(dungeonEntrances[i].xml_entry.id_number);
				
				m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::LABYRINTH_2_DUNGEON,2);
				m_player_manager_ptr->SetDungeonEnteredForPlayer(dungeonEntrances[i].xml_entry.id_number,2);
			}
		}
		
		if(num_players > 2)
		{
			if( p3_loc == PlayerManager::PlayerLocation::LABYRINTH && checkCollision(dungeonEntranceTile->getBox(),m_player_manager_ptr->GetPointerToPlayerThree()->getCollisionBox() ) )
			{
				Labyrinth::setPlayerHitDungeonEntranceBool(true,3);
				
				Labyrinth::SetIndexMiniDungeonEntered(dungeonEntrances[i].xml_entry.id_number);
				
				m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::LABYRINTH_2_DUNGEON,3);
				m_player_manager_ptr->SetDungeonEnteredForPlayer(dungeonEntrances[i].xml_entry.id_number,3);
			}
		}
		
		if(num_players > 3)
		{
			if( p4_loc == PlayerManager::PlayerLocation::LABYRINTH && checkCollision(dungeonEntranceTile->getBox(),m_player_manager_ptr->GetPointerToPlayerFour()->getCollisionBox() ) )
			{
				Labyrinth::setPlayerHitDungeonEntranceBool(true,4);
				
				Labyrinth::SetIndexMiniDungeonEntered(dungeonEntrances[i].xml_entry.id_number);
				
				m_player_manager_ptr->SetLocationEnumOfPlayer(PlayerManager::PlayerLocation::LABYRINTH_2_DUNGEON,4);
				m_player_manager_ptr->SetDungeonEnteredForPlayer(dungeonEntrances[i].xml_entry.id_number,4);
			}
		}
		
	}
	
	
}

void Labyrinth::setPlayerHitDungeonEntranceBool(bool state, int num_player)
{
	switch(num_player)
	{
		case 1:{ hitDungeonEntrace_p1 = state; break;}
		case 2:{ hitDungeonEntrace_p2 = state; break;}
		case 3:{ hitDungeonEntrace_p3 = state; break;}
		case 4:{ hitDungeonEntrace_p4 = state; break;}
	}
}

bool Labyrinth::getPlayerHitDungeonEntraceBool(int num_player)
{
	bool boolToReturn = false;
	
	switch(num_player)
	{
		case 1:{ boolToReturn = hitDungeonEntrace_p1; break;}
		case 2:{ boolToReturn = hitDungeonEntrace_p2; break;}
		case 3:{ boolToReturn = hitDungeonEntrace_p3; break;}
		case 4:{ boolToReturn = hitDungeonEntrace_p4; break;}
	}
	
	return boolToReturn;
}

void Labyrinth::SetIndexMiniDungeonEntered(std::int16_t num){indexMiniDungeonEntered = num;}
std::int16_t Labyrinth::GetIndexMiniDungeonEntered(){return indexMiniDungeonEntered;}

void Labyrinth::getDungeonEntranceLocationForThisIndex(size_t& index, int* x, int* y)
{
	if(index < dungeonEntrances.size())
	{
		*x = dungeonEntrances.at(index).tile_ptr->getBox().x;
		*y = dungeonEntrances.at(index).tile_ptr->getBox().y;
	}
	
}

size_t Labyrinth::getNumberOfDungeonEntranceLocations(){return dungeonEntrances.size();}

void Labyrinth::setPlayerHitLabyrinthExitBool(bool state, int num_player)
{
	switch(num_player)
	{
		case 1:{ hitLabyrinthExit_p1 = state; break;}
		case 2:{ hitLabyrinthExit_p2 = state; break;}
		case 3:{ hitLabyrinthExit_p3 = state; break;}
		case 4:{ hitLabyrinthExit_p4 = state; break;}
	}
}

bool Labyrinth::getPlayerHitLabyrinthExitBool(int num_player)
{
	bool boolToReturn = false;
	
	switch(num_player)
	{
		case 1:{ boolToReturn = hitLabyrinthExit_p1; break;}
		case 2:{ boolToReturn = hitLabyrinthExit_p2; break;}
		case 3:{ boolToReturn = hitLabyrinthExit_p3; break;}
		case 4:{ boolToReturn = hitLabyrinthExit_p4; break;}
	}
	
	return boolToReturn;
}

void Labyrinth::GetExitTileLocation(int* x, int* y)
{
	*x = exitTile->getBox().x;
	*y = exitTile->getBox().y;
}
