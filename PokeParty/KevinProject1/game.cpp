#include "game.h"



#define BALL_RADIUS 25.0f

void InitGame(Game* game) {
    game->position = Vector2{ 200.0f, 200.0f };
    game->velocity = Vector2{ 260.0f, 190.0f };
}

void UpdateGame(Game* game, float deltaTime) {
    game->position.x += game->velocity.x * deltaTime;
    game->position.y += game->velocity.y * deltaTime;

    float w = (float)GetScreenWidth();
    float h = (float)GetScreenHeight();

    if (game->position.x - BALL_RADIUS < 0.0f) {
        game->position.x = BALL_RADIUS;
        game->velocity.x = -game->velocity.x;
    }
    if (game->position.x + BALL_RADIUS > w) {
        game->position.x = w - BALL_RADIUS;
        game->velocity.x = -game->velocity.x;
    }
    if (game->position.y - BALL_RADIUS < 0.0f) {
        game->position.y = BALL_RADIUS;
        game->velocity.y = -game->velocity.y;
    }
    if (game->position.y + BALL_RADIUS > h) {
        game->position.y = h - BALL_RADIUS;
        game->velocity.y = -game->velocity.y;
    }
}

void DrawGame(Game* game) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    DrawCircleV(game->position, BALL_RADIUS, WHITE);
}

void CleanupGame(Game* game) { (void)game; }