#include <sgg/graphics.h>
#include <stdio.h>
#include <string>
#include "util.h"
#include "globalstate.h"


void init()
{
	GlobalState::getInstance()->init();
}

void draw()
{
	GlobalState::getInstance()->draw();

}

void update(float dt)
{
	GlobalState::getInstance()->update(dt);

}


int main(int argc, char** argv)
{
	graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Metro Simulator");

	init();
	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::setCanvasSize(GlobalState::getInstance()->getCanvasWidth(),
		GlobalState::getInstance()->getCanvasHeight());
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::startMessageLoop();

	return 0;
}