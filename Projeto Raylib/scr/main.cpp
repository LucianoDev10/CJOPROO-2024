#include "raylib.h"
#include <ctime>
#include "jogos.h"

void JogoReflexo() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Jogo de Reflexo - Raylib");

    int score = 0;
    bool gameOver = false;
    int targetKey = GetRandomValue(KEY_A, KEY_Z);

    // Configura o tempo limite inicial e a variável para controle do tempo
    float timeLimit = 2.0f; // Tempo limite inicial em segundos
    double startTime = GetTime();

    SetTargetFPS(60); // Define o FPS do jogo

    while (!WindowShouldClose()) {
        double currentTime = GetTime(); // Atualiza o tempo atual no início de cada loop

        if (!gameOver) {
            // Verifica se o tempo limite foi excedido
            if (currentTime - startTime > timeLimit) {
                gameOver = true;
            }

            // Verifica se a tecla correta foi pressionada
            if (IsKeyPressed(targetKey)) {
                score++;
                targetKey = GetRandomValue(KEY_A, KEY_Z); // Nova tecla alvo
                startTime = currentTime; // Reseta o tempo
                timeLimit *= 0.95f; // Reduz o tempo limite em 5% para aumentar a dificuldade
            }
        } else {
            // Reinicia o jogo se apertar ENTER
            if (IsKeyPressed(KEY_ENTER)) {
                gameOver = false;
                score = 0;
                targetKey = GetRandomValue(KEY_A, KEY_Z);
                timeLimit = 2.0f; // Reseta o tempo limite
                startTime = GetTime();
            }
        }

        // Renderização
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!gameOver) {
            DrawText("Pressione a tecla certa!", 100, 100, 20, DARKGRAY);
            DrawText(TextFormat("Pressione: %c", targetKey), 100, 150, 30, BLUE);
            DrawText(TextFormat("Score: %i", score), 10, 10, 20, DARKGRAY);
            DrawText(TextFormat("Tempo restante: %.2f", timeLimit - (currentTime - startTime)), 10, 40, 20, RED);
        } else {
            // Exibe a tela de Game Over com a pontuação final
            DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2, screenHeight / 2 - 20, 40, RED);
            DrawText(TextFormat("Score Final: %i", score), screenWidth / 2 - MeasureText("Score Final: 100", 20) / 2, screenHeight / 2 + 30, 20, DARKGRAY);
            DrawText("Pressione ENTER para reiniciar", screenWidth / 2 - MeasureText("Pressione ENTER para reiniciar", 20) / 2, screenHeight / 2 + 60, 20, DARKGRAY);
        }

        EndDrawing();
    }

    // Fecha a janela e libera recursos
    CloseWindow();
}
