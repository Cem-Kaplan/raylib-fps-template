#include <raylib.h>
#include <cmath>
#include <raymath.h>

int main() {
    InitWindow(800, 600, "Spül");
    SetTargetFPS(60);

        float yaw = 0.0f;
        float pitch = 0.0f;
        float sensitivity = 0.003f;
                
        Camera3D cam = {0};
        cam.position = {7,7,7};
        cam.up = {0,1,0};
        cam.fovy = 60;
        cam.target = {0,1,0};
        cam.projection = CAMERA_PERSPECTIVE;
        DisableCursor();

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);

        Vector2 mouse = GetMouseDelta();

        yaw -= mouse.x * sensitivity;
        pitch -= mouse.y * sensitivity;

        Vector3 forward = {
            cosf(pitch) * sinf(yaw),
            sinf(pitch),
            cosf(pitch) * cosf(yaw)
        };

        cam.target = Vector3Add(cam.position, forward);

        BeginMode3D(cam);

            DrawPlane({0,0,0}, {20,20}, BLUE);

        EndMode3D();
        EndDrawing();
    }

    CloseWindow();
}