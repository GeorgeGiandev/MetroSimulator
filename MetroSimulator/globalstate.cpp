#include "globalstate.h"
#include "util.h"
#include <ctime>
#include "station.h"
#include <vector>
#include <sgg/scancodes.h>
#include "level.h"
#include <string>

void GlobalState::init()
{
	std::srand(std::time(nullptr)); // to generate random numbers

	// starting stuff
	graphics::preloadBitmaps(getAssetDir());
	graphics::setFont(m_asset_path + "MontserratBold.ttf");
	
	m_current_level = new Level();
	m_current_level->init();

	// debug brush
	SETCOLOR(m_brush_debug.fill_color, 0.2f, 1.0f, 0.2f);
	m_brush_debug.fill_opacity = 0.65f;
	
}

void GlobalState::draw()
{
	m_current_level->draw();
	if (m_debugging)
	{
		std::string cur_mouse_pos = '(' + std::to_string(graphics::windowToCanvasX(ms.cur_pos_x))
			+ ',' + std::to_string(graphics::windowToCanvasY(ms.cur_pos_y)) + ')';
		graphics::drawText(0.5f, 0.5f, 0.5f, cur_mouse_pos, m_brush_debug);

	}

	if (!m_start)
	{
		graphics::Brush br;
		SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
		br.fill_opacity = 0.5f;
		graphics::drawText(m_canvas_width / 2.0f - 3.0f, 1.0f , 0.3f, "DRAW LINES AND PRESS ENTER TO START", br);
		graphics::drawText(m_canvas_width / 2.0f - 2.5f, 7.5f, 0.3f, "You can only build 5 reds and 4 blues", br);

	}

	if (m_game_over)
	{
		graphics::Brush br;
		SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
		graphics::drawText(m_canvas_width / 2.0f - 3.5f, m_canvas_height / 2.0f, 0.4f, "GAME OVER!  PRESS ENTER TO EXIT", br);
	}
}

void GlobalState::update(float dt)
{
	m_debugging = graphics::getKeyState(graphics::SCANCODE_0);
 	graphics::getMouseState(ms);
	
	if (m_start)
	{
		m_pause = graphics::getKeyState(graphics::SCANCODE_SPACE);

	}
	if (!m_start && graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		m_start = true;
	}
	m_current_level->update(dt);

}

GlobalState* GlobalState::getInstance()
{
	if (m_unique_instance == nullptr)
		m_unique_instance = new GlobalState();
	
	return m_unique_instance;
}

GlobalState::GlobalState()
{
	srand(time(nullptr)); // to not have the same random number every time
}

GlobalState::~GlobalState()
{	

}


graphics::MouseState& GlobalState::getGlobalMouseState()
{
	return ms;
}


std::string GlobalState::getAssetDir()
{
	return m_asset_path;
}

std::string GlobalState::getFullAssetPath(const std::string& asset)
{
	return m_asset_path + asset;
}



GlobalState* GlobalState::m_unique_instance = nullptr;