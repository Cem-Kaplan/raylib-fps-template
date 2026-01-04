#include "raylib.h"
#include "Player.h"
Shader lightingShader;
int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT); // Antialiasing
    InitWindow(1280, 720, "raylib FPS Template (Clean)");
    SetTargetFPS(60);
    lightingShader = LoadShader(
        "assets/shaders/lighting.vs",
        "assets/shaders/lighting.fs"
    );

    // Shader Uniforms
    int lightDirLoc = GetShaderLocation(lightingShader, "lightDir");
    int lightColorLoc = GetShaderLocation(lightingShader, "lightColor");
    int viewPosLoc = GetShaderLocation(lightingShader, "viewPos");

    // Sonne
    Vector3 sunDirection = { -0.5f, -1.0f, -0.3f };
    Vector3 sunColor = { 1.0f, 0.95f, 0.8f };

    Player player;

    BoundingBox walls[] = {
        { { 4, 0, 4 },   { 6, 2, 6 } },     // Cube bei (5,1,5)
        { { -6, 0, -6 }, { -4, 2, -4 } }    // Cube bei (-5,1,-5)
    };

    int wallCount = 2;


    while (!WindowShouldClose()) {
        float delta = GetFrameTime();
        player.Update(delta, walls, wallCount);
SetShaderValue(lightingShader, lightDirLoc, &sunDirection, SHADER_UNIFORM_VEC3);
SetShaderValue(lightingShader, lightColorLoc, &sunColor, SHADER_UNIFORM_VEC3);
SetShaderValue(lightingShader, viewPosLoc, &player.camera.position, SHADER_UNIFORM_VEC3);

        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode3D(player.camera);

        BeginShaderMode(lightingShader);

        DrawPlane({ 0, 0, 0 }, { 100, 100 }, GREEN);
        DrawCube({ 5, 1, 5 }, 2, 2, 2, GRAY);
        DrawCube({ -5, 1, -5 }, 2, 2, 2, WHITE);

        EndShaderMode();

        EndMode3D();


        DrawFPS(10, 10);
        DrawText("WASD | Maus | Space = Jump | ESC = Quit", 10, 40, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
