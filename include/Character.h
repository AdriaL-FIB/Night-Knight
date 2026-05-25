#pragma once

#include "Sprite.h"
#include "TileMap.h"
#include "SoundManager.h"

class Character
{
public:
	virtual void init(const glm::ivec2& tileMapPos, bool rightSight, string spriteFile, const glm::ivec2& colliderSize, const glm::ivec2& colliderOffset, const glm::ivec2& pixelSize, const glm::vec2& texSize, ShaderProgram& shaderProgram);
	virtual void update(int deltaTime);
	virtual void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void setSpeed(int speed);
	glm::ivec2 getPosition() const;
	glm::ivec2 getSpriteSize() const;
	glm::ivec2 getColliderPos() const;
	glm::ivec2 getColliderSize() const;
	glm::ivec2 getCenterPos() const;

	void freeze(int milisec, bool tremolar);
	void addEffect(int id, int duration, int delay = 0);
	void addEffect(int id, int duration, const glm::ivec2& point, int delay = 0);


	virtual ~Character();

protected:

	virtual void loadAnimations() = 0;
	virtual void updateTimers(int deltaTime, bool freeze = false);

	bool bJumping = false;
	int moveSpeed = 0, moveSpeedBase = 0;

	int freezeTimer = 0;

	glm::ivec2 tileMapDispl = glm::ivec2(0), posCharacter = glm::ivec2(0);
	int jumpAngle = 0, startY = 0;
	Texture spritesheet;
	Sprite* sprite = nullptr;
	TileMap* map = nullptr;
	bool rightSight = true;
	glm::ivec2 spriteSize = glm::ivec2(0);

	glm::ivec2 colliderSize = glm::ivec2(0), colliderOffset = glm::ivec2(0);

	ISoundEngine* engine = nullptr;


	//int effectDelay, effectTimer, effectId;

};

