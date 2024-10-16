#include "Player.h"
#include "GameState.h"

void Player::update(float dt)
{
	float dt_sec = dt / 1000.0f;
	const float velocity = 8.0f;

	if (getKeyState(SCANCODE_DOWN))
	{
		if (m_player_pos_y < 7.f)
			m_player_pos_y += velocity * dt_sec;
	}
	if (getKeyState(SCANCODE_UP))
	{
		if (m_player_pos_y > 0.4f)
			m_player_pos_y -= velocity * dt_sec;
	}

	GameObject::update(dt);
}

void Player::init()
{
}

void Player::draw()
{
	m_brush_player.outline_opacity = 0;
	drawRect(m_player_pos_x, m_player_pos_y, 1.0f, 1.0f, m_brush_player);
}

bool Player::intersect(MouseCollisions& obj)
{
	bool intersect = (fabs(m_player_pos_x - obj.getXpos()) * 2.0f < (1.0f + obj.getSize())) &&
		(fabs(m_player_pos_y - obj.getYpos()) * 2.0f < (1.0f + obj.getSize()));
	return intersect;
}

void Player::setBrTexture(string path)
{
	m_brush_player.texture = path;
}
