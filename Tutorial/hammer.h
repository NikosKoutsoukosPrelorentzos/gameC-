#pragma once
#include "gameobject.h"
#include "config.h"
#include "bullet.h"
class Hammer : public GameObject, public Collidable {
	float speed;
	Bullet* bullet = nullptr;
	bool flag = true;
	int score = 0;
	float pos_x = CANVAS_WIDTH/8, pos_y=CANVAS_HEIGHT/2;
	float height = 1.0f;
	float life = 1.0f;
public:
	Hammer(const class Game & mygame);

	Bullet* currentBullet();

	virtual void update() override;
	virtual void draw() override;
	virtual void init() override;
	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }
	Disk getCollisionHull() const override;
	float getRemainingLife() const { return life; }
	void drainLife(float amount) { life = std::max<float>(0.0f, life - amount); }
	void addScore(int amount) { score += amount; }
	void reduceScore(int amount) { score -= amount; }
	int getScore() { return score; }
	void deleteBullet();
};