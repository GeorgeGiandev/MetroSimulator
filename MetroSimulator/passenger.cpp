#include "passenger.h"
#include "util.h"
#include <random>


Passenger::Passenger(Station* start, Station* end)
	:GameObject("Passenger"), m_arrival(start), m_departure(end), offset_x(0), offset_y(0)
{
}

void Passenger::init()
{
	SETCOLOR(m_brush_passenger.fill_color, 1.0f, 1.0f, 1.0f); 
	m_brush_passenger.outline_opacity = 1.0f;
	SETCOLOR(m_brush_passenger.outline_color, 1.0f, 1.0f, 1.0f);
	m_brush_passenger.outline_opacity = 1.0f;

	SETCOLOR(m_brush_passenger_text.fill_color, 0.0f, 0.0f, 0.0f);
	m_brush_passenger_text.fill_opacity = 1.0f;

}

void Passenger::draw()
{
	if (m_arrival) {
		float pos_x = m_arrival->getPosX();
		float pos_y = m_arrival->getPosY();

		graphics::drawDisk(pos_x + offset_x, pos_y + offset_y, 0.08f, m_brush_passenger);
		graphics::drawText(pos_x + offset_x - 0.057f, pos_y + offset_y + 0.06f, 0.16f, m_departure->getName(), m_brush_passenger_text);
	}
}

void Passenger::update(float dt)
{
}

void Passenger::setPath(std::vector<Station*> newPath)
{
	m_path = newPath;
	m_path_index = 0;
}

Station* Passenger::getNextTarget()
{
	if (m_path.empty() || m_path_index >= m_path.size() - 1) return nullptr;
	return m_path[m_path_index + 1];
}

void Passenger::advancePath()
{
	if (m_path_index < m_path.size() - 1)
	{
		m_path_index++;
	}
}

bool Passenger::hasReachedDestination()
{
	if (m_path.empty()) return false;
	return m_path[m_path_index] == m_departure;
}

void Passenger::setArrival(Station* s)
{
	m_arrival = s;
}


Station* Passenger::getDeparture()
{
	return m_departure;
}
