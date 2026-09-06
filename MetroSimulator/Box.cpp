#include "box.h"
#include "sgg/graphics.h"
#include "globalstate.h"
#include "util.h"
#include <iostream>

void Box::init()
{
	SETCOLOR(m_brush_box_debug.fill_color, 0.1f, 1.0f, 0.1f);
	SETCOLOR(m_brush_box_debug.outline_color, 0.2f, 1.0f, 0.2f);
	m_brush_box_debug.fill_opacity = 0.1f;

	m_brush_box.texture = m_state->getFullAssetPath(m_name);
	m_brush_box.fill_opacity = 0.5f;
	m_brush_box.outline_opacity = 0.0f;

}

void Box::draw()
{
	graphics::drawRect(p.x, p.y, size, size, m_brush_box);

	if (m_state->m_debugging)
		graphics::drawRect(p.x, p.y, size, size, m_brush_box_debug);

	// hoover in box rails
	float current_size = size;
	if (m_hoover)
	{
		current_size = size * 1.2f;
		m_brush_box.fill_opacity = 1.0f;
	}
	
	graphics::drawRect(p.x, p.y, current_size, current_size, m_brush_box);

	// starting of drawing a line
	graphics::MouseState ms = m_state->getGlobalMouseState();

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);

	
}

void Box::update(float dt)
{
	graphics::MouseState ms = m_state->getGlobalMouseState();

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);


	if (mx > p.x - size/2.0f && mx < p.x + size/2.0f && 
		my > p.y - size/2.0f && my < p.y + size/2.0f)
	{
		m_hoover = true;
	}
	else
	{
		m_hoover = false;
	}

	
}


Box::Box(float pos_x, float pos_y, float size, std::string name)
	: GameObject(name), size(size), p{pos_x, pos_y, name}
{

}

Box::~Box()
{
}

Point Box::getPoint()
{
	return p;
}

float Box::getSize()
{
	return size;
}

std::string Box::getName()
{
	return m_name;
}
