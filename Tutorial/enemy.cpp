#include "enemy.h"
#include "graphics.h"
#include "config.h"
#include "util.h"
#include "game.h"

void Enemy::update()
{

	switch (random)
	{
	case 1:
		pos_x -= speed * graphics::getDeltaTime() * rand0to1();
		break;
	case 2:
		pos_x += speed * graphics::getDeltaTime() * rand0to1();
		break;
	case 3:
		pos_y -= speed * graphics::getDeltaTime() * rand0to1();
		break;
	case 4:
		pos_y += speed * graphics::getDeltaTime() * rand0to1();
		break;
	case 5:
		pos_x -= speed * graphics::getDeltaTime() * rand0to1();
		pos_y -= speed * graphics::getDeltaTime() * rand0to1();
		break;
	case 6:
		pos_x += speed * graphics::getDeltaTime() * rand0to1();
		pos_y += speed * graphics::getDeltaTime() * rand0to1();
		break;
	case 7:
		pos_x += speed * graphics::getDeltaTime() * rand0to1();
		pos_y -= speed * graphics::getDeltaTime() * rand0to1();
		break;
	case 8:
		pos_x -= speed * graphics::getDeltaTime() * rand0to1();
		pos_y += speed * graphics::getDeltaTime() * rand0to1();
		break;
	default:
		break;
	}


	rotation += 0.05f * graphics::getDeltaTime();
	rotation = fmodf(rotation, 360);

	if (pos_x < -size || pos_y < -size || pos_x > CANVAS_WIDTH + size*2 || pos_y > CANVAS_HEIGHT + size*2) 
	{
		active = false;
	}

}

void Enemy::draw()
{
	graphics::setOrientation(rotation);
	brush.texture = std::string(ASSET_PATH) + "toilet.png";
	graphics::drawRect(pos_x, pos_y, size, size, brush);
	graphics::resetPose();

	

	if (game.getDebugMode())
	{
		graphics::Brush br;
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.3f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);
	}
}

void Enemy::init()
{
	size = 50 + 100 * rand0to1();
	speed = 1.0f * rand0to1();

	random = rand1to8();
	

	switch (random)
	{
	case 1:
		pos_x = CANVAS_WIDTH + 1.1f * size;
		pos_y = CANVAS_HEIGHT * rand0to1();
		break;
	case 2:
		pos_x = 0 - 1.1f * size;
		pos_y = CANVAS_HEIGHT * rand0to1();
		break;
	case 3:
		pos_x = CANVAS_WIDTH * rand0to1();
		pos_y = CANVAS_HEIGHT  + 1.1f * size;
		break;
	case 4:
		pos_x = CANVAS_WIDTH * rand0to1();
		pos_y = 0 - 1.1f * size;
		break;
	case 5:
		pos_x = CANVAS_WIDTH + 1.1f * size;
		pos_y = CANVAS_HEIGHT + 1.1f * size;
		break;
	case 6:
		pos_x = 0 - 1.1f * size;
		pos_y = 0 - 1.1f * size;
		break;
	case 7:
		pos_x = 0 - 1.1f * size;
		pos_y = CANVAS_HEIGHT + 1.1f * size;
		break;
	case 8:
		pos_x = CANVAS_WIDTH + 1.1f * size;
		pos_y = 0 - 1.1f * size;
		break;

	default:
		break;
	}

	rotation = 360 * rand0to1();
	brush.outline_opacity = 0.0f;
}

Enemy::Enemy(const Game& mygame)
	:GameObject(mygame)
{
	init();
}

Enemy::~Enemy()
{
}

Disk Enemy::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size/2;
	return disk;
}
