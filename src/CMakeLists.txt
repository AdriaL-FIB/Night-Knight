set(NIGHT_KNIGHT_HEADERS
    "../include/AnimKeyframes.h"
    "../include/AssetError.h"
    "../include/Character.h"
    "../include/Effect.h"
    "../include/Enemy.h"
    "../include/Esquelet.h"
    "../include/Fantasma.h"
    "../include/Game.h"
    "../include/Item.h"
    "../include/Menu.h"
    "../include/Player.h"
    "../include/Scene.h"
    "../include/Shader.h"
    "../include/ShaderProgram.h"
    "../include/SoundManager.h"
    "../include/Sprite.h"
    "../include/Text.h"
    "../include/Texture.h"
    "../include/TileMap.h"
    "../include/Vampir.h"
)

set(NIGHT_KNIGHT_SOURCES
    "Character.cpp"
    "AssetError.cpp"
    "Enemy.cpp"
    "Esquelet.cpp"
    "Fantasma.cpp"
    "Game.cpp"
    "main.cpp"
    "Menu.cpp"
    "Player.cpp"
    "Scene.cpp"
    "Shader.cpp"
    "ShaderProgram.cpp"
    "SoundManager.cpp"
    "Sprite.cpp"
    "Text.cpp"
    "Texture.cpp"
    "TileMap.cpp"
    "Vampir.cpp"
)

target_sources(${PROJECT_NAME} PRIVATE
    ${NIGHT_KNIGHT_HEADERS}
    ${NIGHT_KNIGHT_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)

source_group("Header Files" FILES ${NIGHT_KNIGHT_HEADERS})
source_group("Source Files" FILES ${NIGHT_KNIGHT_SOURCES})
