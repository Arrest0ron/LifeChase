cmake_minimum_required(VERSION 3.10)
project(SFMLProject)

# Set the path to your SFML directory (change this if needed)
set(SFML_DIR "/home/user/Documents/SFML-2.6.2/lib/cmake/SFML/")

find_package(SFML 2.5 REQUIRED graphics window system)

add_executable(SFMLProject src/main.cpp src/vmath.cpp src/visual.cpp)
target_link_libraries(SFMLProject sfml-graphics sfml-window sfml-system)
