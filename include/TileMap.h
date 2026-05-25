#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include <vector>

#define TILE_NOT_SOLID 0
#define TILE_SOLID 1
#define TILE_SPIKE 2
#define TILE_PLATFORM 3
#define TILE_PLATFORM_ACTIVATED 4

// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

private:
	TileMap(const string &levelInfoStr, const glm::vec2 &minCoords, ShaderProgram &program);

public:

	int LEFT_WALL = 0, RIGHT_WALL = 0;

	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(const string &levelInfoStr, const glm::vec2 &minCoords, ShaderProgram &program);

	~TileMap();

	void render() const;
	void free();
	
	int getTileSize() const { return tileSize; }
	glm::ivec2 getMapSize() const { return mapSize; }

	int collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size, bool bJumping = false) const;
	int collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size, bool bJumping = false) const;
	int collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY = nullptr) const;
	int collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, bool ignorePlatform = false) const;

	int collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &colliderOffset, const glm::ivec2 &colliderSize, bool ignorePlatform = false) const;
	int collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &colliderOffset, const glm::ivec2 &colliderSize, bool ignorePlatform = false) const;
	int collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &colliderOffset, const glm::ivec2 &colliderSize, int *posY = nullptr) const;
	int collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &colliderOffset, const glm::ivec2 &colliderSize, bool ignorePlatform = false) const;

	int modifyTileMap(int i, int j, int newTile);

	bool tevacae(const glm::ivec2& pos, const glm::ivec2& size, bool rightSight) const;

	void reduceNumberOfPlatforms();
	int getNumOfTilesRemaining();
	glm::ivec2 getRandomPlatform();

	bool dentroDePlataforma(const glm::ivec2& pos, const glm::ivec2& colliderOffset, const glm::ivec2& colliderSize);
	
private:
	bool loadLevel(const string &levelInfoStr);
	void prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program);

private:
	GLuint vao = 0;
	GLuint vbo = 0;
	GLint posLocation = -1, texCoordLocation = -1;
	int nTiles = 0;

	glm::vec2 minCoords = glm::vec2(0.f);

	glm::ivec2 position = glm::ivec2(0);
	//Map size equals number of tiles of the map 16 horizontal 11 vertical
	glm::ivec2 mapSize = glm::ivec2(0);

	//Numero de tiles en tileSet
	glm::ivec2 tilesheetSize = glm::ivec2(0);

	//Numero de pixeles del tile
	int tileSize = 0, blockSize = 0;
	Texture tilesheet;

	//
	glm::vec2 tileTexSize = glm::vec2(0.f);
	

	int *map = nullptr;
	//[i,j] -> nTile
	int *numTile = nullptr;

	vector<glm::ivec2> platformPositions;

	static const vector<int> tileType;

	int numPlatforms = 0;


};


#endif // _TILE_MAP_INCLUDE


