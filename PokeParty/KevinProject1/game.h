#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "constants.h"

typedef struct Game {
    Vector2 position;   // ball center
    Vector2 velocity;   // pixels per second
} Game;

void InitGame(Game* game);
void UpdateGame(Game* game, float deltaTime);
void DrawGame(Game* game);
void CleanupGame(Game* game);

#endif