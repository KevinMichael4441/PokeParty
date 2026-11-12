#pragma once

#include <vector>
#include "player.h"
#include "bullet.h"
#include "leaderboard.h"

class Game {
public:
    Game();
    void run();

private:
    void update(float t_deltaTime);
    void draw();

    void handleFiring();
    void handleBulletCollisions();
    void cleanupBullets();
    bool checkRoundEnd();
    void endRound();

    std::vector<Player> m_players;
    std::vector<Bullet> m_bullets;
    Leaderboard m_leaderboard;
};