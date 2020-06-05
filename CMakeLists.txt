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
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/application")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/geometrie")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/openGL")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/outils")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/rapidjson")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/rapidjson/error")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/rapidjson/internal")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/rapidjson/msinttypes")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/scene")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/")

# Inclusion des sources
file(GLOB SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/geometrie/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/openGL/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/outils/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/scene/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/application/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
)

# Place les binaires générés dans un dossier bin
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/")

# Optimisation du code
add_compile_options("-O2")

add_executable(lray ${SRC_FILES})

# Linkage des bibliothèques
target_link_libraries(lray PRIVATE ${GLEW_LIBRARIES} ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})