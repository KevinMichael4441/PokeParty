#include "game.h"
#include "constants.h"

#include <iostream>
#include <algorithm>

Game::Game()
{
    m_players.push_back(Player("P1", Ship({ 100.0f, 300.0f }, 0.0f,   KEY_Q,    WHITE),  KEY_W));
    m_players.push_back(Player("P2", Ship({ 300.0f, 150.0f }, 90.0f,  KEY_N,    RED),    KEY_M));
    m_players.push_back(Player("P3", Ship({ 500.0f, 450.0f }, 180.0f, KEY_LEFT, GREEN),  KEY_RIGHT));
    m_players.push_back(Player("P4", Ship({ 700.0f, 300.0f }, 270.0f, KEY_KP_8, YELLOW), KEY_KP_9));
}

void Game::run() {
    InitWindow(800, 600, "Simple Ship");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        update(deltaTime);

        BeginDrawing();
        ClearBackground(BLACK);
        draw();
        EndDrawing();
    }

    CloseWindow();
}

void Game::update(float t_deltaTime) {
    for (Player& player : m_players)
    {
        player.update(t_deltaTime);
    }

    handleFiring();

    for (Bullet& bullet : m_bullets)
    {
        bullet.update(t_deltaTime);
    }

    handleBulletCollisions();
    cleanupBullets();

    if (checkRoundEnd()) {
        endRound();
    }
}

void Game::draw()
{
    for (Player& player : m_players)
    {
        player.draw();
    }

    for (Bullet& bullet : m_bullets)
    {
        bullet.draw();
    }
}

void Game::handleFiring()
{
    for (int i = 0; i < (int)m_players.size(); i++)
    {
        if (!m_players[i].isAlive()) continue;
        if (IsKeyPressed(m_players[i].getFireKey())) {
            m_bullets.push_back(m_players[i].fire(i));
        }
    }
}

void Game::handleBulletCollisions()
{
    for (int i = 0; i < (int)m_bullets.size(); i++)
    {
        if (m_bullets[i].isDestroyed()) continue;

        for (int j = 0; j < (int)m_players.size(); j++)
        {
            if (!m_players[j].isAlive()) continue;
            if (m_bullets[i].getOwnerIndex() == j) continue;

            if (m_bullets[i].getCollider().overlaps(m_players[j].getCollider())) {
                m_players[m_bullets[i].getOwnerIndex()].addKill();
                m_players[j].kill();
                m_leaderboard.addPlayer(m_players[j].getName(), m_players[j].getKills());
                m_bullets[i].destroy();
                break;
            }
        }
    }
}

void Game::cleanupBullets()
{
    m_bullets.erase(
        std::remove_if(m_bullets.begin(), m_bullets.end(),
            [](Bullet& bullet) { return bullet.isDestroyed() || bullet.isOutOfBounds(); }),
        m_bullets.end());
}

bool Game::checkRoundEnd()
{
    int aliveCount = 0;
    for (Player& player : m_players)
    {
        if (player.isAlive()) aliveCount++;
    }
    return aliveCount <= 1;
}

void Game::endRound()
{
    for (Player& player : m_players)
    {
        if (player.isAlive()) {
            m_leaderboard.addPlayer(player.getName(), player.getKills());
        }
    }

    std::cout << "=== Round Results ===\n";
    m_leaderboard.displayLeaderboard();
    std::cout << "=====================\n";

    bool fullReset = false;
    for (Player& player : m_players)
    {
        if (player.getKills() >= KILLS_FOR_RESET) fullReset = true;
    }

    if (fullReset) {
        for (Player& player : m_players)
        {
            player.resetKills();
        }
    }

    for (Player& player : m_players)
    {
        player.respawn();
    }
    m_bullets.clear();
}