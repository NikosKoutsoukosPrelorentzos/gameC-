#pragma once
#include "player.h"
#include "enemy.h"

class Game 
{
	int score = 0;
	typedef enum {STATUS_START, STATUS_PLAYING,STATUS_FINISH} status_t;
	Bullet* bullet = nullptr;
	Player* player = nullptr;
	bool player_initialized = false;
	bool debug_mode = true;
	Enemy* meteorite = nullptr;
	Enemy* meteorite2 = nullptr;
	Enemy* meteorite3 = nullptr;
	void spawnMeteorite();
	void checkMeteorite();
	bool checkCollisionWithBullet(Enemy *meteorite);
	bool checkCollisionWithPlayer(Enemy* meteoritee);
	status_t status = STATUS_START;

	unsigned int window_width = WINDOW_WIDTH
		, window_height = WINDOW_HEIGHT;



	void updateStartScreen();
	void updateLevelScreen();

	void drawFinishScreen();
	void drawStartScreen();
	void drawLevelScreen();
public:
	
	float playerX() { return player->getPosX(); }
	float playerY() { return player->getPosY(); }
	void setDebugMode(bool d) { debug_mode = d; }
	bool getDebugMode() const { return debug_mode; }
	void update();
	void draw();
	void init();
	unsigned int getWindowWidth() { return window_width; }
	unsigned int getWindowHeight() { return window_height; }
	float window2canvasX(float x);
	float window2canvasY(float y);
	void setWindowDimensions(unsigned int w, unsigned int h) 
	{
		window_width = w;
		window_height = h;
	}

	Game();
	~Game();
};