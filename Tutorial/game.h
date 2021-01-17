#pragma once
#include "hammer.h"
#include "warrior.h"
#include "enemy.h"
#include "bullet.h"
#include <vector>
class Game {
	std::vector<Enemy*> enemies;

	typedef enum {STATUS_START, STATUS_PLAYING,STATUS_END} status_t; //ENAS TUPOS O OPOIOS MAS LEEI OTI EXW MIA METAVLITI AUTOU TOU TUPOU POU EXEI KAPOIES KATASTASEIS
	Hammer* hammer = nullptr;
	Enemy* enemy = nullptr;
	Warrior* warrior = nullptr;
	Bullet* bullet = nullptr;
	//meta apo ligo ton dimiourgw me tin sunartisi xronou

	//ftiaxnoume state wste na min ftiaxnoume sunexws neo istance
	bool hammer_initialized = false;
	bool warrior_initialized = false;
	bool enemy_initialized = false;
	bool debug_mode = false;
	void spawnEnemy();
	void checkEnemy();
	void checkCollisionWarrior();
	void checkCollision();
	void CreateEnemies();
	void DrawEnemies();
	void UpdateEnemies();
	void checkEnemies();
	status_t status = STATUS_START;

	unsigned int window_width = WINDOW_WIDTH
		, window_height = WINDOW_HEIGHT;

	//ftiaxnoume ligo to paixnidi gia na ksexwrizoume tis othones
	void updateStartScreen();
	void updateLevelScreen();
	//draw
	void drawStartScreen();
	void drawLevelScreen();
	void EndScreen();
public:
	void setDebugMode(bool d) { debug_mode = d; }
	bool  getDebugMode() const { return debug_mode; }
	//den xreiazetai orisma,ta exei mesa sto game (i sta paidia tis)
	void update();
	//den xreiazetai orisma
	void draw();
	//gia na mporesw na tin kalesw gia na ksekinhsw ta dedomena mesa stin klasi mou
	void init();
	//default 
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