#pragma once

#include "raylib.h"
#include "collider.h"

class Ship {
public:
    Ship(Vector2 t_startPos = { 400.0f, 300.0f },
        float t_startRot = 0.0f,
        KeyboardKey t_turnKey = KEY_RIGHT,
        Color t_color = WHITE);

    void update(float t_deltaTime);
    void draw();
    void reset();

    Vector2 getPosition();
    float getRotation();
    Color getColor();

    // Unrotated, axis-aligned rectangle centered on the ship position.
    Rectangle getBody();

    Collider& getCollider();

private:
    Vector2 m_startPos;
    float m_startRot;
    Vector2 m_position;
    float m_rotation;         // degrees
    float m_speed;
    float m_turnRate;         // degrees/s
    KeyboardKey m_turnKey;
    Color m_color;

    Collider m_collider;
};