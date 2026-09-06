#pragma once
#include "gameobject.h"
#include "rail.h"
#include "sgg/graphics.h"
#include <vector>
#include "passenger.h"

class Train : public GameObject
{
	std::vector<Station*>* m_route;	// belongs to level so we delete it in level
	int m_current_station = 0;
	float m_progress = 0.0f;
	float m_speed = 0.001f;
	float m_reverse = false;
	int m_capacity;

	graphics::Brush m_brush_train;
	graphics::Brush m_brush_train_text;
	graphics::Brush m_brush_train_debug;

	std::vector<Passenger*> m_current_passengers;
	
public:
	Train(std::vector<Station*>* route);
	~Train();
	void init() override;
	void draw() override;
	void update(float dt) override;

	void passenger_operations();
	void shiftStationIndex(int d);

};