#pragma once
#include "gameobject.h"
#include "sgg/graphics.h"
#include "rail.h"
#include "train.h"
#include "passenger.h"
#include "box.h"
#include "station.h"

class Level : GameObject
{
	graphics::Brush m_brush_background;
	graphics::Brush m_brush_level_text;
	graphics::Brush m_brush_pause;


	Station* m_start_station = nullptr; 
	std::string m_active_color = "blue.png"; // blue is the default

	std::vector<Box*> boxes;
	std::vector<Station*> stations;
	std::vector<Rail*> rails; // Rails added on level and not globalstate
	std::vector<Train*> trains;
	std::vector<Passenger*> passengers;

	std::vector<Station*> m_blue_rails;
	Train* m_blue_train = nullptr;
	std::vector<Station*> m_red_rails;
	Train* m_red_train = nullptr;

	int m_red_rails_count = 0;
	int m_blue_rails_count = 0;

	float m_passenger_spawn_timer = 0.0f;


public:
	void init() override;
	void draw() override;
	void update(float dt) override;
	Level();
	~Level();

};