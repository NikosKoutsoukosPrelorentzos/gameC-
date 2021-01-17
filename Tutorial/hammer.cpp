#include "hammer.h"
#include "graphics.h"
#include "game.h"
#include "bullet.h"

Hammer::Hammer(const Game& mygame)
	: GameObject(mygame)
{
}

Bullet*  Hammer::currentBullet()
{
	if (bullet) {
		return bullet;
	}
	return nullptr;
}

void Hammer::update()
{
	float speed = 5.0f;
	if (graphics::getKeyState(graphics::SCANCODE_A)) {
		pos_x -= speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_D)) {
		pos_x += speed * graphics::getDeltaTime() / 10.0f;


	}
	if (graphics::getKeyState(graphics::SCANCODE_W)) {
		pos_y -= speed * graphics::getDeltaTime() / 10.0f;

	}
	if (graphics::getKeyState(graphics::SCANCODE_S)) {
		pos_y += speed * graphics::getDeltaTime() / 10.0f;

	}
	/*
	if (graphics::getKeyState(graphics::SCANCODE_DOWN)) {
		height -= 0.01f * graphics::getDeltaTime();

		if (height < 0.8f)
			height = 0.8f;
	}


	if (graphics::getKeyState(graphics::SCANCODE_UP)) {
		height += 0.01f * graphics::getDeltaTime();

		if (height > 2.0f)
			height = 2.0f;
	} */

	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH ;
	if (pos_y < 0) pos_y = 0;
	if (pos_y > CANVAS_HEIGHT) pos_y = CANVAS_HEIGHT;

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

	if (!flag) {
		bullet->update();
	}

	if (bullet && !bullet->isActive()) {
		delete bullet;
		bullet = nullptr;
		flag = true;
	}

}

void Hammer::draw()
{    //anavosvinei
	if (bullet) {
		bullet->draw();
	}
	float glow = 0.5f + 0.05f * sinf(graphics::getGlobalTime());
	graphics::Brush br;
	//h skia tou hammer
	br.outline_opacity = 0.0f;

	graphics::setScale(height, height);
	br.fill_opacity = 0.4f;
	br.texture = std::string(ASSET_PATH) + "hammer_shadow.png";
	graphics::drawRect(pos_x - 5*height, pos_y + 10*height, 45, 45, br);

	br.fill_opacity = 2.f;
	//To hammer
	br.texture = std::string(ASSET_PATH) + "hammer.png";
	graphics::drawRect(pos_x,pos_y,50,50,br);
	//scale sto 1 kai prosanatolismos reset
	graphics::resetPose();

	br.fill_color[0] = 0.3f + glow*0.5f;
	br.fill_color[1] = 0.1f + glow*0.5;
	br.fill_color[2] = 0.1f;
	br.fill_secondary_color[0] = 0.3f;
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 0.0f;
	//
	br.fill_opacity = 1.0f;
	br.fill_secondary_opacity = 0.0f;
	br.gradient = true;
	br.outline_opacity = 0.f;

	graphics::setScale(height, height);
	graphics::drawDisk(pos_x-20*height, pos_y*height, 10, br);
	graphics::resetPose();

	if (game.getDebugMode()) {
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

	
}

void Hammer::init()
{
}

Disk Hammer::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 30.0f;

	return disk;
}

void Hammer::deleteBullet()
{
	delete bullet;
	bullet = nullptr;
	flag = true;
}
