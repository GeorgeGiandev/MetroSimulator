#include "rail.h"
#include "util.h"
#include <string>
#include <iostream>

void Rail::init()
{
}

void Rail::draw()
{   
    m_brush_rail.texture = "";
    if (m_color == "red.png") {
        SETCOLOR(m_brush_rail.outline_color, 1.0f, 0.1f, 0.1f);
    } else {
        SETCOLOR(m_brush_rail.outline_color, 0.1f, 0.1f, 1.0f);
    }

    m_brush_rail.outline_opacity = 1.0f;

    float cx = (m_from->getPosX() + m_to->getPosX()) / 2.0f;
    float cy = (m_from->getPosY() + m_to->getPosY()) / 2.0f;
    graphics::drawDisk(cx, cy, 0.0001f, m_brush_rail);

    graphics::drawLine(m_from->getPosX(), m_from->getPosY(),  m_to->getPosX(), m_to->getPosY(), m_brush_rail);
}

void Rail::update(float dt)
{
}

Station* Rail::getFrom()
{
    return m_from;
}

Station* Rail::getTo()
{
    return m_to;
}


Rail::Rail(Station* s1, Station* s2, std::string color)
	: GameObject("Rail"), m_from(s1), m_to(s2), m_color(color)
{
}

Rail::~Rail()
{

}
