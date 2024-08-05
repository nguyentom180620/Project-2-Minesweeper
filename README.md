Name: Tom Nguyen
Section: 10790
UFL email: nguyentom@ufl.edu
System: Windows 11
Compiler: g++
SFML Version: 2.5.1
IDE: CLion

Other notes:

I used the blog post tutorial by Daniel Melendez at link:
https://dev.to/danielmelendezz/how-to-get-smfl-to-work-on-windows-using-clion-2bef
So, my CMakeLists.txt looks like this below:
cmake_minimum_required(VERSION 3.24)
project(minesweeper)

set(CMAKE_CXX_STANDARD 14)

add_executable(project3_minesweeper main.cpp
windows.cpp
windows.h
Text.cpp
Text.h
Tile.cpp
Tile.h
Board.cpp
Board.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include/SFML)
target_link_libraries(project3_minesweeper sfml-system sfml-window sfml-graphics sfml-audio)