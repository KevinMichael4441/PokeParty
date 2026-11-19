#pragma once

#include <string>
#include "ship.h"
#include "bullet.h"

enum class WeaponType { NORMAL, LASER };

class Player {
public:
    Player(std::string t_name, Ship t_ship, KeyboardKey t_fireKey);

    void update(float t_deltaTime);
    void draw();
    void respawn();
    void kill();

    Bullet fire(int t_ownerIndex);

    std::string getName();
    int getKills();
    void addKill();
    void resetKills();
    bool isAlive();
    KeyboardKey getFireKey();
    Ship& getShip();
    Collider& getCollider();

    void giveMelee();
    bool hasMelee() const;
    Vector2 getMeleeCenter() const;

    WeaponType getWeapon() const;
    void setWeapon(WeaponType t_weapon);

private:
    std::string m_name;
    int m_kills;
    bool m_alive;
    Ship m_ship;
    KeyboardKey m_fireKey;

    bool m_hasMelee = false;
    WeaponType m_weapon = WeaponType::NORMAL;
};