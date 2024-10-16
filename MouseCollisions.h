#pragma once
#include "sgg/graphics.h"
#include "GameObject.h"
using namespace std;
using namespace graphics;

class MouseCollisions : public GameObject
{
	Brush m_brush_col;
	string m_ass_path = " ";

	float m_vel = 0.f;

	float m_col_pos_x = 14.0f * 1.5f;
	float m_col_pos_y = 7.5f * 0.5f;
	float m_col_size = 1.0f;

	int max_pos_y = 75;

public:

	MouseCollisions(string name, float size, string path, float velocity, float x_pos, float y_pos) 
		: GameObject(name){
		m_col_size = size;
		m_ass_path = path;
		m_vel = velocity;
		m_col_pos_x = x_pos;
		m_col_pos_y = y_pos;
	};

	void update(float dt) override;
	void init() override;
	void draw() override;

	void setXpos(float xpos);
	void setYpos(float ypos);

	float getXpos();
	float getYpos();
	float getSize();

	void incrXpos(float incr);
	void incrYpos(float incr);
	void incrVel(float incr);
};