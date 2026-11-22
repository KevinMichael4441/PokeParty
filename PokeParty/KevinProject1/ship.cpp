#include "ship.h"
#include "constants.h"

#include <cmath>

Ship::Ship(Vector2 t_startPos, float t_startRot, KeyboardKey t_turnKey, Color t_color)
    : m_startPos(t_startPos),
    m_startRot(t_startRot),
    m_position(t_startPos),
    m_rotation(t_startRot),
    m_rotationDirection(1.0f),
    m_speed(SHIP_SPEED),
    m_turnRate(SHIP_TURN_RATE),
    m_turnKey(t_turnKey),
    m_color(t_color),
    m_collider(t_startPos, SHIP_COLLIDER_RADIUS)
{
}

void Ship::update(float t_deltaTime)
{
    bool turnRightHeld = IsKeyDown(m_turnKey);

    if (turnRightHeld)
    {
        m_rotation += m_turnRate * m_rotationDirection * t_deltaTime;
        if (m_rotation >= 360.0f)
        {
            m_rotation -= 360.0f;
        }
        if (m_rotation < 0.0f)
        {
            m_rotation += 360.0f;
        }
    }

    m_position.x += cosf(m_rotation * DEG2RAD) * m_speed * t_deltaTime;
    m_position.y += sinf(m_rotation * DEG2RAD) * m_speed * t_deltaTime;

    float halfW = SHIP_WIDTH * 0.5f;
    float halfH = SHIP_HEIGHT * 0.5f;

    if (m_position.x < halfW)
    {
        m_position.x = halfW;
    }
    if (m_position.x > GetScreenWidth() - halfW)
    {
        m_position.x = GetScreenWidth() - halfW;
    }
    if (m_position.y < halfH)
    {
        m_position.y = halfH;
    }
    if (m_position.y > GetScreenHeight() - halfH)
    {
        m_position.y = GetScreenHeight() - halfH;
    }

    m_collider.setPosition(m_position);
}

void Ship::draw()
{
    Rectangle src = { 0.0f, 0.0f, (float)m_texture.width, (float)m_texture.height };

    Rectangle dst = {
        m_position.x,
        m_position.y,
        SHIP_DISPLAY_SIZE,
        SHIP_DISPLAY_SIZE
    };

    Vector2 origin = { SHIP_DISPLAY_SIZE * 0.5f, SHIP_DISPLAY_SIZE * 0.5f };

    DrawTexturePro(m_texture, src, dst, origin, m_rotation, WHITE);
}

void Ship::reset()
{
    m_position = m_startPos;
    m_rotation = m_startRot;
    m_collider.setPosition(m_position);
}

void Ship::reverseRotation()
{
    m_rotationDirection = -m_rotationDirection;
}

void Ship::setTexture(Texture2D t_texture)
{
    m_texture = t_texture;
}

Vector2 Ship::getPosition() const
{
    return m_position;
}

float Ship::getRotation() const
{
    return m_rotation;
}

Color Ship::getColor() const
{
    return m_color;
}

Rectangle Ship::getBody()
{
    return Rectangle{
        m_position.x - SHIP_WIDTH * 0.5f,
        m_position.y - SHIP_HEIGHT * 0.5f,
        SHIP_WIDTH,
        SHIP_HEIGHT
    };
}

Collider& Ship::getCollider()
{
    return m_collider;
}