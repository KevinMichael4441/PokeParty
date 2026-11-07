#ifndef GAME_H
#define GAME_H

#include "raylib.h"

typedef struct Game {
    Vector2 position;
    Vector2 velocity;
} Game;

void InitGame(Game* game);
void UpdateGame(Game* game, float deltaTime);
void DrawGame(Game* game);
void CleanupGame(Game* game);

#endif