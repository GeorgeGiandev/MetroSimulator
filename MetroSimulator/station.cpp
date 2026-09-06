#include "station.h"
#include "globalstate.h"
#include <sgg/graphics.h>
#include "util.h"
#include <cmath>

Station::Station(std::string name, float pos_x, float pos_y, float radius)
		: GameObject(name), pos_x(pos_x), pos_y(pos_y), radius(radius)
{

}

Station::~Station()
{
	for (auto p : m_people_waiting)
	{
		delete p;
	}
	m_people_waiting.clear();
}

void Station::init()
{
	SETCOLOR(m_brush_station.fill_color, 0.5f, 0.5f, 0.2f);
	SETCOLOR(m_brush_station.outline_color, 0.0f, 0.0f, 0.0f);
	m_brush_station.outline_opacity = 1.0f;

	SETCOLOR(m_brush_station_text.fill_color, 1.0f, 1.0f, 1.0f);
	SETCOLOR(m_brush_station_text.outline_color, 0.0f, 0.0f, 0.0f);
	m_brush_station_text.outline_opacity = 1.0f;

	SETCOLOR(m_brush_station_debug.fill_color, 0.1f, 1.0f, 0.1f);
	SETCOLOR(m_brush_station_debug.outline_color, 0.2f, 1.0f, 0.2f);
	m_brush_station_debug.fill_opacity = 0.1f;


	

}

void Station::draw()
{
	// draw stations
	graphics::drawDisk(pos_x, pos_y, radius, m_brush_station);

	graphics::drawText(pos_x - 0.1f, pos_y + 0.1f, text_size, m_name, m_brush_station_text);

	if (m_state->m_debugging)
		graphics::drawDisk(pos_x, pos_y, radius, m_brush_station_debug);

	// draw people waiting

	int count = 0;
	for (auto p : m_people_waiting)
	{
		p->offset_x = 0.4f + (count % 3) * 0.2f;
		p->offset_y = -0.4f + (count / 3) * 0.2f;
		p->draw();
		count++;
	}
}

void Station::update(float dt)
{
	if (m_people_waiting.size() >= 5) 
	{ 
		m_state->m_game_over = true;
	}
}

bool Station::contains(float x, float y)
{
	float dx = x - pos_x;
	float dy = y - pos_y;
	return std::sqrt(dx * dx + dy * dy) < radius;
}

void Station::addPassenger(Passenger* p)
{
	m_people_waiting.push_back(p);
}

std::deque<Passenger*>& Station::getPeople()
{
	return m_people_waiting;
}

float Station::getPosX()
{
	return pos_x;
}

float Station::getPosY()
{
	return pos_y;
}


