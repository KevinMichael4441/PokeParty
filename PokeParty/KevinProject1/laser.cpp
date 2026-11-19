#include "laser.h"

Laser::Laser(int t_ownerIndex, float t_duration)
    : m_ownerIndex(t_ownerIndex), m_timeRemaining(t_duration)
{
}

void Laser::update(float t_deltaTime)
{
    m_timeRemaining -= t_deltaTime;
}

bool Laser::isExpired() const
{
    return m_timeRemaining <= 0.0f;
}

int Laser::getOwnerIndex() const
{
    return m_ownerIndex;
}

float Laser::getRemainingTime() const
{
    return m_timeRemaining;
}