#pragma once
#include "gameobject.h"
#include "graphics.h"
class Enemy : public GameObject, public Collidable
{
	int random;
	float pos_x;
	float pos_y;
	float speed;
	float size;
	float rotation;
	graphics::Brush brush;
	bool active = true;

public:
	float getSize();
	void newRandom();
	void setSize(float newSize);
	void update() override;
	void draw() override;
	void init() override;
	bool isActive(){ return active; }
	Enemy(const class Game& mygame);
	~Enemy();
	Disk getCollisionHull() const override;
};