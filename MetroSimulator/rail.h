#pragma once
#include "gameobject.h"
#include "station.h"
#include <sgg/graphics.h>
#include <string>


class Rail : public GameObject
{
	Station* m_from;
	Station* m_to;
	std::string m_color; 

	graphics::Brush m_brush_rail;


public:
	void init() override;
	void draw() override;
	void update(float dt) override;

	Station* getFrom();
	Station* getTo();

	Rail(Station* s1, Station* s2, std::string color);
	~Rail();

};