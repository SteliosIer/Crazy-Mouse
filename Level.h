#pragma once
#include "sgg/graphics.h"
#include <iostream>
#include <string>
#include <list>
#include "Player.h"
using namespace std;
using namespace graphics;

class Level : public GameObject
{
	typedef enum { 
		STATUS_START, 
		STATUS_STANDARD_PLAY,
		STATUS_MONSTER, 
		STATUS_COLLISION, 
		STATUS_ENDGAME 
	} status_t;


	status_t status = STATUS_START;
	Brush m_brush_background;
	float m_center_x = 5.0f;
	float m_center_y = 5.0f;
	
	int eatCheeseCounter = 0;
	int killCatCounter = 0;


public:

	void init() override;
	void update(float dt) override;
	void draw() override;

	Level(const string& name = "Level0");
	~Level();

	status_t getStatus() { return status; }
	void setStatus(status_t curr_status) { status = curr_status; }

	void drawBackground(float r, float g, float b);
	void drawStartScreen();
	void drawPlayingScreen();
	void drawGameObjects();
	void drawScore();
	void drawEndgame();

	void updateStartScreen();
	void updatePlayingScreen(float dt);
	void increaseCatTrapVelocity();
	void updateGameObjects(float dt);
	
	void updateMonsterLevel(float dt);
	void updateEndgame();
	void restart();

	void handleCollisions();
	void handleDeathCollisions();
	void handlePointGainCollisions();
	void resetCollisionObjectsPos();
	void updateKillCatCounter() { killCatCounter++; }
	void resetKillCatCounter() { killCatCounter = 0; }

	void updateEatCheeseCounter() { eatCheeseCounter++; }
	void resetEatCheeseCounter() { eatCheeseCounter = 0; }

};