#pragma once

#include <vector>
#include "player.h"
#include "bullet.h"
#include "laser.h"
#include "powerup.h"
#include "leaderboard.h"

enum class Screen { MENU, GAME, LEVEL_SELECT };


class Game {
public:
    Game();
    void run();

private:
    void update(float t_deltaTime);
    void draw();

    void updateGame(float t_deltaTime);
    void drawGame();

    void updateMenu(float t_deltaTime);
    void drawMenu();

    void updateLevelSelect(float t_deltaTime);
    void drawLevelSelect();

    void createPlayers(int t_count);

    void handleFiring();
    void handleBulletCollisions();
    void handleLaserCollisions();
    void handleMeleeCollisions();
    void updatePowerups(float t_deltaTime);
    void spawnPowerup();
    void applyPowerup(PowerupType t_type, int t_playerIndex);

    void cleanupBullets();
    void cleanupLasers();

    bool checkRoundEnd();
    void endRound();

    float getRandomSpawnDelay();

    void insertEndCircular(PowerupNode*& t_head, PowerupNode*& t_tail, Powerup t_powerup);

    std::vector<Player> m_players;
    std::vector<Bullet> m_bullets;
    std::vector<Laser> m_lasers;
    std::vector<Powerup> m_powerups;

    PowerupNode* m_currentPowerup = nullptr;
    PowerupNode* m_powerupHead = nullptr;
    PowerupNode* m_powerupTail = nullptr;

    float m_powerupSpawnTimer = 0.0f;

    Leaderboard m_leaderboard;

    int framesCounter = 0;
    Screen m_currentScreen{ Screen::MENU };

    Texture2D m_splashTexture{};
    bool      m_splashLoaded = false;
};