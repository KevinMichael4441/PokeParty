#include "game.h"
#include "constants.h"

#include <iostream>
#include <algorithm>
#include <cmath>

static float pointSegmentDistance(Vector2 p, Vector2 a, Vector2 b)
{
    Vector2 ab = { b.x - a.x, b.y - a.y };
    Vector2 ap = { p.x - a.x, p.y - a.y };
    float abLenSq = ab.x * ab.x + ab.y * ab.y;
    if (abLenSq < 1e-6f)
    {
        float dx = p.x - a.x, dy = p.y - a.y;
        return sqrtf(dx * dx + dy * dy);
    }
    float t = (ap.x * ab.x + ap.y * ab.y) / abLenSq;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    float cx = a.x + ab.x * t;
    float cy = a.y + ab.y * t;
    float dx = p.x - cx;
    float dy = p.y - cy;
    return sqrtf(dx * dx + dy * dy);
}

Game::Game()
{
    m_powerupSpawnTimer = getRandomSpawnDelay();

    HideCursor();
}

void Game::run()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PokeParty");
    SetTargetFPS(60);

    m_splashTexture = LoadTexture("assets/splash.png");
    m_splashLoaded = (m_splashTexture.id > 0);

    insertEndCircular(m_powerupHead, m_powerupTail, Powerup({ 0,0 }, PowerupType::LASER));
    insertEndCircular(m_powerupHead, m_powerupTail, Powerup({ 0,0 }, PowerupType::MELEE));
    insertEndCircular(m_powerupHead, m_powerupTail, Powerup({ 0,0 }, PowerupType::REVERSE));
    m_currentPowerup = m_powerupHead;

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        update(deltaTime);

        BeginDrawing();
        ClearBackground(BLUE);
        draw();
        EndDrawing();
    }

    if (m_splashLoaded)
    {
        UnloadTexture(m_splashTexture);
    }

    CloseWindow();
}


void Game::update(float t_deltaTime)
{
    switch (m_currentScreen)
    {
    case Screen::MENU:
    {
        updateMenu(t_deltaTime);
    } break;

    case Screen::LEVEL_SELECT:
    {
        updateLevelSelect(t_deltaTime);
    } break;

    case Screen::GAME:
    {
        updateGame(t_deltaTime);
    } break;

    default:
    {
    } break;
    }
}

void Game::draw()
{
    switch (m_currentScreen)
    {
    case Screen::MENU:
    {
        drawMenu();
    } break;

    case Screen::LEVEL_SELECT:
    {
        drawLevelSelect();
    } break;

    case Screen::GAME:
    {
        drawGame();
    } break;

    default:
    {
    } break;
    }
}

void Game::updateGame(float t_deltaTime)
{
    for (Player& player : m_players)
    {
        player.update(t_deltaTime);
    }

    handleFiring();

    for (Bullet& bullet : m_bullets)
    {
        bullet.update(t_deltaTime);
    }

    for (Laser& laser : m_lasers)
    {
        laser.update(t_deltaTime);
    }

    updatePowerups(t_deltaTime);

    handleBulletCollisions();
    handleLaserCollisions();
    handleMeleeCollisions();

    cleanupBullets();
    cleanupLasers();

    if (checkRoundEnd())
    {
        endRound();
    }
}

void Game::updateMenu(float t_deltaTime)
{
    framesCounter++;

    if (framesCounter > 120)
    {
        framesCounter = 0;
        m_currentScreen = Screen::LEVEL_SELECT;
    }
}

void Game::drawMenu()
{
    ClearBackground(BLACK);

    if (m_splashLoaded)
    {
        float scaleX = SCREEN_WIDTH / (float)m_splashTexture.width;
        float scaleY = SCREEN_HEIGHT / (float)m_splashTexture.height;
        float scale = fminf(scaleX, scaleY);

        float w = m_splashTexture.width * scale;
        float h = m_splashTexture.height * scale;

        Rectangle src = { 0.0f, 0.0f, (float)m_splashTexture.width, (float)m_splashTexture.height };
        Rectangle dst = { (SCREEN_WIDTH - w) * 0.5f, (SCREEN_HEIGHT - h) * 0.5f, w, h };

        DrawTexturePro(m_splashTexture, src, dst, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
    }
    else
    {
        DrawText("SPLASH", 20, 20, 40, LIGHTGRAY);
    }

    DrawText("Loading...", 20, (int)SCREEN_HEIGHT - 40, 20, LIGHTGRAY);
}

void Game::updateLevelSelect(float t_deltaTime)
{
    const float boxSize = 220.0f;
    const float boxSpacing = 40.0f;
    const float totalW = 3.0f * boxSize + 2.0f * boxSpacing;
    const float startX = (SCREEN_WIDTH - totalW) * 0.5f;
    const float boxY = (SCREEN_HEIGHT - boxSize) * 0.5f;

    Vector2 mouse = GetMousePosition();
    bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    for (int i = 0; i < 3; i++)
    {
        float x = startX + i * (boxSize + boxSpacing);
        Rectangle box = { x, boxY, boxSize, boxSize };

        if (CheckCollisionPointRec(mouse, box) && clicked)
        {
            createPlayers(i + 2);
            m_currentScreen = Screen::GAME;
            return;
        }
    }
}

void Game::drawLevelSelect()
{
    ClearBackground(DARKGREEN);

    const int counts[3] = { 2, 3, 4 };
    const float boxSize = 220.0f;
    const float boxSpacing = 40.0f;
    const float totalW = 3.0f * boxSize + 2.0f * boxSpacing;
    const float startX = (SCREEN_WIDTH - totalW) * 0.5f;
    const float boxY = (SCREEN_HEIGHT - boxSize) * 0.5f;

    const float circleRadius = 17.0f;
    const float circleSpacing = 8.0f;

    Vector2 mouse = GetMousePosition();

    for (int i = 0; i < 3; i++)
    {
        float x = startX + i * (boxSize + boxSpacing);
        Rectangle box = { x, boxY, boxSize, boxSize };

        bool hovered = CheckCollisionPointRec(mouse, box);

        Color boxFill = hovered ? RAYWHITE : Color{ 0, 80, 0, 255 };
        Color circleColor = hovered ? DARKGREEN : RAYWHITE;

        DrawRectangleRec(box, boxFill);
        DrawRectangleLinesEx(box, 4.0f, RAYWHITE);

        int count = counts[i];
        float rowW = count * circleRadius * 2.0f + (count - 1) * circleSpacing;
        float rowStartX = x + (boxSize - rowW) * 0.5f;
        float rowCenterY = boxY + boxSize * 0.5f;

        for (int c = 0; c < count; c++)
        {
            float cx = rowStartX + circleRadius + c * (circleRadius * 2.0f + circleSpacing);
            DrawCircleV(Vector2{ cx, rowCenterY }, circleRadius, circleColor);
        }
    }
}

void Game::createPlayers(int t_count)
{
    m_players.clear();

    m_players.push_back(Player("P1", Ship({ 100.0f, 300.0f }, 0.0f, KEY_Q, WHITE), KEY_W));
    m_players.push_back(Player("P2", Ship({ 300.0f, 150.0f }, 90.0f, KEY_N, RED), KEY_M));

    if (t_count >= 3)
    {
        m_players.push_back(Player("P3", Ship({ 500.0f, 450.0f }, 180.0f, KEY_LEFT, GREEN), KEY_RIGHT));
    }

    if (t_count >= 4)
    {
        m_players.push_back(Player("P4", Ship({ 700.0f, 300.0f }, 270.0f, KEY_KP_8, YELLOW), KEY_KP_9));
    }

    m_bullets.clear();
    m_lasers.clear();
    m_powerups.clear();
    m_powerupSpawnTimer = getRandomSpawnDelay();
}

void Game::drawGame()
{
    for (Powerup& p : m_powerups)
    {
        p.draw();
    }

    for (Player& player : m_players)
    {
        player.draw();
    }

    for (Bullet& bullet : m_bullets)
    {
        bullet.draw();
    }

    for (const Laser& laser : m_lasers)
    {
        int idx = laser.getOwnerIndex();
        if (idx < 0 || idx >= (int)m_players.size())
        {
            continue;
        }
        if (!m_players[idx].isAlive())
        {
            continue;
        }

        Vector2 pos = m_players[idx].getShip().getPosition();
        float rot = m_players[idx].getShip().getRotation();
        Vector2 end = {
            pos.x + cosf(rot * DEG2RAD) * LASER_MAX_LENGTH,
            pos.y + sinf(rot * DEG2RAD) * LASER_MAX_LENGTH
        };

        DrawLineEx(pos, end, LASER_WIDTH * 2.5f, RED);
        DrawLineEx(pos, end, LASER_WIDTH, BLUE);
    }
}

void Game::handleFiring()
{
    for (int i = 0; i < (int)m_players.size(); i++)
    {
        if (!m_players[i].isAlive())
        {
            continue;
        }
        if (!IsKeyPressed(m_players[i].getFireKey()))
        {
            continue;
        }

        if (m_players[i].getWeapon() == WeaponType::LASER)
        {
            m_lasers.push_back(Laser(i, LASER_DURATION));
            m_players[i].setWeapon(WeaponType::NORMAL);
        }
        else
        {
            m_bullets.push_back(m_players[i].fire(i));
        }
    }
}

void Game::handleBulletCollisions()
{
    for (int i = 0; i < (int)m_bullets.size(); i++)
    {
        if (m_bullets[i].isDestroyed())
        {
            continue;
        }

        for (int j = 0; j < (int)m_players.size(); j++)
        {
            if (!m_players[j].isAlive())
            {
                continue;
            }
            if (m_bullets[i].getOwnerIndex() == j)
            {
                continue;
            }

            if (m_bullets[i].getCollider().overlaps(m_players[j].getCollider()))
            {
                m_players[m_bullets[i].getOwnerIndex()].addKill();
                m_players[j].kill();
                m_leaderboard.addPlayer(m_players[j].getName(), m_players[j].getKills());
                m_bullets[i].destroy();
                break;
            }
        }
    }
}

void Game::handleLaserCollisions()
{
    for (const Laser& laser : m_lasers)
    {
        int ownerIdx = laser.getOwnerIndex();
        if (ownerIdx < 0 || ownerIdx >= (int)m_players.size())
        {
            continue;
        }
        if (!m_players[ownerIdx].isAlive())
        {
            continue;
        }

        Vector2 origin = m_players[ownerIdx].getShip().getPosition();
        float rot = m_players[ownerIdx].getShip().getRotation();
        Vector2 end = {
            origin.x + cosf(rot * DEG2RAD) * LASER_MAX_LENGTH,
            origin.y + sinf(rot * DEG2RAD) * LASER_MAX_LENGTH
        };

        for (int j = 0; j < (int)m_players.size(); j++)
        {
            if (j == ownerIdx)
            {
                continue;
            }
            if (!m_players[j].isAlive())
            {
                continue;
            }

            Vector2 center = m_players[j].getShip().getPosition();
            float   radius = m_players[j].getCollider().getRadius();

            if (pointSegmentDistance(center, origin, end) <= radius + LASER_WIDTH * 0.5f)
            {
                m_players[ownerIdx].addKill();
                m_players[j].kill();
                m_leaderboard.addPlayer(m_players[j].getName(), m_players[j].getKills());
            }
        }
    }
}

void Game::handleMeleeCollisions()
{
    for (int i = 0; i < (int)m_players.size(); i++)
    {
        if (!m_players[i].isAlive())
        {
            continue;
        }
        if (!m_players[i].hasMelee())
        {
            continue;
        }

        Vector2 meleeCenter = m_players[i].getMeleeCenter();

        for (int j = 0; j < (int)m_players.size(); j++)
        {
            if (i == j)
            {
                continue;
            }
            if (!m_players[j].isAlive())
            {
                continue;
            }

            Vector2 other = m_players[j].getShip().getPosition();
            float dx = meleeCenter.x - other.x;
            float dy = meleeCenter.y - other.y;
            float r = MELEE_RADIUS + m_players[j].getCollider().getRadius();

            if (dx * dx + dy * dy <= r * r)
            {
                m_players[i].addKill();
                m_players[j].kill();
                m_leaderboard.addPlayer(m_players[j].getName(), m_players[j].getKills());
            }
        }
    }
}

void Game::updatePowerups(float t_deltaTime)
{
    for (Powerup& p : m_powerups)
    {
        p.update(t_deltaTime);
    }

    for (int i = 0; i < (int)m_powerups.size(); i++)
    {
        for (int j = 0; j < (int)m_players.size(); j++)
        {
            if (!m_players[j].isAlive())
            {
                continue;
            }
            if (m_powerups[i].getCollider().overlaps(m_players[j].getCollider()))
            {
                applyPowerup(m_powerups[i].getType(), j);
                m_powerups.erase(m_powerups.begin() + i);
                break;
            }
        }
    }

    m_powerups.erase(
        std::remove_if(m_powerups.begin(), m_powerups.end(),
            [](Powerup& p) { return p.isExpired(); }),
        m_powerups.end());

    m_powerupSpawnTimer -= t_deltaTime;
    if (m_powerupSpawnTimer <= 0.0f && (int)m_powerups.size() < MAX_POWERUPS)
    {
        spawnPowerup();
        m_powerupSpawnTimer = getRandomSpawnDelay();
    }
}

void Game::spawnPowerup()
{
    Powerup powerUpToSpawn = m_currentPowerup->m_data;
    m_currentPowerup = m_currentPowerup->m_next;

    Vector2 pos = { 0.0f, 0.0f };
    const int margin = (int)POWERUP_RADIUS + 20;

    pos.x = (float)GetRandomValue(margin, GetScreenWidth() - margin);
    pos.y = (float)GetRandomValue(margin, GetScreenHeight() - margin);

    powerUpToSpawn.setPosition(pos);

    m_powerups.push_back(powerUpToSpawn);
}

void Game::applyPowerup(PowerupType t_type, int t_playerIndex)
{
    switch (t_type)
    {
    case PowerupType::MELEE:
    {
        m_players[t_playerIndex].giveMelee();
    } break;

    case PowerupType::REVERSE:
    {
        for (Player& p : m_players)
        {
            p.getShip().reverseRotation();
        }
    } break;

    case PowerupType::LASER:
    {
        m_players[t_playerIndex].setWeapon(WeaponType::LASER);
    } break;
    }
}

void Game::cleanupBullets()
{
    m_bullets.erase(
        std::remove_if(m_bullets.begin(), m_bullets.end(),
            [](Bullet& bullet) { return bullet.isDestroyed() || bullet.isOutOfBounds(); }),
        m_bullets.end());
}

void Game::cleanupLasers()
{
    m_lasers.erase(
        std::remove_if(m_lasers.begin(), m_lasers.end(),
            [this](const Laser& l) {
                if (l.isExpired())
                {
                    return true;
                }
                int idx = l.getOwnerIndex();
                if (idx < 0 || idx >= (int)m_players.size())
                {
                    return true;
                }
                return !m_players[idx].isAlive();
            }),
        m_lasers.end());
}

float Game::getRandomSpawnDelay()
{
    int lo = (int)(POWERUP_MIN_SPAWN_TIME * 100.0f);
    int hi = (int)(POWERUP_MAX_SPAWN_TIME * 100.0f);
    return (float)GetRandomValue(lo, hi) / 100.0f;
}

bool Game::checkRoundEnd()
{
    int aliveCount = 0;
    for (Player& player : m_players)
    {
        if (player.isAlive())
        {
            aliveCount++;
        }
    }
    return aliveCount <= 1;
}

void Game::endRound()
{
    for (Player& player : m_players)
    {
        if (player.isAlive())
        {
            m_leaderboard.addPlayer(player.getName(), player.getKills());
        }
    }

    std::cout << "=== Round Results ===\n";
    m_leaderboard.displayLeaderboard();
    std::cout << "=====================\n";

    bool fullReset = false;
    for (Player& player : m_players)
    {
        if (player.getKills() >= KILLS_FOR_RESET)
        {
            fullReset = true;
        }
    }

    if (fullReset)
    {
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
    m_lasers.clear();
    m_powerups.clear();
    m_powerupSpawnTimer = getRandomSpawnDelay();
}

void Game::insertEndCircular(PowerupNode*& t_head, PowerupNode*& t_tail, Powerup t_powerup)
{
    PowerupNode* newNode = createNode(t_powerup);
    if (!m_powerupHead)
    {
        m_powerupHead = newNode;
        m_powerupTail = newNode;
    }
    else
    {
        newNode->m_next = m_powerupHead;
        m_powerupTail->m_next = newNode;
        m_powerupTail = newNode;
    }
}