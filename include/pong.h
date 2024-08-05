#ifndef PONG_H_
#define PONG_H_

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BALL_SPEED 5.0f

#include "raylib.h"
#include <stdio.h>

typedef struct {
    float x, y;
    float width, height;
    float speedY;
    char* score;
} Paddle;

typedef struct {
    float x, y;
    float radius;
    float speedX, speedY;
} Ball;

char score1[20];
char score2[20];
Sound PaddelSound;
Sound GameOver;

void InitGame(Paddle* player1, Paddle* player2, Ball* ball);
void UpdateGame(Paddle* player1, Paddle* player2, Ball* ball);
void BallReset(Ball* ball);
void DrawGame(Paddle* player1, Paddle* player2, Ball* ball);

#endif