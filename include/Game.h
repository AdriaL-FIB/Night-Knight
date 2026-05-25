#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include "Menu.h"
#include "SoundManager.h"



#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT (16*2+16*22 + 1)





// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

private:
	Game() {}
	
public:
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	//void postProcessing();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	void updateTimers(int deltaTime);
	
	bool getKey(int key) const;
	bool getKeyUp(int key) const;
	bool getSpecialKey(int key) const;
	bool getSpecialKeyUp(int key) const;

	void exitLevel();
	void changeLevel(int level);

	void savePuntuacionYVidas(int puntuacion, int vidas);
	int getVidasActuales();
	int getPuntuacionActual();

	void resize(int w, int h);

	void theEnd();

private:
	bool initShaders();
	void addPostEffect(int id, int duration);
	void addPostEffect(int id, int duration, const glm::ivec2& point);

	bool playing();


	int currentTime = 0;

	int currentLevel = 0, targetLevel = 0;

	bool bPlay = false;               // Continue to play game?
	Scene* scene = nullptr;           // Scene to render
	Menu menu;					      // Menu
	bool keys[256] = {}, specialKeys[256] = {}; // Store key states so that 
	                                  // we can have access at any time
	bool old_keys[256] = {}, old_specialKeys[256] = {};

	ISoundEngine* engine = nullptr;
	ISound* menuMusic = nullptr;
	ISound** bgMusicPtr = nullptr;

	int transitionTimer = 0;

	Texture frameBufferTexture;
	GLuint FBO = 0;


	GLuint vao = 0;
	GLuint vbo = 0;
	GLint posLocation = -1, texCoordLocation = -1;


	int puntuacionActual = 0;
	int vidasActuales = 3;
	
	ShaderProgram postProcessingProgram;

	Effect postEffect;
};


#endif // _GAME_INCLUDE


