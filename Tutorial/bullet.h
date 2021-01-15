#pragma once
#include "gameobject.h"
#include "graphics.h"
#include "game.h"

class Bullet : public GameObject, public Collidable
{
	float height = 1.0f;
	float pos_x;
	float pos_y;
	float speed;
	float size;
	graphics::Brush brush;
	bool active = true;

public:
	void setXY(float x, float y);
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() { return active; }
	Bullet(const class Game& mygame);
	~Bullet();
	Disk getCollisionHull() const override;
};
