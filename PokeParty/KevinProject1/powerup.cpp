#include "powerup.h"
#include "constants.h"

#include <cmath>

Powerup::Powerup(Vector2 t_position, PowerupType t_type)
    : m_position(t_position),
    m_type(t_type),
    m_lifeRemaining(POWERUP_LIFETIME),
    m_collider(t_position, POWERUP_RADIUS)
{
}

void Powerup::update(float t_deltaTime)
{
    m_lifeRemaining -= t_deltaTime;
}

void Powerup::draw()
{
    DrawCircleV(m_position, POWERUP_RADIUS, getTypeColor());

    DrawCircleV(m_position, POWERUP_RADIUS, getTypeColor());
}

bool Powerup::isExpired() const
{
    return m_lifeRemaining <= 0.0f;
}

PowerupType Powerup::getType() const
{
    return m_type;
}

Collider& Powerup::getCollider()
{
    return m_collider;
}

Color Powerup::getTypeColor() const
{
    switch (m_type) 
    {
        case PowerupType::MELEE:   
            return ORANGE;
        case PowerupType::REVERSE: 
            return PURPLE;
        case PowerupType::LASER:   
            return RED;
    }
}

void Powerup::setPosition(Vector2 t_position)
{
    m_position = t_position;
    m_collider.setPosition(t_position);
}