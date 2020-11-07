# Door To Life

This is a video game in which the player wins by finding a golden tile in a labyrinth. Avoid monsters and obstacles.

Wear headphones to hear sound effects in 3D audio or use a 5.1, 6.1, 7.1 surround sound system with alsoft-config.
## Libraries Required
- SDL2
- SDL2 Image
- SDL2 Mixer
- SDL2 TTF
- Boost Random library
- OpenAL Soft

## How to Install

1. git clone or download this project.
2. cd Door-To-Life
3. mkdir build
4. cmake .. -DDATAPATH=../data -DCMAKE_BUILD_TYPE=Release
5. make
6. ./Door-to-Life


## Controls
- WASD or Arrow keys to move
- Space to activate weapon or open door

## Adding Custom Mini Dungeons to the Game

Custom dungeons can be created by using the program DTL-Dungeon-Editor here.
https://github.com/adct-the-experimenter/DTL-Dungeon-Editor

To add these custom dungeons, follow the steps below.

1. Create the dungeon in DTL-Dungeon-Editor.

2. Move the .xml file to Door-To-Life/data/dungeons_xml folder.

3. Edit the file Door-To-Life/data/dungeons_xml/xml-dungeon-registry.xml to include the name of the .xml file.

For example, if file is called t1.xml, then name should be added like so <Name>t1</Name> inside <Dungeons> node
with proper spacing of 4 spaces from the beginning of the line.

4. Play the game since it will automatically be added and given a random location.

## Special Note on Video Drivers

If the game won't show a menu or any graphics, it is very likely that there is something wrong with the video driver.

This is true for FreeBSD on IronLake and older Intel graphics cards. 
It says it is capable of using hardware acceleration, but it fails to do so and a segfault is caused in i965_dri.so.

Fortunately, a workaround is to choose a different driver for the renderer to use.

./Door-to-Life --show-renderer-drivers-info will show information on the renderer drivers including the number to use to reference the driver.

./Door-to-Life --renderer-deriver NUM will choose the renderer driver to use. NUM is an integer value 0,1,2, etc.

### To force software fallback for a renderer:
./Door-to-Life --renderer-software-fallback NUM
./Door-to-Life --renderer-software-fallback --renderer-deriver NUM
