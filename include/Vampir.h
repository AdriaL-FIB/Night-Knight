#pragma once
#include "Enemy.h"
class Vampir : public Enemy
{
public:
	virtual void init(const glm::ivec2& tileMapPos, bool rightSight, const glm::vec2& pos, TileMap *map,ShaderProgram& shaderProgram);
	virtual void update(int deltaTime);
private:
	virtual void loadAnimations();

	virtual void updateTimers(int deltaTime, bool freeze);

	void transformBat();
	void transformVampir();

	bool isBat = false;
	bool wantsToTransform = false;
	bool goesUp = false;

	glm::ivec2 realColliderSize = glm::ivec2(0), realColliderOffset = glm::ivec2(0);

	int timer = 0, transformTimer = 0;
	int nextTransformTime = 0;

};

