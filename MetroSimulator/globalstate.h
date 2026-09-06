#pragma once
#include <string>
#include <sgg/graphics.h>
#include "station.h"
#include <vector>
#include "rail.h"
#include "level.h"
#include "box.h"

class GlobalState
{
	float m_canvas_width = 16.0f;
	float m_canvas_height = 8.0f;

	std::string m_asset_path = "assets\\";

	graphics::Brush m_brush_debug;

	static GlobalState* m_unique_instance;

	Level* m_current_level;

	graphics::MouseState ms;


public:
	bool m_start = false;
	bool m_pause = true;
	bool m_game_over = false;
	bool m_debugging = false;

	void init();
	void draw();
	void update(float dt);

	static GlobalState* getInstance();
	GlobalState();
	~GlobalState();

	float getCanvasWidth() { return m_canvas_width; }
	float getCanvasHeight() { return m_canvas_height;  }

	graphics::MouseState& getGlobalMouseState ();

	std::string getAssetDir();
	std::string getFullAssetPath(const std::string& asset);


};