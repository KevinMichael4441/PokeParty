#include "game.h"

void Game::run() {
    InitWindow(800, 600, "Simple Ship");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        update(deltaTime);

        BeginDrawing();
        ClearBackground(BLACK); // plain black screen
        draw();
        EndDrawing();
    }

    CloseWindow();
}

void Game::update(float t_deltaTime) {

    m_ship.update(t_deltaTime);
}

void Game::draw()
{
    m_ship.draw();
}