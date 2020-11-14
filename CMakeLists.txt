cmake_minimum_required(VERSION 3.16.3)

project(bigbool)

set(SOURCE_EXE testbb.c)

set(SOURCE_LIB bblib.c)

add_library(bblib STATIC ${SOURCE_LIB})

add_executable(testbb ${SOURCE_EXE})

target_link_libraries(testbb bblib)