cmake_minimum_required(VERSION 3.11.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -g3")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -no-pie")

set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

file(
    GLOB_RECURSE
    MEDIAS
    "${CMAKE_CURRENT_SOURCE_DIR}/models/*"
    "${CMAKE_CURRENT_SOURCE_DIR}/media/*"
)

foreach(MEDIA ${MEDIAS})
    file(COPY ${MEDIA} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach()

set(
    SRC_GRAPHIC
    Client/Menu/Menu.cpp
    Client/Menu/Main.cpp
    Client/Menu/Button.cpp
    Client/Menu/Event.cpp
    Client/Menu/MenuMode.cpp
    Client/Menu/MenuNbPlayer.cpp
    Client/Menu/MenuSave.cpp
    Client/Menu/MenuOption.cpp
    Client/Menu/MenuPause.cpp
    Client/Sources/Client.cpp
    Client/Sources/LocalPlay.cpp
    Client/Sources/Ai.cpp
    Client/Sources/Scenes/WaitingScreen.cpp
    Client/Sources/Scenes/InGame.cpp
    Client/Sources/Scenes/Lose.cpp
    Client/Sources/Scenes/Win.cpp
    Client/Sources/Scenes/SceneManager.cpp
    Client/Sources/MapDisplayer.cpp
    Common/Sources/ClientSocket.cpp
    Server/Sources/GameLogic/Bomb.cpp
    Server/Sources/GameLogic/BombHandler.cpp
    Server/Sources/GameLogic/Game.cpp
    Server/Sources/GameLogic/Player.cpp
    Server/Sources/GameLogic/Wall.cpp
    Server/Sources/MapGenerator/MapGeneration.cpp
)

set(
    SRC_CLIENT
    Client/Sources/Main.cpp
    Common/Sources/ClientSocket.cpp
    Common/Sources/ClientSocket.hpp
    Client/Sources/Client.cpp
    Client/Sources/Client.hpp
    Server/Sources/GameLogic/Bomb.cpp
    Server/Sources/GameLogic/BombHandler.cpp
    Server/Sources/GameLogic/Game.cpp
    Server/Sources/GameLogic/Player.cpp
    Server/Sources/GameLogic/Wall.cpp
    Server/Sources/MapGenerator/MapGeneration.cpp
    Client/Sources/Ai.cpp
)

set(
    SRC_CLIENT_REVIEW
    Client/Sources/Main.cpp
    Common/Sources/ClientSocket.cpp
    Common/Sources/ClientSocket.hpp
    Client/Sources/ClientReview.cpp
    Client/Sources/Client.hpp
    Server/Sources/GameLogic/Bomb.cpp
    Server/Sources/GameLogic/BombHandler.cpp
    Server/Sources/GameLogic/Game.cpp
    Server/Sources/GameLogic/Player.cpp
    Server/Sources/GameLogic/Wall.cpp
    Server/Sources/MapGenerator/MapGeneration.cpp
    Client/Sources/Ai.cpp
)

set(
    SRC_SERVER_MATCH
    Server/Sources/ServerSocket.cpp
    Common/Sources/ClientSocket.cpp
    Server/Sources/Client.cpp
    Server/Sources/MatchMain.cpp
    Server/Sources/ServerMatch.cpp
    Server/Sources/GameLogic/Bomb.cpp
    Server/Sources/GameLogic/BombHandler.cpp
    Server/Sources/GameLogic/Game.cpp
    Server/Sources/GameLogic/Player.cpp
    Server/Sources/GameLogic/Wall.cpp
    Server/Sources/MapGenerator/MapGeneration.cpp
)

set(
    SRC_SERVER_MATCHMAKING
    Server/Sources/Server.cpp
    Server/Sources/Client.cpp
    Server/Sources/Tournament.cpp
    Server/Sources/ServerSocket.cpp
)

set(
    SRC_SERVER_MATCHMAKING_REVIEW
    Server/Sources/Server.cpp
    Server/Sources/Client.cpp
    Server/Sources/TournamentReview.cpp
    Server/Sources/ServerSocket.cpp
)

set(
    SRC_SERVER_TOURNAMENT
    Server/Sources/TournamentMain.cpp
    Server/Sources/ServerTournament.cpp
    Server/Sources/ServerSocket.cpp
    Server/Sources/Client.cpp
    Server/Sources/Match.cpp
    Common/Sources/ClientSocket.cpp
)

set(
    SRC_MAP_GENERATOR
    Server/Sources/MapGenerator/MapGeneration.cpp
    Server/Sources/MapGenerator/Main.cpp
)

file(
    GLOB
    SRC_GAME_LOGIC
    "Server/Sources/GameLogic/*.cpp"
    "Server/Sources/MapGenerator/MapGeneration.cpp"
)

add_executable(
    bomberman
    ${SRC_GRAPHIC}
)

add_executable(
    mapGenerator
    ${SRC_MAP_GENERATOR}
)

add_executable(
    ia
    ${SRC_CLIENT}
)

add_executable(
    ia_review
    ${SRC_CLIENT_REVIEW}
)

add_executable(
    server
    Server/Sources/Main.cpp
    ${SRC_SERVER_MATCHMAKING}
    ${SRC_GAME_LOGIC}
)

add_executable(
    server_tournament
    ${SRC_SERVER_TOURNAMENT}
)

add_executable(
    server_match
    ${SRC_SERVER_MATCH}
)

add_executable(
    server_review
    Server/Sources/Main.cpp
    ${SRC_SERVER_MATCHMAKING_REVIEW}
)

# Build a library to use it in local with a thread
add_library(
    local_server
    STATIC
    ${SRC_SERVER_MATCHMAKING}
)

target_include_directories (
    bomberman
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Irrlicht/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Client/Sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Client/Sources/Scenes
    ${CMAKE_CURRENT_SOURCE_DIR}/Client/Menu
    ${CMAKE_CURRENT_SOURCE_DIR}/Server/Sources/GameLogic
)

target_include_directories (
    ia
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Server/Sources/GameLogic
    ${CMAKE_CURRENT_SOURCE_DIR}/Common/Sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Server/Sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Client/Menu
)

target_include_directories (
    ia_review
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Server/Sources/GameLogic
    ${CMAKE_CURRENT_SOURCE_DIR}/Common/Sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Server/Sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Client/Menu
)

target_include_directories(
    server_tournament
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Server/Sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Common/Sources
)

target_include_directories(
    server_match
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Server/Sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Common/Sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Server/Sources/GameLogic
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Irrlicht/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Common/Sources
)

if(WIN32)
	target_link_libraries(server "Ws2_32.lib")
	target_link_libraries(server_review "Ws2_32.lib")
	target_link_libraries(server_tournament "Ws2_32.lib")
	target_link_libraries(server_match "Ws2_32.lib")
	target_link_libraries(ia "Ws2_32.lib")
	target_link_libraries(ia_review "Ws2_32.lib")
	target_link_libraries(local_server "Ws2_32.lib")
	target_link_libraries(bomberman
						"Ws2_32.lib"
						"${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Irrlicht/lib/Win64-visualStudio/Irrlicht.lib"
	)
	file (COPY ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Irrlicht/bin/Win64-VisualStudio/Irrlicht.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	include_directories(C:/libs/boost_1_70_0)
	include_directories(C:/libs/SFML/include)
endif()

target_compile_options(server PUBLIC "-g3")

target_link_libraries(
    ia
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Irrlicht/lib/Linux/libIrrlicht.a
)

target_link_libraries(
    server
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Irrlicht/lib/Linux/libIrrlicht.a
)

target_link_libraries(
    ia_review
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Irrlicht/lib/Linux/libIrrlicht.a
)

target_link_libraries(
    server_review
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Irrlicht/lib/Linux/libIrrlicht.a
)

add_dependencies(
    ia
    local_server
)

add_dependencies(
    ia_review
    local_server
)

if (UNIX)
target_link_libraries(
    bomberman
    sfml-audio
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/Irrlicht/lib/Linux/libIrrlicht.a
    GL 
    Xxf86vm 
    X11
)
endif ()