#include "globalvariables.h"

std::string DATADIR_STR_PRE = DATADIR_NAME;

//std::string DATADIR_STR_PRE2 = DATADIR_STR_PRE.erase(0,1);

//std::string DATADIR_STR = DATADIR_STR_PRE2.erase(DATADIR_STR_PRE2.size() - 1,1);

std::string DATADIR_STR = DATADIR_NAME;

//Directories for string

//Place Directory File Path
std::string PLACEDIR_STR = "/Graphics/";

//Buttons Directory file path
std::string BUTTONSDIR_STR = "/Graphics/";

//weapons directory file path
std::string WEAPONS_IMAGE_DIR_STR = "/Graphics/weapons/";

//Menu directory file path
std::string MENU_IMAGE_DIR_STR = "/Graphics/";

//Tile Dimensions
 //tile dimensions 
std::int16_t globalTileWidth = 80;
std::int16_t globalTileHeight = 80;

//global function to load buffer
bool LoadBuffer(ALuint* buffer, std::string& rel_path)
{
	bool success = true;
	
	 //load wave file
    std::string filePath = DATADIR_STR + std::string(rel_path);
    Mix_Chunk* chunkWAV = Mix_LoadWAV(filePath.c_str());

    if(chunkWAV == nullptr)
    {
        fprintf(stderr, "Unable to load WAV file: %s\n", Mix_GetError());
        success = false;
    }
    else
    {        
        //setup buffer 
        
        //allocate buffer
        alGenBuffers(1, buffer);
        
        //transfer Mix_Chunk data and length to OpenAL buffer
        alBufferData(*buffer, AL_FORMAT_MONO16, chunkWAV->abuf, chunkWAV->alen, 44100); 
        ALenum test_error_flag = alGetError();
		if(test_error_flag != AL_NO_ERROR)
		{
			std::cout << "\nError found in making buffer:" << alGetString(test_error_flag) << "\n";
			return false;
		}
        
        //free win music media
        Mix_FreeChunk(chunkWAV);
        chunkWAV = nullptr;
    }
    
    return success;
}
