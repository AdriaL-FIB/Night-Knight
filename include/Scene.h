#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include <queue>
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include "Text.h"
#include "Item.h"
#include "SoundManager.h"

#define MAX_LIGHTS 10


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene(int level);
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	void changePauseState();
	bool getPauseState();



private:
	void initShaders();
	void spawnKey();
	void spawnDoor();
	Item spawnHourglass(glm::vec2 pos);
	Item spawnGem(glm::vec2 pos);
	Item spawnClock(glm::vec2 pos);
	void spawnDoorParticle(glm::vec2 pos);
	void spawnCor();
	void spawnTorch(glm::ivec2 pos, int type);
	//void executeFunction(void(Scene::*)());
	vector<pair<glm::ivec2, int>>* getLightSources();

	//void gameOver();

	bool loadLevelInfo(const string& levelFile);

private:
	void updateTimers(int deltaTime);

	int level = 0;

	Texture bgSpritesheet, objectsSpritesheet, doorSpritesheet, particleSpritesheet, corSpritesheet, torchSpriteSheet;

	Sprite *bg = nullptr;
	TileMap *map = nullptr;
	Player *player = nullptr;
	vector<Enemy*> enemies;
	ShaderProgram texProgram;
	float currentTime = 0.f;
	glm::mat4 projection = glm::mat4(1.f);

	Enemy* asesino = nullptr;

	Sprite* key = nullptr;
	Sprite* door = nullptr;
	Sprite* particleDoor = nullptr;
	Sprite* cor = nullptr;

	vector<Sprite*> torches;

	glm::vec2 doorPos = glm::vec2(0.f), keyPos = glm::vec2(0.f), initPlayerPos = glm::vec2(0.f);


	bool keyCollected = false;
	int spawnTimer = -1, despawnTimer = -1, freezeTimer = 0, startTimer = 0;
	deque<Item> objects; 
	int stageTimer = 0, gameOverTimer = 0, stageCompletedTimer = 0;
	bool gameOver = false, stageCompleted = false;
	//void(Scene::*timerFunc)();

	Text text;

	ISoundEngine* engine = nullptr;
	ISound* bgSound = nullptr;
	ISoundSource* puntIncrSrc = nullptr;

	ISoundSource* hourglassSrc = nullptr, * gemSoundSrc = nullptr, * clockSoundSrc = nullptr;

	ISound* puntIncrSound = nullptr;
	ISound* hourglassSound = nullptr;
	ISound* gameOverSound = nullptr;
	ISound* readySound = nullptr;
	ISound* clockSound = nullptr;

	int tickSoundTime = 0;


	bool paused = false;

	vector<pair<glm::ivec2, int>> lightSources;


};


#endif // _SCENE_INCLUDE

