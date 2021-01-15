#include "player.h"
#include "graphics.h"
#include "game.h"

Player::Player(const Game& mygame)
	: GameObject(mygame)
{
	
}

void Player::update()
{
	
	if (graphics::getKeyState(graphics::SCANCODE_A))
	{
		pos_x -= speed * graphics::getDeltaTime()/10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_D))
	{
		pos_x += speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_W))
	{
		pos_y -= speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_S))
	{
		pos_y += speed * graphics::getDeltaTime() / 10.0f;
	}

	if (pos_x < 0) {
		pos_x = 0;
	}
	if (pos_x > CANVAS_WIDTH) {
		pos_x = CANVAS_WIDTH;
	}
	if (pos_y < 0)
	{
		pos_y = 0;
	}
	if (pos_y > CANVAS_HEIGHT)
	{
		pos_y = CANVAS_HEIGHT;
	}

	//Create Bullet

	if (!bullet) {
		bullet = new Bullet(game);
	}

	if (flag) {
		bullet->setX(pos_x);
		bullet->setY(pos_y);
	}

	graphics::MouseState ms;
	graphics::getMouseState(ms);
	
	if (ms.button_left_pressed) {
		flag = false;
	}

	if (!flag){
		bullet->update();
	}

	if (bullet && !bullet->isActive()) {
		delete bullet;
		bullet = nullptr;
		flag = true;
	}

	
}

void Player::draw()
{
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime()/10);
	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "ppo.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, 100, 100, br);
	br.texture = "";

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.5f + glow*0.5f;
	br.fill_color[2] = 0.0f;
	br.fill_secondary_color[0] = 0.3f;
	br.fill_secondary_color[1] = 0.1f;
	br.fill_secondary_color[2] = 0.0f;
	br.fill_opacity = 1.0f;
	br.fill_secondary_opacity = 0.0f;
	br.gradient = true;
	graphics::setScale(height, height);
	graphics::drawDisk(pos_x, pos_y+30, 20, br);
	graphics::resetPose();

	if (game.getDebugMode()) 
	{
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 0.3f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
 		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);
	}
	
	if (bullet) {
		bullet->draw();
	}
}

void Player::init()
{
}

Disk Player::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 55.0f;
	return disk;
}
