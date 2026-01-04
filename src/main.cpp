#include "raylib.h"
#include "Player.h"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT); // Antialiasing
    InitWindow(1280, 720, "raylib FPS Template (Clean)");
    SetTargetFPS(60);

    Player player;

    while (!WindowShouldClose()) {
        float delta = GetFrameTime();
        player.Update(delta);

        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode3D(player.camera);

        DrawPlane({ 0, 0, 0 }, { 100, 100 }, DARKGREEN);
        DrawCube({ 5, 1, 5 }, 2, 2, 2, RED);
        DrawCube({ -5, 1, -5 }, 2, 2, 2, BLUE);

        EndMode3D();

        DrawFPS(10, 10);
        DrawText("WASD | Maus | Space = Jump | ESC = Quit", 10, 40, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
