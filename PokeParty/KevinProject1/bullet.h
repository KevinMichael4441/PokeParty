#pragma once

#include "raylib.h"
#include "collider.h"

class Bullet {
public:
    Bullet(Vector2 t_position, float t_direction, int t_ownerIndex);

    void update(float t_deltaTime);
    void draw();

    bool isOutOfBounds();
    bool isDestroyed();
    void destroy();

    Collider& getCollider();
    int getOwnerIndex();

private:
    Vector2 m_position;
    float m_direction;
    float m_speed;
    int m_ownerIndex;
    bool m_destroyed;

    Collider m_collider;
};