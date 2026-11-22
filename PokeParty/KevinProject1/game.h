#pragma once

#include <vector>
#include "player.h"
#include "bullet.h"
#include "laser.h"
#include "powerup.h"
#include "leaderboard.h"

enum class Screen { MENU, GAME, LEVEL_SELECT, LEADERBOARD };


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

    void updateLeaderboard(float t_deltaTime);
    void drawLeaderboard();

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

    float m_splashTimer = 0.0f;
    Screen m_currentScreen{ Screen::MENU };

    Texture2D m_splashTexture{};
    Texture2D m_bgTexture{};
    Texture2D m_playerTextures[4]{};
    Texture2D m_playerFrontTextures[4]{};

    float m_leaderboardTimer = 0.0f;
    bool m_matchOver = false;
};