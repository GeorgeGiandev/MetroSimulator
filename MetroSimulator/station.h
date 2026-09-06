#pragma once
#include <sgg/graphics.h>
#include "gameobject.h"
#include <string>
#include <deque>

class Passenger;

class Station : public GameObject
{
	float pos_x, pos_y;
	float radius;
	float text_size = 0.3f;

	graphics::Brush m_brush_station;
	graphics::Brush m_brush_station_text;
	graphics::Brush m_brush_station_debug;

	std::deque<Passenger*> m_people_waiting;



public:
	Station(std::string name, float pos_x, float pos_y, float radius);
	~Station();

	void init() override;
	void draw() override;
	void update(float dt) override;

	bool contains(float x, float y);
	void addPassenger(Passenger* p);
	std::deque<Passenger*>& getPeople();

	float getPosX();
	float getPosY();

	std::string getName() { return m_name;}


};