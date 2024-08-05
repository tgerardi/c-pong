#include "pong.h"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong Game!");

    Paddle player1;
    Paddle player2;
    Ball ball;

    InitAudioDevice();
    InitGame(&player1, &player2, &ball);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            UpdateGame(&player1, &player2, &ball);
            DrawGame(&player1, &player2, &ball);
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}

void InitGame(Paddle* player1, Paddle* player2, Ball* ball)
{
    /* Player 1 - Right Paddle */
    player1->x = 50;
    player1->y = SCREEN_HEIGHT / 2 - 50;
    player1->width = 20;
    player1->height = 100;
    player1->speedY = 5.0f;
    player1->score = 0;

    /* Player 2 - Left Paddle */
    player2->x = SCREEN_WIDTH - 70;
    player2->y = SCREEN_HEIGHT / 2 - 50;
    player2->width = 20;
    player2->height = 100;
    player2->speedY = 5.0f;
    player2->score = 0;

    /* Ball */
    ball->x = SCREEN_WIDTH / 2;
    ball->y = SCREEN_HEIGHT / 2;
    ball->radius = 10;
    ball->speedX = BALL_SPEED;
    ball->speedY = BALL_SPEED;

    /* Sounds */
    PaddelSound = LoadSound("sound/paddel-sound.wav");
    GameOver = LoadSound("sound/game-over-sound.mp3");
}

void UpdateGame(Paddle* player1, Paddle* player2, Ball* ball)
{
    /* Player 1 Movement */
    if (IsKeyDown(KEY_W) && player1->y > 0)
        player1->y -= player1->speedY;
    if (IsKeyDown(KEY_S) && player1->y < SCREEN_HEIGHT - player1->height)
        player1->y += player1->speedY;

    /* Player 2 Movement */
    if (IsKeyDown(KEY_UP) && player2->y > 0)
        player2->y -= player1->speedY;
    if (IsKeyDown(KEY_DOWN) && player1->y < SCREEN_HEIGHT - player2->height)
        player2->y += player1->speedY;

    /* Ball Movement */
    ball->x += ball->speedX;
    ball->y += ball->speedY;

    /* Ball Wall Collision */
    if (ball->y < 0 || ball->y > SCREEN_HEIGHT)
        ball->speedY *= -1;

    /* Ball Paddel Collision */
    if (
        CheckCollisionCircleRec((Vector2){ball->x, ball->y}, ball->radius, (Rectangle){player1->x, player1->y, player1->width, player1->height}) ||
        CheckCollisionCircleRec((Vector2){ball->x, ball->y}, ball->radius, (Rectangle){player2->x, player2->y, player2->width, player2->height})
    ) {
        ball->speedX *= -1;
        PlaySound(PaddelSound);
    }

    /* Ball Reset Position & Score Update */
    if (ball->x < 0) {
        ++player1->score;
        BallReset(ball);
        PlaySound(GameOver);
    } else if (ball->x > SCREEN_WIDTH) {
        ++player2->score;
        BallReset(ball);
        PlaySound(GameOver);
    }
}

void BallReset(Ball* ball)
{
    ball->x = SCREEN_WIDTH / 2;
    ball->y = SCREEN_HEIGHT / 2;
    ball->speedX = ((rand() % 2) * 2 - 1) * BALL_SPEED;
    ball->speedY = ((rand() % 2) * 2 - 1) * BALL_SPEED;
}

void DrawGame(Paddle* player1, Paddle* player2, Ball* ball)
{
    ClearBackground(BLACK);
    DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, WHITE);
    DrawRectangle(player1->x, player1->y, player1->width, player1->height, WHITE);
    DrawRectangle(player2->x, player2->y, player2->width, player2->height, WHITE);
    DrawCircle(ball->x, ball->y, ball->radius, RED);
    sprintf(score1, "%d", player1->score);
    sprintf(score2, "%d", player2->score);
    DrawText(score1, (SCREEN_WIDTH / 2) - 100, 10, 36, WHITE);
    DrawText(score2, (SCREEN_WIDTH / 2) + 100, 10, 36, WHITE);
}