cmake_minimum_required(VERSION 3.10)
project(Reder)
include(FetchContent)


FetchContent_Declare(
    MVM
    GIT_REPOSITORY https://github.com/Arrest0ron/MVM.git
    GIT_TAG master
)

FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        2.6.2  # or a specific tag
)

FetchContent_MakeAvailable(SFML)
# set(CMAKE_PREFIX_PATH "include/")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fonts/TimesNewRoman.ttf
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)


# find_package(SFML REQUIRED graphics window system)

# Make the dependency available for use
FetchContent_MakeAvailable(MVM)

add_executable(Reder src/main.cpp )
target_link_libraries(Reder MVM  sfml-graphics sfml-window sfml-system)
