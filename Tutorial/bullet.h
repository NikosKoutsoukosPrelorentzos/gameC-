#pragma once
#include "gameobject.h"
#include "graphics.h"
#include "config.h"

class Bullet : public GameObject, public Collidable
{
	float xBullet;
	float yBullet;
	bool fired = false;
	float x;
	float y;
	float angle;
	double dx;
	double dy;
	bool flag = true;
	float height = 0.1f;
	float pos_x;
	float pos_y;
	float speed;
	float BulletSize = 2.0f;
	graphics::Brush brush;
	bool active = true;

	unsigned int window_width = WINDOW_WIDTH
		, window_height = WINDOW_HEIGHT;

public:
	float window2canvasX(float x);
	float window2canvasY(float y);
	void setX(float x) { pos_x = x; }
	void setY(float y) { pos_y = y; }
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() { return active; }
	Bullet(const class Game& mygame);
	~Bullet();
	Disk getCollisionHull() const override;
};
