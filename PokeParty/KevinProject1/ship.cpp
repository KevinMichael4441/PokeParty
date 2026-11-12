#include "ship.h"
#include "constants.h"

#include <cmath>

Ship::Ship(Vector2 t_startPos, float t_startRot, KeyboardKey t_turnKey, Color t_color)
    : m_startPos(t_startPos),
    m_startRot(t_startRot),
    m_position(t_startPos),
    m_rotation(t_startRot),
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

    if (turnRightHeld) {
        m_rotation += m_turnRate * t_deltaTime;
        if (m_rotation >= 360.0f) m_rotation -= 360.0f;
    }

    m_position.x += cosf(m_rotation * DEG2RAD) * m_speed * t_deltaTime;
    m_position.y += sinf(m_rotation * DEG2RAD) * m_speed * t_deltaTime;

    float halfW = SHIP_WIDTH * 0.5f;
    float halfH = SHIP_HEIGHT * 0.5f;

    if (m_position.x < halfW) m_position.x = halfW;
    if (m_position.x > GetScreenWidth() - halfW) m_position.x = GetScreenWidth() - halfW;
    if (m_position.y < halfH) m_position.y = halfH;
    if (m_position.y > GetScreenHeight() - halfH) m_position.y = GetScreenHeight() - halfH;

    m_collider.setPosition(m_position);
}

void Ship::draw()
{
    Rectangle body = { m_position.x, m_position.y, SHIP_WIDTH, SHIP_HEIGHT };
    Vector2 origin = { SHIP_WIDTH * 0.5f, SHIP_HEIGHT * 0.5f };
    DrawRectanglePro(body, origin, m_rotation, m_color);
}

void Ship::reset()
{
    m_position = m_startPos;
    m_rotation = m_startRot;
    m_collider.setPosition(m_position);
}

Vector2 Ship::getPosition()
{
    return m_position;
}

float Ship::getRotation()
{
    return m_rotation;
}

Color Ship::getColor()
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