#pragma once
#include "sgg/graphics.h"
#include "GameObject.h"
#include "MouseCollisions.h"
using namespace std;
using namespace graphics;

class Player : public GameObject
{
	Brush m_brush_player;

	float m_player_pos_x = 14.0f * 0.1f;
	float m_player_pos_y = 7.5f * 0.5f;
	float m_player_size = 1.0f;

public:
	Player(string name) : GameObject(name) {};

	void update(float dt) override;
	void init() override;
	void draw() override;
	bool intersect(MouseCollisions& obj);

	void setBrTexture(string path);
};