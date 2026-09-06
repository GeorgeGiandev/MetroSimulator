#pragma once
#include "gameobject.h"
#include "station.h"
#include "sgg/graphics.h"

class Station; // to avoid circular include from compiler

class Passenger : public GameObject
{
	Station* m_arrival;
	Station* m_departure;

	std::vector<Station*> m_path;
	int m_path_index = 0;

	graphics::Brush m_brush_passenger;
	graphics::Brush m_brush_passenger_text;


public:

	Passenger(Station* start, Station* end);
	void init() override;
	void draw() override;
	void update(float dt) override;

	void setPath(std::vector<Station*> newPath);
	Station* getNextTarget();
	void advancePath();
	bool hasReachedDestination();
	void setArrival(Station* s);

	// offset is coming from station
	float offset_x; 
	float offset_y;

	Station* getDeparture();
};