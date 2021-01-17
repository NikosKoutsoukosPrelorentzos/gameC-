#include "bullet.h"
#include "enemy.h"
#include "graphics.h"
#include "config.h"
#include "util.h"
#include "game.h"
#include "hammer.h"
#include <math.h>

void Bullet::update()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	if (!fired) {
		xBullet = pos_x;
		yBullet = pos_y;
		x = window2canvasX(ms.cur_pos_x);
		y = window2canvasY(ms.cur_pos_y);
		fired = true;
	}


	angle = atan2(y - yBullet, x - xBullet);

	dx = (cos(angle) * speed);
	dy = (sin(angle) * speed);

	pos_x += dx;
	pos_y += dy;

	if (pos_x < -BulletSize || pos_y < -BulletSize || pos_x > CANVAS_WIDTH + BulletSize * 2 || pos_y > CANVAS_HEIGHT + BulletSize * 2)
	{
		active = false;
	}

}

void Bullet::draw()
{

	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "bullet.png";
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
	speed = 3.0f;
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
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 1.0f;
	return disk;
}

float Bullet::window2canvasX(float x)
{

	return x * CANVAS_WIDTH / (float)window_width;
}

float Bullet::window2canvasY(float y)
{
	return y * CANVAS_HEIGHT / (float)window_height;
}

