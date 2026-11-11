#pragma once

#include "raylib.h"

class Collider {
public:
    Collider(Vector2 t_position = Vector2{ 0.0f, 0.0f }, float t_radius = 0.0f);

    void setPosition(Vector2 t_newPosition);

    Vector2 getPosition();
    float getRadius();

private:
    Vector2 m_position;
    float m_radius;
};