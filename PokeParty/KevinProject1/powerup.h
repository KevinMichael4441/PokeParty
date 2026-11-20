#pragma once

#include "raylib.h"
#include "collider.h"

enum class PowerupType { MELEE, REVERSE, LASER };

class Powerup {
public:
    Powerup(Vector2 t_position, PowerupType t_type);

    void update(float t_deltaTime);
    void draw();

    bool isExpired() const;
    PowerupType getType() const;
    Collider& getCollider();

    void setPosition(Vector2 t_position);

private:
    Vector2 m_position;
    PowerupType m_type;
    float m_lifeRemaining;
    Collider m_collider;

    Color getTypeColor() const;
    const char* getTypeLabel() const;
};


class PowerupNode
{
public:
    PowerupNode(Powerup t_player) : m_data(t_player), m_next(nullptr) {};
    Powerup m_data;
    PowerupNode* m_next;
};

static PowerupNode* createNode(Powerup player)
{
    PowerupNode* newNode = new PowerupNode(player);
    newNode->m_next = nullptr;
    return newNode;
}