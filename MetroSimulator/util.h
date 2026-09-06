#pragma once
#include <string>
#include "sgg/graphics.h"
#include <vector>
#include <cmath>

#define SETCOLOR(c, r, g, b) {c[0] = r; c[1] = g; c[2] = b;}
#define WINDOW_WIDTH float(1400)
#define WINDOW_HEIGHT float(600)

inline float getDistance(float x1, float y1, float x2, float y2) {
    return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}

inline bool checkCollision(float cx1, float cy1, float w1, float h1,
                            float cx2, float cy2, float w2, float h2) 
{
    bool collisionX = std::abs(cx1 - cx2) < (w1 + w2) / 2.0f;

    bool collisionY = std::abs(cy1 - cy2) < (h1 + h2) / 2.0f;

    return collisionX && collisionY;
}