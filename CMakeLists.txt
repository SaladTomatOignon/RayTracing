cmake_minimum_required(VERSION 3.0)

project(lray)

# Inclusion des headers
include_directories(include/geometrie)
include_directories(include/outils)
include_directories(include/rapidjson)
include_directories(include/rapidjson/error)
include_directories(include/rapidjson/internal)
include_directories(include/rapidjson/msinttypes)
include_directories(include/scene)

# Inclusion des sources
file(GLOB SRC_FILES
    "src/geometrie/*.cpp"
    "src/outils/*.cpp"
    "src/scene/*.cpp"
    src/main.cpp
)

# Met binaires générés dans un dossier bin
set(EXECUTABLE_OUTPUT_PATH "../bin/")

add_executable(lray ${SRC_FILES})