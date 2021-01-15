#include "bullet.h"
#include "enemy.h"
#include "graphics.h"
#include "config.h"
#include "util.h"
#include "game.h"
#include "player.h"


void Bullet::update()
{
	pos_x -= speed * graphics::getDeltaTime() * 0.2f;
}

void Bullet::draw()
{
	
	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "ppo.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, 30, 30, br);
	br.texture = "";

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.5f;
	br.fill_color[2] = 0.0f;
	br.fill_opacity = 1.0f;
	br.fill_secondary_opacity = 0.0f;
	br.gradient = true;
	graphics::setScale(height, height);
	graphics::resetPose();
}

void Bullet::init()
{
	//pos_x  game.playerX();

	pos_y = CANVAS_HEIGHT / 3;
	speed = 0.4f;
}

Bullet::Bullet(const Game& mygame)
	:GameObject(mygame)
{
	init();
}


Bullet::~Bullet()
{
}

Disk Bullet::getCollisionHull() const
{
	return Disk();
}

