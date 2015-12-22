cmake_minimum_required(VERSION 3.3)
project(anihilacja)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc")

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

set(SOURCE_FILES src/main.c src/graphic/window.c src/graphic/window.h config.h src/debug/debug.c src/debug/debug.c src/debug/debug.h)
add_executable(anihilacja ${SOURCE_FILES})

target_link_libraries(anihilacja SDL2main SDL2)