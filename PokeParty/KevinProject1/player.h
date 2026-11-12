#pragma once

#include <string>
#include "ship.h"
#include "bullet.h"

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

private:
    std::string m_name;
    int m_kills;
    bool m_alive;
    Ship m_ship;
    KeyboardKey m_fireKey;
};