#pragma once
#include "sgg/graphics.h"
#include <iostream>
#include <string>
#include <list>
using namespace std;
using namespace graphics;


class GameState
{
private:

	string m_asset_path = ".\\assets\\";

	float m_canvas_width = 14.0f;
	float m_canvas_height = 7.5f;

	static GameState* m_unique_instance;
	GameState();

	class Player* m_player = 0;
	class MouseCollisions* m_mouse_trap = 0;
	class MouseCollisions* m_mouse_trap2 = 0;
	class MouseCollisions* m_mouse_trap3 = 0;
	class MouseCollisions* m_cheese = 0;
	class MouseCollisions* m_cat = 0;
	class MouseCollisions* m_cat2 = 0;
	class MouseCollisions* m_scared_cat = 0;
	class Level* m_curr_level = 0;

	int score = 0;

public:

	float getCanvasWidth();
	float getCanvasHeight();

	void init();
	void draw();
	void update(float dt);

	void initializeCollisionObjects();
	void initializeCats(int random_pos);
	void initializeMouseTraps(int random_pos);
	void initializeCheese(int random_pos);

	static GameState* getInstance();
	~GameState();

	string getAssetDir();
	string getFullAssetPath(const string& asset);

	class Player* getPlayer() { return m_player; }
	class MouseCollisions* getTrap() { return m_mouse_trap; }
	class MouseCollisions* getTrap2() { return m_mouse_trap2; }
	class MouseCollisions* getTrap3() { return m_mouse_trap3; }
	class MouseCollisions* getCheese() { return m_cheese; }
	class MouseCollisions* getCat() { return m_cat; }
	class MouseCollisions* getCat2() { return m_cat2; }
	class MouseCollisions* getScaredCat() { return m_scared_cat; }

	void updateScore();
	void resetScore();
	int getScore();

	void quitGame();
};