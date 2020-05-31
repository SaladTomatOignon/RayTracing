cmake_minimum_required(VERSION 3.0)

project(lray)

# Inclusion de la bibliotheque OpenGL - SDL2
find_package(GLEW REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# Inclusion des headers
include_directories(include/application)
include_directories(include/geometrie)
include_directories(include/openGL)
include_directories(include/outils)
include_directories(include/rapidjson)
include_directories(include/rapidjson/error)
include_directories(include/rapidjson/internal)
include_directories(include/rapidjson/msinttypes)
include_directories(include/scene)
include_directories(include/)

# Inclusion des sources
file(GLOB SRC_FILES
    "src/geometrie/*.cpp"
    "src/openGL/*.cpp"
    "src/outils/*.cpp"
    "src/scene/*.cpp"
    "src/application/*.cpp"
    "src/main.cpp"
)

# Place les binaires générés dans un dossier bin
set(EXECUTABLE_OUTPUT_PATH "../bin/")

add_executable(lray ${SRC_FILES})

# Linkage des bibliothèques
target_link_libraries(lray PRIVATE ${GLEW_LIBRARIES} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})