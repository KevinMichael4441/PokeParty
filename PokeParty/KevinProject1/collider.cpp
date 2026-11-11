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