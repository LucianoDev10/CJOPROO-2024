#include "raylib.h"
#include "jogos.h"

void JogoEsquiva() {
    // Inicializa a janela
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Jogo de Esquiva - Raylib");

    // Configura o jogador
    Rectangle player = { 400.0f, 400.0f, 50.0f, 50.0f };
    float playerSpeed = 5.0f;

    // Configura obstáculos
    const int numObstacles = 5;  // Número de obstáculos
    Rectangle obstacles[numObstacles];
    float obstacleSpeed = 5.0f;

    // Inicializa os obstáculos em posições aleatórias
    for (int i = 0; i < numObstacles; i++) {
        obstacles[i] = { GetRandomValue(0, screenWidth - 50), GetRandomValue(-screenHeight, 0), 50, 50 };
    }

    int score = 0;  // Pontuação do jogador
    bool gameOver = false;

    SetTargetFPS(60); // Define o FPS do jogo

    // Loop principal do jogo
    while (!WindowShouldClose()) {
        // Lógica do jogo
        if (!gameOver) {
            // Movimento do jogador
            if (IsKeyDown(KEY_RIGHT) && player.x + player.width < screenWidth) player.x += playerSpeed;
            if (IsKeyDown(KEY_LEFT) && player.x > 0) player.x -= playerSpeed;

            // Movimento dos obstáculos
            for (int i = 0; i < numObstacles; i++) {
                obstacles[i].y += obstacleSpeed;

                // Verifica se o obstáculo saiu da tela e o reposiciona
                if (obstacles[i].y > screenHeight) {
                    obstacles[i].x = GetRandomValue(0, screenWidth - obstacles[i].width);
                    obstacles[i].y = GetRandomValue(-100, 0);  // Reposiciona acima da tela
                    score++; // Incrementa a pontuação ao evitar um obstáculo
                }

                // Verifica colisão entre o jogador e o obstáculo
                if (CheckCollisionRecs(player, obstacles[i])) {
                    gameOver = true;
                }
            }
        } else {
            // Reinicia o jogo se apertar ENTER
            if (IsKeyPressed(KEY_ENTER)) {
                gameOver = false;
                score = 0;
                player.x = 400.0f;
                player.y = 400.0f;
                
                // Reposiciona obstáculos aleatoriamente acima da tela
                for (int i = 0; i < numObstacles; i++) {
                    obstacles[i].x = GetRandomValue(0, screenWidth - 50);
                    obstacles[i].y = GetRandomValue(-screenHeight, 0);
                }
            }
        }

        // Renderização
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!gameOver) {
            // Desenha o jogador e os obstáculos
            DrawRectangleRec(player, BLUE);
            for (int i = 0; i < numObstacles; i++) {
                DrawRectangleRec(obstacles[i], RED);
            }

            // Desenha a pontuação
            DrawText(TextFormat("Score: %i", score), 10, 10, 20, DARKGRAY);
        } else {
            // Exibe a tela de Game Over
            DrawText("GAME OVER", screenWidth / 2 - MeasureText("GAME OVER", 40) / 2, screenHeight / 2 - 20, 40, RED);
            DrawText("Pressione ENTER para reiniciar", screenWidth / 2 - MeasureText("Pressione ENTER para reiniciar", 20) / 2, screenHeight / 2 + 30, 20, DARKGRAY);
        }

        EndDrawing();
    }

    // Fecha a janela e libera recursos
    CloseWindow();
}
