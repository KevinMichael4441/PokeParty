#include "ship.h"
#include "constants.h"

#include <cmath>

static constexpr Vector2 SHIP_START_POS = { 400.0f, 300.0f };

Ship::Ship()
    : m_position(SHIP_START_POS),
    m_rotation(0.0f),
    m_speed(SHIP_SPEED),
    m_turnRate(SHIP_TURN_RATE),
    m_collider(SHIP_START_POS, SHIP_COLLIDER_RADIUS)
{
}

void Ship::update(float t_deltaTime)
{
    // Holding the button refreshes the grace timer; releasing lets it run out.

    bool turnRightHeld = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);

    if (turnRightHeld) {
        m_rotation += m_turnRate * t_deltaTime;
        if (m_rotation >= 360.0f) m_rotation -= 360.0f;
    }

    // Always moving forward at a constant speed.
    m_position.x += cosf(m_rotation * DEG2RAD) * m_speed * t_deltaTime;
    m_position.y += sinf(m_rotation * DEG2RAD) * m_speed * t_deltaTime;

    m_collider.setPosition(m_position);
}

void Ship::draw()
{

    Rectangle body = { m_position.x, m_position.y, SHIP_WIDTH, SHIP_HEIGHT };
    Vector2 origin = { SHIP_WIDTH * 0.5f, SHIP_HEIGHT * 0.5f };
    DrawRectanglePro(body, origin, m_rotation, WHITE);

    // Small nose marker so the heading is easy to read.
    Vector2 nose = {
        m_position.x + cosf(m_rotation * DEG2RAD) * SHIP_WIDTH * 0.5f,
        m_position.y + sinf(m_rotation * DEG2RAD) * SHIP_HEIGHT * 0.5f
    };
    DrawCircleV(nose, 3.0f, RED);

    // m_collider.drawDebug(); // uncomment to visualize the hit circle
}

Vector2 Ship::getPosition()
{
    return m_position;
}

float Ship::getRotation()
{
    return m_rotation;
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

const Collider& Ship::getCollider()
{
    return m_collider;
}