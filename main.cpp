#include "sgg/graphics.h"
#include "GameState.h"
#include <iostream>
#include <string>
#include "util.h"
using namespace std;
using namespace graphics;

void draw()
{
	GameState::getInstance()->draw();
}

void update(float dt)
{
	GameState::getInstance()->update(dt);

}

void init()
{
	GameState::getInstance()->init();
}

int main(int argc, char** argv)
{
	createWindow(1400, 750, "Crazy Mouse");
	init();

	setUpdateFunction(update);
	setDrawFunction(draw);

	setCanvasSize(GameState::getInstance()->getCanvasWidth(), GameState::getInstance()->getCanvasHeight());
	setCanvasScaleMode(CANVAS_SCALE_FIT);
	startMessageLoop();
	return 0;
}