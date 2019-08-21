#variable CXX is the C++ compiler to use 
CXX=g++
#Debug is the variable containing flags passed for debugging
DEBUG = -g
#IFLAGS is the variable for search path for header files
IFLAGS = -I/usr/local/include
#LDFLAGS is the variable for library search paths to look into for libraries in LDLIBS
LDFLAGS = -L/usr/local/lib

#CXXFLAGS are the options to pass to the C++ compiler
CXXFLAGS= -std=c++11 -Wall  $(DEBUG) $(LDFLAGS) $(IFLAGS)
#LDLIBS is the variable for library flags passed to the compiler
LDLIBS = $(IFLAGS) $(LDFLAGS) -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lopenal



#source directory to put object and source files in
srcDir = src

#variable for object files used to make game executable
objects = $(srcDir)/main.o \
$(srcDir)/submap.o \
$(srcDir)/collisionhandler.o \
$(srcDir)/enemy_inventory.o \
$(srcDir)/dungeon_media_loader.o \
$(srcDir)/enemy_media_loader.o \
$(srcDir)/player_media_loader.o \
$(srcDir)/game_inventory.o \
$(srcDir)/weapons_loader.o \
$(srcDir)/labyrinth.o \
$(srcDir)/MazeGenerator.o $(srcDir)/NodeGenerator.o $(srcDir)/LabyrinthMap.o \
$(srcDir)/hashtable.o $(srcDir)/linkedlist.o $(srcDir)/item.o \
$(srcDir)/MazeNode.o $(srcDir)/Node.o \
$(srcDir)/LabyrinthNode.o \
$(srcDir)/Dungeon_Tile.o $(srcDir)/TileMapDimensions.o \
$(srcDir)/door.o $(srcDir)/key.o \
$(srcDir)/gun.o $(srcDir)/bullet.o $(srcDir)/sword.o $(srcDir)/weapon.o \
$(srcDir)/othercockroach.o \
$(srcDir)/enemy.o $(srcDir)/lineofsight.o \
$(srcDir)/player.o $(srcDir)/healthbar.o $(srcDir)/player_inventory.o \
$(srcDir)/sprite.o $(srcDir)/dot_final.o \
$(srcDir)/title.o $(srcDir)/titlemenu.o \
$(srcDir)/pause_menu.o $(srcDir)/menu.o $(srcDir)/graphicalbutton.o \
$(srcDir)/gamestate.o \
$(srcDir)/frame_rate_cap.o \
$(srcDir)/event_handler.o \
$(srcDir)/collisionobject.o \
$(srcDir)/LTexture.o $(srcDir)/LTimer.o \
$(srcDir)/damage_values.o \
$(srcDir)/globalvariables.o

#to dereference variables just use the dereference operator $(VAR)

#create game executable which depends on objects variable
game: $(objects) 
	$(CXX) -o game $(objects) $(LDLIBS) 

#create main object file
main.o: $(srcDir)/main.cpp  $(srcDir)/DungeonMedia.h \
$(srcDir)/sprite.h $(srcDir)/labyrinth.h 
	$(CXX) $(CXXFLAGS)  -c $(srcDir)/main.cpp $(LDLIBS)

#create object file for submap
submap.o: $(srcDir)/submap.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/submap.cpp

#create object file for collision handler
collisionhandler.o: $(srcDir)/collisionhandler.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/collisionhandler.cpp
    

#create enemy inventory object file
enemy_inventory.o: $(srcDir)/enemy_inventory.h 
	$(CXX) $(CXXFLAGS) -c $(srcDir)/enemy_inventory.cpp
    
#create object file for dungeon media loader
dungeon_media_loader.o: $(srcDir)/dungeon_media_loader.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/dungeon_media_loader.cpp

#create object file for enemy media loader
enemy_media_loader.o: $(srcDir)/enemy_media_loader.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/enemy_media_loader.cpp

#create object file for player media loader
player_media_loader.o: $(srcDir)/player_media_loader.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/player_media_loader.cpp

#create game inventory obect file
game_inventory.o: $(srcDir)/game_inventory.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/game_inventory.cpp

#create weapons loader object file
weapons_loader.o: $(srcDir)/weapons_loader.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/weapons_loader.cpp

#create labyrinth object file
labyrinth.o: $(srcDir)/labyrinth.h \
$(srcDir)/MazeGenerator.h $(srcDir)/NodeGenerator.h \
$(srcDir)/LabyrinthNode.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/labyrinth.cpp

#create maze generator object file
MazeGenerator.o: $(srcDir)/MazeGenerator.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/MazeGenerator.cpp
    
#create node generator object file
NodeGenerator.o: $(srcDir)/NodeGenerator.h $(srcDir)/hashtable.h $(srcDir)/Node.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/NodeGenerator.cpp

#create dungeon map object file
LabyrinthMap.o: $(srcDir)/LabyrinthMap.h $(srcDir)/LabyrinthNode.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/LabyrinthMap.cpp

#create hashtable object file
hashtable.o: $(srcDir)/hashtable.h $(srcDir)/linkedlist.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/hashtable.cpp
    
#create linkedlist object file 
linkedlist.o: $(srcDir)/linkedlist.h $(srcDir)/item.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/linkedlist.cpp

#create item object file
item.o: $(srcDir)/item.h $(srcDir)/Node.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/item.cpp

#create maze node object file
MazeNode.o: $(srcDir)/MazeNode.h $(srcDir)/Node.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/MazeNode.cpp
    
#create node object file
Node.o: $(srcDir)/Node.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/Node.cpp

#create dungeon map object file
LabyrinthNode.o: $(srcDir)/LabyrinthNode.h \
$(srcDir)/LTimer.h $(srcDir)/gamestate.h $(srcDir)/Dungeon_Tile.h \
$(srcDir)/dot_final.h $(srcDir)/key.h $(srcDir)/door.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/LabyrinthNode.cpp

#create dungeon tile object file
Dungeon_Tile.o: $(srcDir)/Dungeon_Tile.cpp $(srcDir)/Dungeon_Tile.h $(srcDir)/LTexture.h 
	$(CXX) $(CXXFLAGS) -c $(srcDir)/Dungeon_Tile.cpp
    
#create tile map dimensions object file
TileMapDimensions.o: $(srcDir)/LTexture.h $(srcDir)/TileMapDimensions.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/TileMapDimensions.cpp $(LDLIBS)

#create door object file
door.o: $(srcDir)/door.cpp $(srcDir)/door.h \
$(srcDir)/key.h $(srcDir)/dot_final.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/door.cpp

#create key object file
key.o: $(srcDir)/key.cpp $(srcDir)/key.h $(srcDir)/LTexture.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/key.cpp

#create gun object file
gun.o: $(srcDir)/gun.h $(srcDir)/bullet.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/gun.cpp

#create bullet object file
bullet.o:$(srcDir)/bullet.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/bullet.cpp

#create sword object file
sword.o: $(srcDir)/sword.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/sword.cpp

#create weapon object file
weapon.o: $(srcDir)/weapon.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/weapon.cpp

#create other cockroach object file
othercockroach.o: $(srcDir)/othercockroach.h
	$(CXX $(CXXFLAGS) -c $(srcDir)/othercockroach.cpp
    
#create enenmy object file
enemy.o : $(srcDir)/enemy.cpp $(srcDir)/enemy.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/enemy.cpp 

#create line of sight object file
lineofsight.o: $(srcDir)/lineofsight.h $(srcDir)/collisionhandler.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/lineofsight.cpp
    
#create player object file
player.o: $(srcDir)/player.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/player.cpp

#create healthbar object file
healthbar.o: $(srcDir)/healthbar.h $(srcDir)/healthbar.cpp
	$(CXX) $(CXXFLAGS) -c $(srcDir)/healthbar.cpp

player_inventory.o: $(srcDir)/player_inventory.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/player_inventory.cpp
    
#create sprite object file
sprite.o: $(srcDir)/sprite.cpp $(srcDir)/sprite.h $(srcDir)/dot_final.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/sprite.cpp

#create dot final object file
dot_final.o: $(srcDir)/dot_final.h $(srcDir)/collisionhandler.h \
$(srcDir)/Dungeon_Tile.h $(srcDir)/LTexture.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/dot_final.cpp

#create Title object file 	
title.o: $(srcDir)/title.cpp $(srcDir)/title.h $(srcDir)/titlemenu.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/title.cpp

#create title menu object file
titlemenu.o: $(srcDir)/titlemenu.cpp $(srcDir)/titlemenu.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/titlemenu.cpp

#create pause menu state object file
pause_menu.o: $(srcDir)/pause_menu.cpp $(srcDir)/pause_menu.h $(srcDir)/menu.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/pause_menu.cpp

#create menu state object file
menu.o: $(srcDir)/menu.cpp $(srcDir)/menu.h $(srcDir)/gamestate.h $(srcDir)/graphicalbutton.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/menu.cpp

#create graphical button object file
graphicalbutton.o: $(srcDir)/graphicalbutton.cpp $(srcDir)/graphicalbutton.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/graphicalbutton.cpp 
 
#create gamestate object file
gamestate.o: $(srcDir)/gamestate.cpp $(srcDir)/gamestate.h 
	$(CXX) $(CXXFLAGS) -c $(srcDir)/gamestate.cpp

#create frame rate cap object file
frame_rate_cap.o: $(srcDir)/frame_rate_cap.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/frame_rate_cap.cpp

#create event handler object file
event_handler.o: $(srcDir)/event_handler.h
	$(CXX) $(CXXFLAGS) -c $(srcDor)/event_handler.cpp

#create collisionobject object file
collisionobject.o: $(srcDir)/collisionobject.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/collisionobject.cpp
	
#create LTexture object file
LTexture.o: $(srcDir)/LTexture.cpp $(srcDir)/LTexture.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/LTexture.cpp $(LDLIBS)

#create LTimer object file
LTimer.o: $(srcDir)/LTimer.cpp $(srcDir)/LTimer.h
	$(CXX) $(CXXFLAGS)  -c $(srcDir)/LTimer.cpp $(LDLIBS)

#create damage values object file
damage_values.o: $(srcDir)/damage_values.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/damage_values.cpp
    
#create global variables object file
globalvariables.o: globalvariables.cpp globalvariables.h
	$(CXX) $(CXXFLAGS) -c $(srcDir)/globalvariables.cpp

#remove the game object file which also removes the object files
clean:
	rm game $(objects)

