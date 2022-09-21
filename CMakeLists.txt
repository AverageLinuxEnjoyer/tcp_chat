cmake_minimum_required(VERSION 3.1)

IF (WIN32)
    set(CMAKE_C_COMPILER C:/msys64/mingw64/bin/gcc.exe)
    set(CMAKE_CXX_COMPILER C:/msys64/mingw64/bin/g++.exe)
    # this makes sure that .dll-files are build into build/ folder
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
ELSEIF (APPLE)
    # run 'where clang' and 'where clang++' to get paths
    set(CMAKE_C_COMPILER /usr/bin/clang)
    set(CMAKE_CXX_COMPILER /usr/bin/clang++)
ELSEIF (UNIX AND NOT APPLE)
    # run 'which gcc' and 'which g++' to get paths
    set(CMAKE_C_COMPILER /usr/bin/gcc)
    set(CMAKE_CXX_COMPILER /usr/bin/g++)
ENDIF()
    
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})


set(CMAKE_CXX_STANDARD 17)

set (CMAKE_CXX_FLAGS "-g -W -pedantic")

set(SOURCES 
    src/main.cpp
    src/server/server.cpp
    src/client/client.cpp
    src/server/server_network.cpp
    src/client/client_network.cpp
)

include_directories(src)


add_subdirectory(lib)


add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML)
#target_link_libraries(${PROJECT_NAME} PRIVATE sfml-audio)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-network)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-window)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "lobby")