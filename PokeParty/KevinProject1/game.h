#pragma once

#include "ship.h"

class Game {
public:
    void run();

private:
    void update(float t_deltaTime);
    void draw();

    Ship m_ship;
};