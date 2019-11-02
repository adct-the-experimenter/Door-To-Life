# Door To Life

This is a video game in which the player wins by finding a golden tile in a labyrinth. Avoid monsters and obstacles.

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
