#include "bullet.h"
#include "constants.h"

#include <cmath>

Bullet::Bullet(Vector2 t_position, float t_direction, int t_ownerIndex, Color t_color)
    : m_position(t_position),
    m_direction(t_direction),
    m_speed(BULLET_SPEED),
    m_ownerIndex(t_ownerIndex),
    m_destroyed(false),
    m_color(t_color),
    m_collider(t_position, BULLET_RADIUS)
{
}

void Bullet::update(float t_deltaTime)
{
    m_position.x += cosf(m_direction * DEG2RAD) * m_speed * t_deltaTime;
    m_position.y += sinf(m_direction * DEG2RAD) * m_speed * t_deltaTime;
    m_collider.setPosition(m_position);
}

void Bullet::draw()
{
    DrawCircleV(m_position, BULLET_RADIUS, m_color);
}

bool Bullet::isOutOfBounds()
{
    return m_position.x < 0.0f
        || m_position.x > GetScreenWidth()
        || m_position.y < 0.0f
        || m_position.y > GetScreenHeight();
}

bool Bullet::isDestroyed()
{
    return m_destroyed;
}

void Bullet::destroy()
{
    m_destroyed = true;
}

Collider& Bullet::getCollider()
{
    return m_collider;
}

int Bullet::getOwnerIndex()
{
    return m_ownerIndex;
}