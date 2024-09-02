# Snake
Simple snake game with C and SDL2 library and SDL2_ttf
User presses SPACE to pause/unpause the game 
## Requirements
* CMake > 3.10
  * [CMake official page](https://cmake.org/)
* Make > 4.4.1
* GCC > 6.3.0
  * MinGW on Windows: [Download on Sourceforge](https://sourceforge.net/projects/mingw/)
* SDL2 library 
  * [SDL2 repo](https://github.com/libsdl-org/SDL)
* SDL2_ttf library
  * [SDL2_ttf repo](https://github.com/libsdl-org/SDL_ttf)
## Build Instructions
### For Linux
1. Make sure SDL2 and SDL2_ttf are installed in `/usr/local/` otherwise you have to edit the library and include path inside the CMakeLists.txt file.
2. Create a bin folder inside this repo `mkdir bin && cd bin`
3. Compile cmake and build `cmake .. && make`
### For Windows
1. Change the `mingw_dev_lib` in the CMakeLists.txt file with the location of your SDL2 and SDL2_ttf library.
2. Create a bin folder inside this repo `mkdir bin && cd bin`
3. Compile cmake and build `cmake .. -G "MinGW Makefiles" && make`



