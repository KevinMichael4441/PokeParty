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

    void reverseRotation();

    void setTexture(Texture2D t_texture);

    Vector2 getPosition() const;
    float   getRotation() const;
    Color   getColor()    const;

    Rectangle getBody();

    Collider& getCollider();

private:
    Vector2 m_startPos;
    float m_startRot;
    Vector2 m_position;
    float m_rotation;
    float m_rotationDirection = 1.0f;
    float m_speed;
    float m_turnRate;
    KeyboardKey m_turnKey;
    Color m_color;

    Texture2D m_texture{};

    Collider m_collider;
};