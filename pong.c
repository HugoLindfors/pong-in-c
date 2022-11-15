#include "raylib.h"

// cc pong.c `pkg-config --libs --cflags raylib` -o pong

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screen_width = 800;
    const int screen_height = 450;

    int fail = 0;
    int player_1_score = 0;
    int player_2_score = 0;

    InitWindow(screen_width, screen_height, "raylib [core] example - keyboard input");

    // ball
    Vector2 ball_position = {(float)screen_width / 2, (float)screen_height / 2};
    Vector2 ball_velocity = {5.0f, 5.0f};

    // paddle_1
    Vector2 paddle_1_position = {80, (float)screen_height / 2};
    Vector2 paddle_1_velocity = {0.0f, 5.0f};

    // paddle_2
    Vector2 paddle_2_position = {720, (float)screen_height / 2};
    Vector2 paddle_2_velocity = {0.0f, 5.0f};

    // ball
    Rectangle ball = {
        .x = ball_position.x,
        .y = ball_position.y,
        .height = 20,
        .width = 20,
    };

    // paddle_1
    Rectangle paddle_1 = {
        .x = paddle_1_position.x,
        .y = paddle_1_position.y,
        .height = 200,
        .width = 20};

    // paddle_2
    Rectangle paddle_2 = {
        .x = paddle_2_position.x,
        .y = paddle_2_position.y,
        .height = 200,
        .width = 20};

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        ball_position.x += ball_velocity.x;
        ball_position.y += ball_velocity.y;

        if (IsKeyDown(KEY_S))
            paddle_1.y += paddle_1_velocity.y;
        if (IsKeyDown(KEY_DOWN))
            paddle_2.y += paddle_2_velocity.y;

        if (IsKeyDown(KEY_W))
            paddle_1.y -= paddle_1_velocity.y;
        if (IsKeyDown(KEY_UP))
            paddle_2.y -= paddle_2_velocity.y;

        Rectangle ball = {
            .x = ball_position.x,
            .y = ball_position.y,
            .width = 20,
            .height = 20};

        if (CheckCollisionRecs(ball, paddle_1))
        {
            ball_velocity.x = -ball_velocity.x;
        }

        if (CheckCollisionRecs(ball, paddle_2))
        {
            ball_velocity.x = -ball_velocity.x;
        }

        if (ball_position.x >= (GetScreenWidth() - 20))
        {
            ball_velocity.x = -ball_velocity.x;
            fail = 1;
            player_1_score ++;
        }

        if (ball_position.y >= (GetScreenHeight() - 20))
        {
            ball_velocity.y = -ball_velocity.y;
        }

        if (ball_position.x <= (0))
        {
            ball_velocity.x = -ball_velocity.x;
            player_2_score ++;
            fail = 1;
        }

        if (ball_position.y <= (0))
        {
            ball_velocity.y = -ball_velocity.y;
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        DrawRectangle(ball.x, ball.y, ball.width, ball.height, WHITE);
        DrawRectangle(paddle_1.x, paddle_1.y, paddle_1.width, paddle_1.height, WHITE);
        DrawRectangle(paddle_2.x, paddle_2.y, paddle_2.width, paddle_2.height, WHITE);

        if (fail == 1)
        {
            ClearBackground(BLACK);
            DrawText(("%d – %d", player_1_score, player_2_score), 10, 10, 20, WHITE);
            fail = 0;
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
