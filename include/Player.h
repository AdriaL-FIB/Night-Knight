#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "Character.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player : public Character
{
public:
	~Player();
	virtual void init(const glm::ivec2& tileMapPos, bool rightSight, string spriteFile, const glm::ivec2& colliderSize, const glm::ivec2& colliderOffset, const glm::ivec2& pixelSize, const glm::vec2& texSize, const glm::ivec2& spawnPos, ShaderProgram& shaderProgram);
	virtual void update(int deltaTime);
	virtual void render();

	void checkCollisionUnder();
	bool isHurted();
	bool checkCollisionWithRect(const glm::ivec2 &leftTop, const glm::ivec2 &rightBottom, int type);
	bool inGodMode() const;
	void setGodMode(bool b);

	bool isGameOver() const;

	int getVidas() const;

	void increasePuntuacion(int valueToIncrease);
	int getPuntuacion() const;

	void morir();
	void muelto();

	bool sePuedeMover();
	void setVidas(int vidas);

private:
	virtual void loadAnimations();
	void respawn();

	void dentroDePlataforma();

	//bool damaged = false;
	int damagedTimer = 0, invulnerabilityTimer = 0;

	bool godMode = false;

	int vidas = 0;
	int puntuacion = 0;

	ISoundSource* jumpSrc = nullptr;
	ISoundSource* hitSrc = nullptr;
	ISoundSource* platformSrc = nullptr;

	glm::ivec2 spawnPos = glm::ivec2(0);

	int lastJumpAngle = 0;

};


#endif // _PLAYER_INCLUDE


