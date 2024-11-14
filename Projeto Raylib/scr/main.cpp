#include "raylib.h"
#include "jogos.h"  // Adicionando o cabeçalho com as declarações dos jogos

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "Menu Principal - Selecione um Jogo");

    // Carrega a imagem do logo
    Texture2D logo = LoadTexture("logo.png");

    if (logo.id == 0) {  // Verifica se a textura foi carregada corretamente
        DrawText("Erro ao carregar a imagem do logo", 10, 10, 20, RED);
        EndDrawing();
        CloseWindow();
        return -1;
    }
    
    int option = 0;
    
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Desenha o logo no canto superior esquerdo
        DrawTexture(logo, 10, 10, WHITE);

        DrawText("Escolha um Jogo", screenWidth / 2 - 80, 50, 20, DARKGRAY);
        DrawText("1. Jogo de Esquiva", screenWidth / 2 - 100, 150, 20, option == 0 ? BLUE : DARKGRAY);
        DrawText("2. Jogo de Captura", screenWidth / 2 - 100, 200, 20, option == 1 ? BLUE : DARKGRAY);
        DrawText("3. Jogo de Reflexo", screenWidth / 2 - 100, 250, 20, option == 2 ? BLUE : DARKGRAY);

        if (IsKeyPressed(KEY_DOWN)) option = (option + 1) % 3;
        if (IsKeyPressed(KEY_UP)) option = (option - 1 + 3) % 3;

        if (IsKeyPressed(KEY_ENTER)) {
            if (option == 0) JogoEsquiva();
            else if (option == 1) JogoCaptura();
            else if (option == 2) JogoReflexo();
        }
        
        EndDrawing();
    }
    
    // Libera a textura do logo
    UnloadTexture(logo);
    
    CloseWindow();
    return 0;
}
