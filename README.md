# lvgl-sdl
Windows lvgl sdl demo. Using mingw toolchain.


## Windows

## Step 1. Setup environment (MSYS2 recommended)
### Install MSYS2
https://www.msys2.org/

### Setup environment variable
![alt text](/others/environment_variable.png)

make sure ".../mingw64/bin" has higher priority than ".../usr/bin".

## Step 2. Install mingw toolchain (MSYS2 recommended)
### Update database
```Bash
pacman -Syyu
```
### Install GCC
```Bash
pacman -S mingw-w64-x86_64-gcc
```
### Install MAKE
```Bash
pacman -S mingw-w64-x86_64-make
```
### Install CMAKE
```Bash
pacman -S mingw-w64-x86_64-cmake
```
### Install SDL2
```Bash
pacman -S mingw-w64-x86_64-SDL2
```

## Step 3. Clone repository
### Clone
```Bash
git clone git@github.com:sunzhen222/lvgl-sdl.git
cd lvgl-sdl
```
### lvgl Submodule
```Bash
git submodule init
git submodule update
```

## Step 4. Build and run
```Bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
./lvgl-sdl.exe
```

or
```Bash
.\build.bat
```

