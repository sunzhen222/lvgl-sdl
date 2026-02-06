cmake_minimum_required(VERSION 3.14)

MESSAGE(STATUS "os: ${CMAKE_HOST_SYSTEM_NAME}")

project(lvgl-sdl LANGUAGES C CXX)

find_package(PkgConfig)
find_package(SDL2 REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

set(PROJECT_DIR "${CMAKE_SOURCE_DIR}")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(LVGL_DIR "${PROJECT_DIR}/lvgl")
set(SIMULATOR_DIR "${SOURCE_DIR}/simulator")
set(SIMULATOR_LVDRV_DIR "${SIMULATOR_DIR}/lvgl_drv")


set(LV_BUILD_CONF_DIR "${PROJECT_DIR}/src/simulator" CACHE STRING "" FORCE)

include_directories(${PROJECT_DIR})
include_directories(${LVGL_DIR})
include_directories(${SIMULATOR_DIR})
include_directories(${SIMULATOR_LVDRV_DIR})


file(GLOB SIMULATOR_FILES
    "${SIMULATOR_DIR}/*.c"
)

file(GLOB SIMULATOR_LVDRV_FILES
    "${SIMULATOR_LVDRV_DIR}/*.c"
)

add_compile_options(-Wall -O3)

set(objsrc
    ${SIMULATOR_FILES} 
    ${SIMULATOR_LVDRV_FILES}
)

add_executable(lvgl-sdl ${objsrc})

add_subdirectory(${LVGL_DIR})

target_include_directories(lvgl-sdl PUBLIC ${SDL2_INCLUDE_DIRS})
target_compile_options(lvgl-sdl PUBLIC ${SDL2_CFLAGS_OTHER})

add_definitions(-DLV_LVGL_H_INCLUDE_SIMPLE)

if(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(lvgl-sdl ${SDL2_LIBRARIES} lvgl::lvgl lvgl::demos SDL2)
else()
    target_link_libraries(lvgl-sdl lvgl::demos SDL2::SDL2)
endif()
