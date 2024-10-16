#include "GameState.h"
#include "MouseCollisions.h"
#include "Level.h"
#include "Player.h"
#include <cstdlib>
#include <windows.h>

//HANDLE CANVAS
float GameState::getCanvasWidth()
{
	return m_canvas_width;
}

float GameState::getCanvasHeight()
{
	return m_canvas_height;
}

//INITIALIZE OBJECTS
void GameState::init()
{
	m_curr_level = new Level();
	m_curr_level->init();
	m_player = new Player("Mouse");
	m_player->init();

	initializeCollisionObjects();
	preloadBitmaps(getAssetDir());
}

void GameState::initializeCollisionObjects()
{
	srand(GetTickCount());
	int random_pos = rand() % 18;

	initializeMouseTraps(random_pos);
	initializeCats(random_pos);
	initializeCheese(random_pos);
}

void GameState::initializeCats(int random_pos)
{
	m_cat = new MouseCollisions("Cat", 1.0f, "angrycat.png", 12.f, 14.0f * 4.9f, 7.5f * (random_pos / 10));
	m_cat->init();
	m_cat2 = new MouseCollisions("Cat", 1.0f, "angrycat.png", 12.f, 14.0f * 14.9f, 7.5f * (random_pos / 10));
	m_cat2->init();
	m_scared_cat = new MouseCollisions("ScaredCat", 1.0f, "scared.png", 12.f, 14.0f * 4.9f, 7.5f * (random_pos / 10));
	m_scared_cat->init();
}

void GameState::initializeMouseTraps(int random_pos)
{
	m_mouse_trap = new MouseCollisions("Trap", 1.6f, "mouse trap.png", 4.f, 14.0f * 1.5f, 7.5f * (random_pos / 10));
	m_mouse_trap->init();
	m_mouse_trap2 = new MouseCollisions("Trap2", 1.6f, "mouse trap.png", 4.f, 14.0f * 2.8f, 7.5f * (random_pos / 10));
	m_mouse_trap2->init();
	m_mouse_trap3 = new MouseCollisions("Trap3", 1.6f, "mouse trap.png", 4.f, 14.0f * 2.8f, 7.5f * (random_pos / 10));
	m_mouse_trap3->init();
}

void GameState::initializeCheese(int random_pos)
{
	m_cheese = new MouseCollisions("Cheese", 0.7f, "cheese.png", 7.f, 14.0f * 2.9f, 7.5f * (random_pos / 10));
	m_cheese->init();
}


//DRAW UPDATE
void GameState::draw()
{
	if (!m_curr_level)
	{
		return;
	}

	m_curr_level->draw();
}

void GameState::update(float dt)
{
	if (dt > 500)
	{
		return;
	}

	if (!m_curr_level)
	{
		return;
	}
	m_curr_level->update(dt);
}


//ASSET PATH HANDLING
string GameState::getAssetDir()
{
	return m_asset_path;
}

string GameState::getFullAssetPath(const string& asset)
{
	return m_asset_path + asset;
}


//SCORE HANDLING
void GameState::updateScore()
{
	score = score + 1;
}

void GameState::resetScore()
{
	score = 0;
}

int GameState::getScore()
{
	return score;
}


//CONSTRUCTOR DESTRUCTOR
GameState::GameState()
{
}

GameState::~GameState()
{
	if (m_player)
		delete m_player;
	if (m_cat)
		delete m_cat;
	if (m_cat2)
		delete m_cat2;
	if (m_scared_cat)
		delete m_scared_cat;
	if (m_cheese)
		delete m_cheese;
	if (m_mouse_trap)
		delete m_mouse_trap;
	if (m_mouse_trap2)
		delete m_mouse_trap2;
	if (m_mouse_trap3)
		delete m_mouse_trap3;
	if (m_curr_level)
		delete m_curr_level;
}

void GameState::quitGame()
{
	stopMessageLoop();
}


//HANDLE INSTASCE
GameState* GameState::getInstance()
{
	if (m_unique_instance == nullptr)
	{
		m_unique_instance = new GameState();
	}
	return m_unique_instance;
}

GameState* GameState::m_unique_instance = nullptr;