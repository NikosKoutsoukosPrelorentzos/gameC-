#include "game.h"
#include "graphics.h"
#include "config.h"
#include <list>
#include <vector> 

//create enemies
void Game::CreateEnemies() {
	if (enemies.empty()) {
		for (int i = 0; i < 10; ++i) {
			//enemies.at(i) = new Enemy(*this);
			enemies.push_back(new Enemy(*this));
		}
	}
	

}
//update enemies
void Game::UpdateEnemies() {
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies.at(i)) {
			enemies.at(i)->update();
		}
	}
}
//draw enemies
void Game::DrawEnemies() {
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies.at(i)) {
			enemies.at(i)->draw();
		}
	}
}



void Game::spawnEnemy() {

	if(!enemy)
	enemy = new Enemy(*this);

}


void Game::checkEnemies() {
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies.at(i) && !enemies.at(i)->isActive()) {
			delete enemies.at(i);
			enemies.at(i) = nullptr;
			enemies.at(i) = new Enemy(*this);
		}
	}

}
void Game::checkEnemy() {

	if (enemy && !enemy->isActive()) {
		delete enemy;
		enemy = nullptr;
	}
}

void Game::checkCollisionWarrior()
{   
	if (warrior) {
		Disk d1 = warrior->getCollisionHull();

		for (int i = 0; i < enemies.size(); i++) {

			Disk d2 = enemies.at(i)->getCollisionHull();


			float dx = d1.cx - d2.cx;
			float dy = d1.cy - d2.cy;

			if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {

				warrior->drainLife(0.001f * (enemies.at(i)->getSize()));
				delete enemies.at(i);
				enemies.at(i) = nullptr;
				enemies.at(i) = new Enemy(*this);
				graphics::playSound(std::string(ASSET_PATH) + "cat.mp3", 0.4f, false);
			}


		}


	}
}

void Game::checkCollision()
{
	if (hammer) {

		Disk d1 = hammer->getCollisionHull();

		for (int i = 0; i < enemies.size(); i++) {
			bullet = hammer->currentBullet();

			Disk d2 = enemies.at(i)->getCollisionHull();

			if (bullet) {
				Disk d3 = bullet->getCollisionHull();
				float dx2 = d3.cx - d2.cx;
				float dy2 = d3.cy - d2.cy;
				if (sqrt(dx2 * dx2 + dy2 * dy2) < d3.radius + d2.radius) {
					hammer->addScore(25 * enemies.at(i)->getSize());
					
					graphics::playSound(std::string(ASSET_PATH) + "cat.mp3", 0.4f, false);
					hammer->deleteBullet();
					if (enemies.at(i)->getSize() > 50.0f) {
						
						enemies.at(i)->setSize(enemies.at(i)->getSize() * 0.6f);
						enemies.at(i)->newRandom();
					}
					else {
						delete enemies.at(i);
						enemies.at(i) = nullptr;
						enemies.at(i) = new Enemy(*this);
					}

				}
			}
			float dx = d1.cx - d2.cx;
			float dy = d1.cy - d2.cy;

			if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) {

				hammer->drainLife(0.001f * (enemies.at(i)->getSize()));
				enemies.at(i) = nullptr;
				enemies.at(i) = new Enemy(*this);
				graphics::playSound(std::string(ASSET_PATH) + "cat.mp3", 0.4f, false);

			}

		}
	}
}
void Game::updateStartScreen(){
	if(graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		status = STATUS_PLAYING;
		
	}
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	if (ms.button_left_pressed) {
		status = STATUS_PLAYING;
	}
}

void Game::updateLevelScreen() {
	if (graphics::getGlobalTime() > 2000 && !hammer_initialized && !warrior_initialized) {
		hammer = new Hammer(*this);
		warrior = new Warrior(*this);

		hammer_initialized = true;
		warrior_initialized = true;


	}


	if (hammer) {
		if (hammer->getRemainingLife() == 0.0f) {
			status = STATUS_END;
		}
		hammer->update();
	}

	if (warrior) {
		if (warrior->getRemainingLife() == 0.0f) {
			status = STATUS_END;
		}
		warrior->update();
	}

	CreateEnemies();
	
	UpdateEnemies();
	checkEnemies();
	
	
	//checkEnemy();
	//spawnEnemy();

	//if (enemy) {
		//enemy->update();
	//}

	checkCollisionWarrior();

	checkCollision();

	
	
}
	


void Game::drawStartScreen()
{
	graphics::Brush br;
	char infos[40];
	sprintf_s(infos, "Press\n ENTER \nto \nstart");
	graphics::drawText(CANVAS_WIDTH * 0.4f, CANVAS_HEIGHT/4,20,infos ,br);
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	graphics::drawDisk(window2canvasX(ms.cur_pos_x), window2canvasY(ms.cur_pos_y), 10, br);
	


}

void Game::drawLevelScreen()
{

	//FTIAXNW ENA BACKGROUND ME METHODO POU FTIANXEI KOUTIA.
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "moon.png";
	br.outline_opacity = 0.0f;
	//allazei analoga me ton xrono
	float offset = CANVAS_HEIGHT * sinf(graphics::getGlobalTime() / 10.0f) / 2;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	//draw hammer
	if (hammer) {
		hammer->draw();
	}

	if (warrior) {
		warrior->draw();
	}

	/*if (enemy) {
		enemy->draw();
	}
	*/
	//ui { --- INFO LAYER ---  }
	DrawEnemies();




	if (hammer && debug_mode) {
		char info[40];
		sprintf_s(info, "(%6.2f,%6.2f)", hammer->getPosX(), hammer->getPosY());
		graphics::drawText(20, 30, 10, info, br);
	}

	if (warrior && debug_mode) {
		char infos[40];
		sprintf_s(infos, "(%6.2f,%6.2f)", warrior->getPosX(), warrior->getPosY());
		graphics::drawText(CANVAS_WIDTH - 150, 30, 10, infos, br);
	}

	//score
	if (hammer) {
		char info[40];
		sprintf_s(info, "Score is: %d" , hammer->getScore());
		graphics::drawText(CANVAS_WIDTH*0.7f , 50, 15, info, br);
	}
	//HAMMER

	float hammer_life = hammer ? hammer->getRemainingLife() : 0.0f;

	br.outline_opacity = 0.0f;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.5f;
	br.fill_color[2] = 0.5f;
	br.texture = "";
	br.fill_secondary_color[0] = 0.0f;
	br.fill_secondary_color[1] = 0.0f;
	br.fill_secondary_color[2] = 1.0f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 6 - (1.0f - hammer_life) * 60, CANVAS_HEIGHT * 0.9f, hammer_life * 120, 20, br);


	br.outline_opacity = 1.0f;
	br.gradient = false;
	br.fill_opacity = 0.0f; //den exei gemisma
	graphics::drawRect(CANVAS_WIDTH / 6, CANVAS_HEIGHT * 0.9f, 120, 20, br);

	//WARRIOR
	float warrior_life = warrior ? warrior->getRemainingLife() : 0.0f;

	br.outline_opacity = 0.0f;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.5f;
	br.fill_color[2] = 0.5f;
	br.texture = "";
	br.fill_secondary_color[0] = 0.0f;
	br.fill_secondary_color[1] = 0.0f;
	br.fill_secondary_color[2] = 1.0f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	graphics::drawRect(CANVAS_WIDTH - 100 - (1.0f - warrior_life) * 60, CANVAS_HEIGHT * 0.9f, warrior_life * 120, 20, br);


	br.outline_opacity = 1.0f;
	br.gradient = false;
	br.fill_opacity = 0.0f; //den exei gemisma
	graphics::drawRect(CANVAS_WIDTH - 100, CANVAS_HEIGHT * 0.9f, 120, 20, br);


	graphics::Brush fr;

	graphics::MouseState ms;
	graphics::getMouseState(ms);
	fr.texture = std::string(ASSET_PATH) + "target.png";
	fr.outline_opacity = 0.0f;
	fr.gradient = false;
	graphics::drawRect(window2canvasX(ms.cur_pos_x), window2canvasY(ms.cur_pos_y), 30, 30, fr);

}


void Game::EndScreen()
{
	graphics::Brush br;
	char infos[40];
	sprintf_s(infos, "BYEEE!!!!");
	graphics::drawText(CANVAS_WIDTH * 0.4f, CANVAS_HEIGHT / 4, 20, infos, br);
}



void Game::update()
{
	if (status == STATUS_START) {
		updateStartScreen();
	}
	else if (status == STATUS_PLAYING) {
		updateLevelScreen();
	}

}


	

void Game::draw() {
	if (status == STATUS_START) {
		drawStartScreen();
	}
	else if (status == STATUS_PLAYING) {
		drawLevelScreen();
	}
	else if (status == STATUS_END) {
		EndScreen();
	}
}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "GulagDecay.ttf");
	graphics::playMusic(std::string(ASSET_PATH) + "motherland.mp3", 0.4f, true, 4000);
}




	float Game::window2canvasX(float x)
	{

		return x * CANVAS_WIDTH / (float)window_width;
	}

	float Game::window2canvasY(float y)
	{
		return y * CANVAS_HEIGHT / (float)window_height;
	}


Game::Game()
{
}

Game::~Game()
{
	if (hammer) {
		delete hammer;
	}

	if (warrior) {
		delete warrior;
	}

	if (enemy) {
		delete enemy;
	}
	if (bullet) {
		delete bullet;
	}
}
