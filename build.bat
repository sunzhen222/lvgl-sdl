@echo off

SET BUILD_FOLDER=%CD%\build

if not exist %BUILD_FOLDER% (
    mkdir %BUILD_FOLDER%
)

pushd build
del lvgl-sdl.exe
cmake .. -G "Ninja"
cmake --build .

start lvgl-sdl.exe

popd

