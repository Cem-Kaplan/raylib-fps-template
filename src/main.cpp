#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <cmath>

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "raylib FPS - Fixed Controls");

    DisableCursor();

    Camera3D camera = { 0 };
    camera.position = { 0.0f, 1.8f, 0.0f };
    camera.target = { 0.0f, 1.8f, 1.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 playerPosition = camera.position;
    float yaw = 0.0f;
    float pitch = 0.0f;
    const float playerHeight = 1.8f;

    Mesh weaponMesh = GenMeshCube(0.2f, 0.2f, 1.0f);
    Model weaponModel = LoadModelFromMesh(weaponMesh);

    Camera3D weaponCamera = { 0 };
    weaponCamera.position = { 0, 0, 0 };
    weaponCamera.target = { 0, 0, 1 };
    weaponCamera.up = { 0, 1, 0 };
    weaponCamera.fovy = 45.0f;
    weaponCamera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        Vector2 mouse = GetMouseDelta();
        yaw -= mouse.x * 0.003f;
        pitch -= mouse.y * 0.003f;
        pitch = Clamp(pitch, -1.2f, 1.2f);

        Vector3 forward = { sinf(yaw), 0.0f, cosf(yaw) };
        Vector3 right   = { -cosf(yaw), 0.0f, sinf(yaw) };

        float speed = 5.0f * GetFrameTime();

        bool isMoving = false;

        if (IsKeyDown(KEY_W)) { playerPosition = Vector3Add(playerPosition, Vector3Scale(forward, speed)); isMoving = true; }
        if (IsKeyDown(KEY_S)) { playerPosition = Vector3Subtract(playerPosition, Vector3Scale(forward, speed)); isMoving = true; }
        if (IsKeyDown(KEY_A)) { playerPosition = Vector3Subtract(playerPosition, Vector3Scale(right, speed));   isMoving = true; }
        if (IsKeyDown(KEY_D)) { playerPosition = Vector3Add(playerPosition, Vector3Scale(right, speed));        isMoving = true; }

        playerPosition.y = playerHeight;

        camera.position = playerPosition;
        camera.target = {
            playerPosition.x + cosf(pitch) * sinf(yaw),
            playerPosition.y + sinf(pitch),
            playerPosition.z + cosf(pitch) * cosf(yaw)
        };

        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode3D(camera);
            DrawPlane({ 0,0,0 }, { 50,50 }, DARKGREEN);
            DrawCube({ 5,1,5 }, 2,2,2, RED);
            DrawCube({ -4,1,-3 }, 2,2,2, BLUE);
        EndMode3D();

        BeginMode3D(weaponCamera);
        rlDisableDepthTest();

            float bob = 0.0f;
            float swayX = 0.0f;
            float swayY = 0.0f;

            if (isMoving)
            {
                bob = sinf(GetTime() * 10.0f) * 0.03f;
                swayX = mouse.x * 0.0005f;
                swayY = mouse.y * 0.0005f;
            }

            Vector3 weaponPos = {
                0.35f + swayX,
               -0.35f + bob - swayY,
                1.0f
            };

            DrawModel(weaponModel, weaponPos, 1.0f, GRAY);
        rlEnableDepthTest();

        EndMode3D();

        DrawText("+", screenWidth / 2 - 5, screenHeight / 2 - 10, 20, BLACK);
        DrawFPS(10, 10);

        EndDrawing();
    }

    UnloadModel(weaponModel);
    CloseWindow();
    return 0;
}
