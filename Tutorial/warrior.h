#pragma once
#include "gameobject.h"
#include "config.h"

class Warrior :  public GameObject, public Collidable {
	float speed;
	float life = 1.0f;
	float pos_x = 0.9f* CANVAS_WIDTH, pos_y = CANVAS_HEIGHT / 2;

public:
	Warrior(const class Game& mygame);
	virtual void update() override;
	virtual void draw() override;
	virtual void init() override;
    float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }
	float getRemainingLife() const { return life; }
	void drainLife(float amount) { life = std::max<float>(0.0f, life - amount); }
	Disk getCollisionHull() const override;
		



};