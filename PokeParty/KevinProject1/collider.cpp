#include "collider.h"

Collider::Collider(Vector2 t_position, float t_radius) : m_position(t_position), m_radius(t_radius)
{
}

void Collider::setPosition(Vector2 t_newPosition)
{
    m_position = t_newPosition;
}

Vector2 Collider::getPosition()
{
    return m_position;
}

float Collider::getRadius()
{
    return m_radius;
}

bool Collider::overlaps(Collider& t_other)
{
    float dx = m_position.x - t_other.getPosition().x;
    float dy = m_position.y - t_other.getPosition().y;
    float r = m_radius + t_other.getRadius();
    return dx * dx + dy * dy <= r * r;
}