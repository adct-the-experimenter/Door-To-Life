cmake_minimum_required(VERSION 3.1.1)

set (CMAKE_CXX_STANDARD 11)

set(PROJECT_NAME Door-to-Life)
project (${PROJECT_NAME} LANGUAGES C CXX)

option(DATAPATH "Path to data Directory" ON)

#-DCMAKE_BUILD_TYPE=Release
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -Wall -DDATADIR=${DATAPATH} -fPIE")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2 -Wall -DDATADIR=${DATAPATH} -fPIE")

#SDL2 specific stuff and its add on libraries
INCLUDE(FindPkgConfig)

pkg_check_modules(openal REQUIRED openal)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2image REQUIRED SDL2_image)

pkg_check_modules(SDL2mixer REQUIRED SDL2_mixer)
pkg_check_modules(SDL2ttf REQUIRED SDL2_ttf)

#Boost random generation
set(BOOST_LIBS date_time system random)
find_package(Boost COMPONENTS ${BOOST_LIBS} REQUIRED)
#find_package(Threads REQUIRED)

#Pugi XML parsing
find_path(pugixml_INCLUDE_DIRS pugixml.hpp)
find_library(pugixml_LIBRARIES NAMES pugixml)


#For the shared library:
set ( PROJECT_LINK_LIBS  ${openal_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2image_LIBRARIES} ${SDL2ttf_LIBRARIES} ${SDL2mixer_LIBRARIES} ${Boost_LIBRARIES} ${pugixml_LIBRARIES})
#where to find library files .so 
link_directories( /usr/lib /usr/local/lib ) 

set ( PROJECT_INCLUDE_DIR ${SDL2_INCLUDE_DIRS} ${SDL2image_INCLUDE_DIRS} ${SDL2mixer_INCLUDE_DIRS} ${SDL2ttf_INCLUDE_DIRS} ${pugixml_INCLUDE_DIRS})

#for where to find header files for source and library
include_directories(/usr/include /usr/local/include ./src ${PROJECT_INCLUDE_DIR})

if (MINGW)
    # need to link with mingw32 before SDL2
    list(APPEND _link_libraries mingw32)
endif ()

set(SOURCES src/main.cpp
src/labyrinth_dungeon_manager.cpp src/WinnerDecisionRoom.cpp src/winner_judge.cpp src/labyrinth.cpp src/Dungeon.cpp 
src/DungeonXMLRegistry.cpp src/DungeonXMLReader.cpp 
src/submap.cpp
src/collisionhandler.cpp
src/audio_renderer.cpp
src/enemy_inventory.cpp
src/winner_media_loader.cpp
src/dungeon_media_loader.cpp
src/enemy_media_loader.cpp
src/player_media_loader.cpp
src/game_inventory.cpp
src/weapons_loader.cpp

src/MazeGenerator.cpp src/NodeGenerator.cpp src/LabyrinthMap.cpp
src/hashtable.cpp src/linkedlist.cpp src/item.cpp
src/MazeNode.cpp src/Node.cpp
src/LabyrinthNode.cpp
src/Dungeon_Tile.cpp src/TileMapDimensions.cpp
src/door.cpp src/key.cpp
src/gun.cpp src/bullet.cpp src/sword.cpp src/weapon.cpp
src/greedy_zombie.cpp
src/othercockroach.cpp
src/enemy.cpp src/lineofsight.cpp
src/player_manager.cpp src/player.cpp src/healthbar.cpp src/player_inventory.cpp
src/sprite.cpp src/dot_final.cpp
src/title.cpp src/titlemenu.cpp
src/pause_menu.cpp src/menu.cpp src/graphicalbutton.cpp
src/gamestate.cpp
src/frame_rate_cap.cpp
src/event_handler.cpp
src/collisionobject.cpp
src/DrawingManager.cpp
src/LTexture.cpp src/LTimer.cpp
src/damage_values.cpp
src/globalvariables.cpp
			 )

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

#make executable sphere from simple-sphere.cpp 
add_executable(${PROJECT_NAME} ${SOURCES})
#link libraries
target_link_libraries(${PROJECT_NAME} ${PROJECT_LINK_LIBS})
