#ifndef GLOBALVARIABLES
#define GLOBALVARIABLES

#include <iostream>

#include <string>

///Data Directory File Path

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)

//DATADIR macro used by automake for path to data files
//if DATADIR macro is not defined, define it as data
#ifndef DATADIR
    #define DATADIR "../data"
#endif

#define DATADIR_NAME STR(DATADIR)

extern std::string DATADIR_STR;

//Place Directory File Path
extern std::string PLACEDIR_STR;

//Buttons Directory file path
extern std::string BUTTONSDIR_STR;

//weapons directory file path
extern std::string WEAPONS_IMAGE_DIR_STR;

//Menu directory file path
extern std::string MENU_IMAGE_DIR_STR;

 //tile dimensions 
extern std::int16_t globalTileWidth;
extern std::int16_t globalTileHeight;

//Platform dependent SDL headers and OpenAL headers

//If platform is unix
#if defined _unix_ || defined _unix || defined unix

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include "AL/al.h" //header for OpenAL Soft
#include "AL/alc.h" //header for OpenAL Soft

#include <cstdint>

//boost random meresenne twister with probablities
#include <ctime>
//random generation
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/discrete_distribution.hpp> // for generating a random number with different probabilities for each number
#include <boost/random/variate_generator.hpp>

typedef boost::mt19937_64 RNGType;

//If platform is linux
#elif  defined _linux_ || defined _gnu_linux_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include "AL/al.h" //header for OpenAL Soft
#include "AL/alc.h" //header for OpenAL Soft

//boost random meresenne twister with probablities
#include <ctime>
//random generation
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/discrete_distribution.hpp> // for generating a random number with different probabilities for each number
#include <boost/random/variate_generator.hpp>

typedef boost::mt19937_64 RNGType;

//If platform is from Apple
#elif __APPLE__ && __MACH__

//Assuming apple with framework linking
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"

#include "AL/al.h" //header for OpenAL Soft
#include "AL/alc.h" //header for OpenAL Soft

#include <cstdint>

//boost random meresenne twister with probablities
#include <ctime>
//random generation
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/discrete_distribution.hpp> // for generating a random number with different probabilities for each number
#include <boost/random/variate_generator.hpp>

typedef boost::mt19937_64 RNGType;

//if platform is Windows
#elif  	_WIN32


#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "al.h" //header for OpenAL Soft
#include "alc.h" //header for OpenAL Soft

#include <ctime>
#include <boost\random\mersenne_twister.hpp>
#include <boost\random\uniform_int_distribution.hpp>
#include <boost\random\discrete_distribution.hpp> // for generating a random number with different probabilities for each number
#include <boost\random\variate_generator.hpp>

typedef boost::mt19937_64 RNGType;

#include <cstdint>

#else
//Assuming apple with framework linking
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include "AL/al.h" //header for OpenAL Soft
#include "AL/alc.h" //header for OpenAL Soft

#include <cstdint>

//boost random meresenne twister with probablities
#include <ctime>
//random generation
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/discrete_distribution.hpp> // for generating a random number with different probabilities for each number
#include <boost/random/variate_generator.hpp>

typedef boost::mt19937_64 RNGType;

#endif


//global function to load buffer
bool LoadBuffer(ALuint* buffer, std::string& rel_path);


#endif // GLOBALVARIABLES

