#include "game.h"
#include "graphics.h"
#include "config.h"


void Game::spawnMeteorite()
{
	if (!meteorite) {
		meteorite = new Enemy(*this);
	}

	if (!meteorite2) {
		meteorite2 = new Enemy(*this);
	}

	if (!meteorite3) {
		meteorite3 = new Enemy(*this);
	}
}

void Game::checkMeteorite()
{
	if (meteorite && !meteorite->isActive()) {
		delete meteorite;
		meteorite = nullptr;
	}
	if (meteorite2 && !meteorite2->isActive()) {
		delete meteorite2;
		meteorite2 = nullptr;
	}
	if (meteorite3 && !meteorite3->isActive()) {
		delete meteorite3;
		meteorite3 = nullptr;
	}
}

bool Game::checkCollision(Enemy *meteoritee)
{
	if (!player || !meteoritee) {
		return false;
	}
	Disk d1 = player->getCollisionHull();
	Disk d2 = meteoritee->getCollisionHull();
	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius) 
	{
		player->drainLife(0.1f);
		return true;
	}
	else
	{
		return false;
	}
}

void Game::updateStartScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
		status = STATUS_PLAYING;
	}
	
}

void Game::updateLevelScreen()
{
	if (!player_initialized && graphics::getGlobalTime() > 1000)
	{
		player = new Player(*this);
		player_initialized = true;
	}
	if (player)
	{
		player->update();
	}

	checkMeteorite();

	spawnMeteorite();


	if (meteorite) {
		meteorite->update();
	}

	if (meteorite2) {
		meteorite2->update();
	}

	if (meteorite3) {
		meteorite3->update();
	}


	if (checkCollision(meteorite))
	{
		delete meteorite;
		meteorite = nullptr;
	}

	if (checkCollision(meteorite2))
	{
		delete meteorite2;
		meteorite2 = nullptr;
	}

	if (checkCollision(meteorite3))
	{
		delete meteorite3;
		meteorite3 = nullptr;
	}
}

void Game::drawStartScreen()
{
	graphics::Brush br;
	char info[40];
	sprintf_s(info, "Press Enter to start");
	graphics::drawText(CANVAS_WIDTH/2, CANVAS_HEIGHT/2, 30, info, br);

}


void Game::drawLevelScreen()
{
	

	graphics::Brush br;
	
	br.texture = std::string(ASSET_PATH) + "bathroom_background.png";
	br.outline_opacity = 0.0f;

	//Draw Background
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);


	//Draw Player
	if (player)
	{
		player->draw();
	}
	//Draw Enemy
	if (meteorite) {
		meteorite->draw();
	}

	if (meteorite2) {
		meteorite2->draw();
	}

	if (meteorite3) {
		meteorite3->draw();
	}

	// UI/INFO LAYER

	if (player && debug_mode)
	{

		char info[40];
		sprintf_s(info, "(%f, %f)", player->getPosX(), player->getPosY());
		graphics::drawText(50, 50, 40, info, br);

	}

	float player_Life = player ? player->getRemainingLife() : 0.0f;
	br.outline_opacity = 1.0f;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 0.2f;
	br.texture = "";
	br.fill_secondary_color[0] = 1.0f * (1.0f - player_Life) + player_Life * 0.2f;
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 0.2f * (1.0f - player_Life) + player_Life * 1.0f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	graphics::drawRect(CANVAS_WIDTH - 100 - ((1.0f - player_Life) * 120 / 2), 30, player_Life * 120, 20, br);

	br.outline_opacity = 1.0f;
	br.gradient = false;
	br.fill_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH - 100, 30, 120, 20, br);

	graphics::Brush fr;

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	graphics::drawDisk(window2canvasX(ms.cur_pos_x), window2canvasY(ms.cur_pos_y), 10, fr);
}

void Game::update()
{
	if (status == STATUS_START)
	{
		updateStartScreen();

	}
	else
	{
		updateLevelScreen();
	}

	
}

void Game::draw()
{
	if (status == STATUS_START) {
		drawStartScreen();
	}
	else
	{
		drawLevelScreen();
	}

}


void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "youmurdererbb_reg.ttf");
	graphics::playMusic(std::string(ASSET_PATH) + "Elevator Music.mp3", 0.07f, true, 4000);
}

float Game::window2canvasX(float x)
{

	return x * CANVAS_WIDTH /(float)window_width;
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
	if (player)
	{
		delete player;
	}
}
