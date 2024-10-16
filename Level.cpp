#include "Level.h"
#include "Player.h"
#include "MouseCollisions.h"
#include "GameState.h"
#include "util.h"

void Level::update(float dt)
{
	if (status == STATUS_START)
	{
		updateStartScreen();
	}

	if (status == STATUS_STANDARD_PLAY)
	{
		updatePlayingScreen(dt);
	}

	if (status == STATUS_MONSTER)
	{
		updateMonsterLevel(dt);
	}

	if (status == STATUS_ENDGAME)
	{
		updateEndgame();
	}

	GameObject::update(dt);
}

void Level::draw()
{
	if (status == STATUS_START)
	{
		drawBackground(0.6f, 0.8f, 0.9f);
		drawStartScreen();
	}

	if (status == STATUS_STANDARD_PLAY)
	{
		drawBackground(0.6f, 0.8f, 0.9f);
		m_brush_background.texture = "";
		drawPlayingScreen();
	}

	if (status == STATUS_MONSTER)
	{
		drawBackground(1.0f, 1.0f, 1.0f);
		m_brush_background.texture = m_state->getFullAssetPath("evilback.png");
		drawPlayingScreen();
	}

	if (status == STATUS_ENDGAME)
	{
		drawEndgame();
	}
}

void Level::init()
{
}


//DRAW FUNCTIONS

void Level::drawBackground(float r, float g, float b)
{
	SETCOLOR(m_brush_background.fill_color, r, g, b);

	float canvas_width = m_state->getCanvasWidth();
	float canvas_height = m_state->getCanvasWidth();

	drawRect(canvas_width / 2.0f, canvas_height / 2.0f,
		canvas_width, canvas_height,
		m_brush_background);
}

void Level::drawStartScreen()
{
	setFont(m_state->getFullAssetPath("HOMOARAK.ttf"));

	Brush br;
	SETCOLOR(br.fill_color, 0.7f, 0.3f, 1.0f);;
	char info[40];
	char info2[40];
	sprintf_s(info, "CRAZY MOUSE");
	sprintf_s(info2, "PRESS ENTER TO PLAY");
	drawText(m_state->getCanvasWidth() / 3.5, m_state->getCanvasHeight() / 2.0, 0.7, info, br);

	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	br.texture = m_state->getFullAssetPath("mouse.png");
	br.outline_opacity = 0;
	drawRect(m_state->getCanvasWidth() / 3.5, m_state->getCanvasHeight() / 2.3, 1.5,1.5, br);

	SETCOLOR(br.fill_color, 0.7f, 0.95f, 0.95f);
	drawText(m_state->getCanvasWidth() / 1.5, m_state->getCanvasHeight() / 1.1, 0.3, info2, br);
}

void Level::drawPlayingScreen()
{
	drawGameObjects();
	drawScore();
}

void Level::drawGameObjects()
{
	if (m_state->getPlayer()->isActive())
	{
		m_state->getPlayer()->draw();
	}
	if (m_state->getTrap()->isActive())
	{
		m_state->getTrap()->draw();
	}
	if (m_state->getTrap2()->isActive())
	{
		m_state->getTrap2()->draw();
	}
	if (m_state->getCheese()->isActive())
	{
		m_state->getCheese()->draw();
	}

	if (status == STATUS_STANDARD_PLAY)
	{
		if (m_state->getCat()->isActive())
		{
			m_state->getCat()->draw();
		}
		if (m_state->getCat2()->isActive())
		{
			m_state->getCat2()->draw();
		}
	}
	if (status == STATUS_MONSTER)
	{
		if (m_state->getScaredCat()->isActive())
		{
			m_state->getScaredCat()->draw();
		}
		if (m_state->getTrap3()->isActive())
		{
			m_state->getTrap3()->draw();
		}
	}
}

void Level::drawScore()
{
	setFont(m_state->getFullAssetPath("Zombie.otf"));
	Brush br;
	SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.0f);
	int sc = m_state->getScore();
	drawText(m_state->getCanvasWidth() / 1.2, m_state->getCanvasHeight() / 11.7, 0.4, "SCORE:   " + to_string(sc), br);
}

void Level::drawEndgame()
{
	setFont(m_state->getFullAssetPath("HOMOARAK.ttf"));
	Brush br;
	SETCOLOR(br.fill_color, 0.0f, 0.0f, 1.0f);
	char info[40];
	
	if (m_state->getScore() >= 10)
	{
		drawBackground(0.2, 0.8, 0.6);
		SETCOLOR(br.fill_color, 0.0f, 1.0f, 0.8f);
		sprintf_s(info, "YOU WON!! PRESS ESC TO QUIT GAME..");
		drawText(m_state->getCanvasWidth() / 9.0, m_state->getCanvasHeight() / 2.0, 0.5, info, br);
	}
	else {
		drawBackground(0.0f, 0.0f, 0.0f);
		SETCOLOR(br.fill_color, 1.0f, 0.0f, 0.0f);
		sprintf_s(info, "YOU LOST.. PRESS ESC TO QUIT GAME..");
		drawText(m_state->getCanvasWidth() / 9.0, m_state->getCanvasHeight() / 2.0, 0.5, info, br);
	}
	sprintf_s(info, "PRESS BACKSPACE TO RESTART");
	drawText(m_state->getCanvasWidth() / 9.0, m_state->getCanvasHeight() / 1.7, 0.5, info, br);
}


 //UPDATE FUNCTIONS

void Level::updateStartScreen()
{
	if (getKeyState(SCANCODE_RETURN))
	{
		status = STATUS_STANDARD_PLAY;
	}
}

void Level::updatePlayingScreen(float dt)
{
	m_state->getPlayer()->setBrTexture(m_state->getFullAssetPath("mouse.png"));
	updateGameObjects(dt);
	handleCollisions();
	if (eatCheeseCounter == 3)
	{
		resetEatCheeseCounter();
		status = STATUS_MONSTER;
	}

	if (m_state->getScore() >= 15)
	{
		status = STATUS_ENDGAME;
	}
}

void Level::updateGameObjects(float dt)
{
	if (m_state->getPlayer()->isActive())
	{
		m_state->getPlayer()->update(dt);
	}
	if (m_state->getTrap()->isActive())
	{
		m_state->getTrap()->update(dt);
	}
	if (m_state->getTrap2()->isActive())
	{
		m_state->getTrap2()->update(dt);
	}
	if (m_state->getCheese()->isActive())
	{
		m_state->getCheese()->update(dt);
	}

	if (status == STATUS_STANDARD_PLAY)
	{
		if (m_state->getCat()->isActive())
		{
			m_state->getCat()->update(dt);
		}
		if (m_state->getCat2()->isActive())
		{
			m_state->getCat2()->update(dt);
		}
	}
	if (status == STATUS_MONSTER)
	{
		if (m_state->getScaredCat()->isActive())
		{
			m_state->getScaredCat()->update(dt);
		}
		if (m_state->getTrap3()->isActive())
		{
			m_state->getTrap3()->update(dt);
		}
	}

}

void Level::updateMonsterLevel(float dt)
{
	m_state->getPlayer()->setBrTexture(m_state->getFullAssetPath("monster.png"));
	updateGameObjects(dt);
	handleCollisions();

	if (killCatCounter == 2)
	{
		resetKillCatCounter();
		resetCollisionObjectsPos();
		status = STATUS_STANDARD_PLAY;
	}

	if (m_state->getScore() >= 10)
	{
		status = STATUS_ENDGAME;
	}
}

void Level::updateEndgame()
{
	if (getKeyState(SCANCODE_ESCAPE))
	{
		m_state->quitGame();
	}
	if (getKeyState(SCANCODE_BACKSPACE))
	{
		restart();
	}
}

void Level::restart()
{
	m_state->resetScore();
	resetKillCatCounter();
	resetEatCheeseCounter();
	m_state->initializeCollisionObjects();
	status = STATUS_STANDARD_PLAY;
}


// HELPING FUNCTIONS

void Level::handleCollisions()
{
	handleDeathCollisions();
	handlePointGainCollisions();
}

void Level::handleDeathCollisions()
{
	if (m_state->getCat()->isActive()) {
		if ((m_state->getPlayer()->intersect(*m_state->getCat()))) {
			status = STATUS_ENDGAME;
		}
	}

	if (m_state->getTrap()->isActive()) {
		if ((m_state->getPlayer()->intersect(*m_state->getTrap()))) {
			if (status == STATUS_STANDARD_PLAY)
			{
				status = STATUS_ENDGAME;
			}
			else if (status == STATUS_MONSTER)
			{
				status = STATUS_STANDARD_PLAY;
			}
		}
	}

	if (m_state->getTrap2()->isActive()) {
		if ((m_state->getPlayer()->intersect(*m_state->getTrap2()))) {
			if (status == STATUS_STANDARD_PLAY)
			{
				status = STATUS_ENDGAME;
			}
			else if (status == STATUS_MONSTER)
			{
				status = STATUS_STANDARD_PLAY;
			}
		}
	}

	if (m_state->getTrap3()->isActive()) {
		if ((m_state->getPlayer()->intersect(*m_state->getTrap3()))) {
			if (status == STATUS_STANDARD_PLAY)
			{
				status = STATUS_ENDGAME;
			}
			else if (status == STATUS_MONSTER)
			{
				status = STATUS_STANDARD_PLAY;
			}
		}
	}
}

void Level::handlePointGainCollisions()
{
	srand(time(NULL));
	if (m_state->getCheese()->isActive()) {
		if ((m_state->getPlayer()->intersect(*m_state->getCheese()))) {
			m_state->getCheese()->incrXpos(40.0f);
			m_state->getCheese()->incrYpos(rand());
			m_state->updateScore();
			increaseCatTrapVelocity();
			updateEatCheeseCounter();
		}
	}

	if (m_state->getScaredCat()->isActive()) {
		if ((m_state->getPlayer()->intersect(*m_state->getScaredCat()))) {
			m_state->getScaredCat()->incrXpos(40.0f);
			m_state->getScaredCat()->incrYpos(rand());
			m_state->updateScore();
			m_state->updateScore();
			increaseCatTrapVelocity();
			updateKillCatCounter();
		}
	}
}

void Level::increaseCatTrapVelocity()
{
	if (m_state->getTrap()->isActive())
	{
		m_state->getTrap()->incrVel(0.5f);
	}
	if (m_state->getTrap2()->isActive())
	{
		m_state->getTrap2()->incrVel(0.5f);
	}
	if (m_state->getCat()->isActive())
	{
		m_state->getCat()->incrVel(0.5f);
	}
	if (m_state->getCat2()->isActive())
	{
		m_state->getCat2()->incrVel(0.5f);
	}
}

void Level::resetCollisionObjectsPos()
{
	if (m_state->getTrap()->isActive())
	{
		m_state->getTrap()->setXpos(14.0f * 1.5f);
	}
	if (m_state->getTrap2()->isActive())
	{
		m_state->getTrap2()->setXpos(14.0f * 2.8f);
	}
	if (m_state->getCat()->isActive())
	{
		m_state->getCat()->setXpos(14.0f * 4.9f);
	}
	if (m_state->getCat2()->isActive())
	{
		m_state->getCat2()->setXpos(14.0f * 14.9f);
	}
}


//CONSTRUCTOR/ DESTRUCTOR

Level::Level(const string& name) : GameObject(name)
{
}

Level::~Level()
{
}










