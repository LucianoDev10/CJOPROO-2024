#include "raylib.h"
#include "jogos.h"

void JogoCaptura() {
    // Inicializa a janela
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Jogo de Captura - Raylib");

    // Configura o jogador
    Rectangle player = { 400.0f, 400.0f, 50.0f, 50.0f };
    float playerSpeed = 5.0f;

    // Configura múltiplos itens
    const int itemCount = 5;
    Rectangle items[itemCount];
    float itemSpeeds[itemCount];
    
    for (int i = 0; i < itemCount; i++) {
        items[i] = { static_cast<float>(GetRandomValue(0, screenWidth - 30)), 
                     static_cast<float>(GetRandomValue(-screenHeight, 0)), 
                     30, 30 };
        itemSpeeds[i] = 2.0f + i; // Velocidades iniciais diferentes para cada item
    }

    int score = 0;           // Pontuação do jogador
    int timeLeft = 30;        // Tempo restante em segundos
    double lastTime = GetTime(); // Marca o último tempo para contagem regressiva
    bool gameOver = false;

    SetTargetFPS(60); // Define o FPS do jogo

    // Loop principal do jogo
    while (!WindowShouldClose()) {
        // Atualização do tempo
        double currentTime = GetTime();
        if (currentTime - lastTime >= 1.0 && !gameOver) {
            timeLeft--;
            lastTime = currentTime;
            if (timeLeft <= 0) gameOver = true; // Termina o jogo quando o tempo chega a zero
        }

        // Lógica do jogo
        if (!gameOver) {
            // Movimento do jogador
            if (IsKeyDown(KEY_RIGHT) && player.x + player.width < screenWidth) player.x += playerSpeed;
            if (IsKeyDown(KEY_LEFT) && player.x > 0) player.x -= playerSpeed;

            // Movimento e reaparecimento dos itens
            for (int i = 0; i < itemCount; i++) {
                items[i].y += itemSpeeds[i];

                if (items[i].y > screenHeight) {
                    items[i].x = static_cast<float>(GetRandomValue(0, screenWidth - items[i].width));
                    items[i].y = static_cast<float>(GetRandomValue(-100, 0));
                    itemSpeeds[i] += 0.2f; // Aumenta a velocidade para dificultar
                }

                // Verifica captura de cada item
                if (CheckCollisionRecs(player, items[i])) {
                    score += 10; // Incrementa a pontuação
                    items[i].x = static_cast<float>(GetRandomValue(0, screenWidth - items[i].width));
                    items[i].y = static_cast<float>(GetRandomValue(-100, 0));
                    itemSpeeds[i] += 0.3f; // Aumenta a velocidade após captura
                }
            }
        } else {
            // Reinicia o jogo se o jogador pressionar ENTER
            if (IsKeyPressed(KEY_ENTER)) {
                gameOver = false;
                score = 0;
                timeLeft = 30;
                player.x = 400.0f;

                for (int i = 0; i < itemCount; i++) {
                    items[i].x = static_cast<float>(GetRandomValue(0, screenWidth - items[i].width));
                    items[i].y = static_cast<float>(GetRandomValue(-100, 0));
                    itemSpeeds[i] = 2.0f + i;
                }
            }
        }

        // Renderização
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!gameOver) {
            // Desenha o jogador e os itens
            DrawRectangleRec(player, BLUE);
            for (int i = 0; i < itemCount; i++) {
                DrawRectangleRec(items[i], GREEN);
            }

            // Exibe a pontuação e o tempo restante
            DrawText(TextFormat("Score: %i", score), 10, 10, 20, DARKGRAY);
            DrawText(TextFormat("Time: %i", timeLeft), screenWidth - 100, 10, 20, DARKGRAY);
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
