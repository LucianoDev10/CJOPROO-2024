#include "raylib.h"
#include <ctime>
#include "jogos.h"

void JogoReflexo() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Jogo de Reflexo - Raylib");

    // Tenta carregar a textura
    Texture2D backgroundTexture = LoadTexture("assets/background.jpg");
    
    
    if (backgroundTexture.id == 0) {  // Verifica se a textura foi carregada
        DrawText("Erro ao carregar a imagem", 10, 10, 20, RED);
        EndDrawing();
        CloseWindow();
        return;
    }

    int score = 0;
    bool gameOver = false;
    int targetKey = GetRandomValue(KEY_A, KEY_Z);

    float timeLimit = 2.0f;
    double startTime = GetTime();

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        double currentTime = GetTime();

        if (!gameOver) {
            if (currentTime - startTime > timeLimit) gameOver = true;

            if (IsKeyPressed(targetKey)) {
                score++;
                targetKey = GetRandomValue(KEY_A, KEY_Z);
                startTime = currentTime;
                timeLimit *= 0.95f;
            }
        } else {
            if (IsKeyPressed(KEY_ENTER)) {
                gameOver = false;
                score = 0;
                targetKey = GetRandomValue(KEY_A, KEY_Z);
                timeLimit = 2.0f;
                startTime = GetTime();
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Desenha a textura do background, se carregada
        if (backgroundTexture.id != 0) {
            DrawTexture(backgroundTexture, 0, 0, WHITE);
        }
        
        DrawText("Pressione a tecla certa!", 100, 100, 20, DARKGRAY);
        DrawText(TextFormat("Pressione: %c", targetKey), 100, 150, 30, BLUE);
        DrawText(TextFormat("Score: %i", score), 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("Tempo restante: %.2f", timeLimit - (currentTime - startTime)), 10, 40, 20, RED);

        if (gameOver) {
            DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2, screenHeight / 2 - 20, 40, RED);
            DrawText("Pressione ENTER para reiniciar", screenWidth / 2 - MeasureText("Pressione ENTER para reiniciar", 20) / 2, screenHeight / 2 + 30, 20, DARKGRAY);
        }

        EndDrawing();
    }

    UnloadTexture(backgroundTexture);
    CloseWindow();
}
