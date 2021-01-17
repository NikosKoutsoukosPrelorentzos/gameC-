#include "warrior.h"
#include "graphics.h"
#include "game.h"
Warrior::Warrior(const Game& mygame)
	:GameObject(mygame)
{ 
}
void Warrior::update()
{
	float speed = 9.0f;
	if (graphics::getKeyState(graphics::SCANCODE_DELETE)) {
		pos_x -= speed * graphics::getDeltaTime() / 10.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_PAGEDOWN)) {
		pos_x += speed * graphics::getDeltaTime() / 10.0f;


	}
	if (graphics::getKeyState(graphics::SCANCODE_HOME)) {
		pos_y -= speed * graphics::getDeltaTime() / 10.0f;

	}
	if (graphics::getKeyState(graphics::SCANCODE_END)) {
		pos_y += speed * graphics::getDeltaTime() / 10.0f;

	}

	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;
	if (pos_y < 0) pos_y = 0;
	if (pos_y > CANVAS_HEIGHT) pos_y = CANVAS_HEIGHT;

}

void Warrior::draw()
{    //anavosvinei
	float glow = 0.5f + 0.05f * sinf(graphics::getGlobalTime());
	graphics::Brush br;
	//h skia tou hammer
	br.outline_opacity = 0.0f;
	br.fill_opacity = 0.4f;
	br.texture = std::string(ASSET_PATH) + "warrior_shadow.png";
	graphics::drawRect(pos_x + 20, pos_y- 40, 50, 50, br);

	br.fill_opacity = 2.f;

	//To warrior
	br.texture = std::string(ASSET_PATH) + "warrior.png";
	graphics::drawRect(pos_x, pos_y, 65, 65, br);


	br.fill_color[0] = 0.1f;
	br.fill_color[1] = 0.5f + glow*0.5f;
	br.fill_color[2] = 0.0f;
	br.fill_secondary_color[0] = 0.3f;
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 0.0f;
	//
	br.fill_opacity = 1.0f;
	br.fill_secondary_opacity = 0.0f;
	br.gradient = true;
	br.outline_opacity = 0.f;
	graphics::drawDisk(pos_x-20, pos_y, 10, br);


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

void Warrior::init()
{
}

Disk Warrior::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius =  65.0f* 0.5f;

	return disk;
}
