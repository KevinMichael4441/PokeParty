#include "player.h"
#include "constants.h"

#include <cmath>

Player::Player(std::string t_name, Ship t_ship, KeyboardKey t_fireKey)
    : m_name(t_name),
    m_kills(0),
    m_alive(true),
    m_ship(t_ship),
    m_fireKey(t_fireKey),
    m_hasMelee(false),
    m_weapon(WeaponType::NORMAL)
{
}

void Player::update(float t_deltaTime)
{
    if (m_alive)
    {
        m_ship.update(t_deltaTime);
    }
}

void Player::draw()
{
    if (!m_alive)
    {
        return;
    }

    if (m_hasMelee)
    {
        Vector2 center = getMeleeCenter();
        DrawCircleV(center, MELEE_RADIUS, Color{ 255, 161, 0, 127 });
        DrawCircleLinesV(center, MELEE_RADIUS, Color{ 255, 161, 0, 255 });
    }

    m_ship.draw();
}

void Player::respawn()
{
    m_alive = true;
    m_ship.reset();
    m_hasMelee = false;
    m_weapon = WeaponType::NORMAL;
}

void Player::kill()
{
    m_alive = false;
    m_hasMelee = false;
    m_weapon = WeaponType::NORMAL;
}

Bullet Player::fire(int t_ownerIndex)
{
    Vector2 pos = m_ship.getPosition();
    float rot = m_ship.getRotation();
    float spawnDist = SHIP_COLLIDER_RADIUS + BULLET_RADIUS + 1.0f;

    Vector2 bulletPos = {
        pos.x + cosf(rot * DEG2RAD) * spawnDist,
        pos.y + sinf(rot * DEG2RAD) * spawnDist
    };

    return Bullet(bulletPos, rot, t_ownerIndex, m_ship.getColor());
}

std::string Player::getName()
{
    return m_name;
}

int Player::getKills()
{
    return m_kills;
}

void Player::addKill()
{
    m_kills++;
}

void Player::resetKills()
{
    m_kills = 0;
}

bool Player::isAlive()
{
    return m_alive;
}

KeyboardKey Player::getFireKey()
{
    return m_fireKey;
}

Ship& Player::getShip()
{
    return m_ship;
}

Collider& Player::getCollider()
{
    return m_ship.getCollider();
}

void Player::giveMelee()
{
    m_hasMelee = true;
}

bool Player::hasMelee() const
{
    return m_hasMelee;
}

Vector2 Player::getMeleeCenter() const
{
    return m_ship.getPosition();
}

WeaponType Player::getWeapon() const
{
    return m_weapon;
}

void Player::setWeapon(WeaponType t_weapon)
{
    m_weapon = t_weapon;
}