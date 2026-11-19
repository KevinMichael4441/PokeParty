#pragma once

class Laser {
public:
    Laser(int t_ownerIndex, float t_duration);

    void update(float t_deltaTime);

    bool isExpired() const;
    int getOwnerIndex() const;
    float getRemainingTime() const;

private:
    int m_ownerIndex;
    float m_timeRemaining;
};