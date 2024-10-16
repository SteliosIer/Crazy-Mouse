#include "MouseCollisions.h"
#include "GameState.h"
#include <cstdlib>
#include <windows.h>

void MouseCollisions::update(float dt)
{
	srand(GetTickCount());
	float dt_sec = dt / 1000.0f;
	m_col_pos_x -= m_vel * dt_sec;

	if (m_col_pos_x < -10) {
		m_col_pos_x = 14.0f * 1.5f;
		int random_num_y = rand() % max_pos_y;
		m_col_pos_y = random_num_y/10;
	}

	GameObject::update(dt);
}

void MouseCollisions::init()
{
	m_brush_col.texture = m_state->getFullAssetPath(m_ass_path);
}

void MouseCollisions::draw()
{
	m_brush_col.outline_opacity = 0;
	drawRect(m_col_pos_x * 0.7f, m_col_pos_y , m_col_size, m_col_size, m_brush_col);
}

//HANDLE POSITION
void MouseCollisions::setXpos(float xpos)
{
	m_col_pos_x = xpos;
}

void MouseCollisions::setYpos(float ypos)
{
	m_col_pos_y = ypos;
}

float MouseCollisions::getXpos()
{
	return m_col_pos_x;
}

float MouseCollisions::getYpos()
{
	return m_col_pos_y;
}

float MouseCollisions::getSize()
{
	return m_col_size;
}

void MouseCollisions::incrXpos(float incr) 
{ 
	m_col_pos_x = +incr; 

}

void MouseCollisions::incrYpos(float incr) 
{ 
	m_col_pos_y = +incr; 
}

//HANDLE VELOCITY
void MouseCollisions::incrVel(float incr) 
{ 
	m_vel += incr; 
}