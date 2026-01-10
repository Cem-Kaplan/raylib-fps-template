#include "raylib.h"
#include "raymath.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(screenWidth, screenHeight, "Simple FPS - Ground Movement");

    DisableCursor(); // 🔒 Cursor entfernen (FPS-Style)

    Camera3D camera = { 0 };
    camera.position = { 0.0f, 1.8f, 0.0f };   // Spielerhöhe
    camera.target = { 0.0f, 1.8f, 1.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 playerPosition = camera.position;

    float yaw = 0.0f;
    float pitch = 0.0f;

    const float playerHeight = 1.8f;
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // 🖱️ Maussteuerung
        Vector2 mouseDelta = GetMouseDelta();
        yaw -= mouseDelta.x * 0.003f;
        pitch -= mouseDelta.y * 0.003f;
        pitch = Clamp(pitch, -1.2f, 1.2f); // kein Überkopf-Blick

        // Blickrichtung (Y bleibt 0 für Bewegung)
        Vector3 forward = {
            sinf(yaw),
            0.0f,
            cosf(yaw)
        };

        Vector3 right = {
            cosf(yaw),
            0.0f,
            -sinf(yaw)
        };

        float speed = 5.0f * GetFrameTime();

        // 🚶 Bewegung nur auf XZ-Ebene
        if (IsKeyDown(KEY_W)) playerPosition = Vector3Add(playerPosition, Vector3Scale(forward, speed));
        if (IsKeyDown(KEY_S)) playerPosition = Vector3Subtract(playerPosition, Vector3Scale(forward, speed));
        if (IsKeyDown(KEY_D)) playerPosition = Vector3Subtract(playerPosition, Vector3Scale(right, speed));
        if (IsKeyDown(KEY_A)) playerPosition = Vector3Add(playerPosition, Vector3Scale(right, speed));

        // Spieler bleibt auf Bodenhöhe
        playerPosition.y = playerHeight;

        // Kamera aktualisieren
        camera.position = playerPosition;
        camera.target = {
            playerPosition.x + cosf(pitch) * sinf(yaw),
            playerPosition.y + sinf(pitch),
            playerPosition.z + cosf(pitch) * cosf(yaw)
        };

        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode3D(camera);
            // 🟩 Boden (Plane)
            DrawPlane({ 0, 0, 0 }, { 50, 50 }, DARKGREEN);

            // 🧱 Objekte
            DrawCube({ 5, 1, 5 }, 2, 2, 2, RED);
            DrawCube({ -4, 1, -3 }, 2, 2, 2, BLUE);
        EndMode3D();

        DrawFPS(10, 10);
        DrawText("WASD bewegen | Maus schauen | ESC = Exit", 10, 30, 18, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
