#pragma once

#include "raylib.h"
#include "collider.h"

class Ship {
public:
    Ship();

    // turnRightHeld: true while the turn button is down.
    void update(float t_deltaTime);
    void draw();

    Vector2 getPosition();
    float getRotation();

    // Unrotated, axis-aligned rectangle centered on the ship position.
    Rectangle getBody();

    const Collider& getCollider();

private:
    Vector2 m_position;
    float m_rotation;         // degrees
    float m_speed;
    float m_turnRate;         // degrees/s

    Collider m_collider;
};