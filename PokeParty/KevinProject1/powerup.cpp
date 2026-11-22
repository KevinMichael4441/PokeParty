#include "powerup.h"
#include "constants.h"

Powerup::Powerup(Vector2 t_position, PowerupType t_type, Texture2D t_texture)
    : m_position(t_position),
    m_type(t_type),
    m_lifeRemaining(POWERUP_LIFETIME),
    m_collider(t_position, POWERUP_RADIUS),
    m_texture(t_texture)
{
}

void Powerup::update(float t_deltaTime)
{
    m_lifeRemaining -= t_deltaTime;
}

void Powerup::draw()
{
    Rectangle src = { 0.0f, 0.0f, (float)m_texture.width, (float)m_texture.height };
    Rectangle dst = { m_position.x, m_position.y, POWERUP_DISPLAY_SIZE, POWERUP_DISPLAY_SIZE };
    Vector2 origin = { POWERUP_DISPLAY_SIZE * 0.5f, POWERUP_DISPLAY_SIZE * 0.5f };

    DrawTexturePro(m_texture, src, dst, origin, 0.0f, WHITE);
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

void Powerup::setPosition(Vector2 t_position)
{
    m_position = t_position;
    m_collider.setPosition(t_position);
}