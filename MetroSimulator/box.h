#pragma once
#include "gameobject.h"
#include "point.h"
#include "sgg/graphics.h"

class Box : public GameObject
{
	Point p;
	graphics::Brush m_brush_box;
	graphics::Brush m_brush_box_debug;
	float size;


public:

	void init() override;
	void draw() override;
	void update(float dt) override;

	Box(float pos_x, float pos_y, float size, std::string name);
	~Box();

	Point getPoint();
	float getSize();
	std::string getName();
};