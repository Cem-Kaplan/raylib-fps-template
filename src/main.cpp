#include <raylib.h>

int main() {
    InitWindow(800, 600, "Spiel");
    SetTargetFPS(60);

        Camera3D cam = {0};
        cam.position = {7,7,7};
        cam.up = {0,1,0};
        cam.fovy = 60;
        cam.projection = CAMERA_PERSPECTIVE;
        cam.target = {0,1,0};

        float yaw = 0.0f;
        float pitch = 0.0f;

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);
        
        
        
        BeginMode3D(cam);

        DrawPlane({0,0,0}, {20,20}, GREEN);

        EndMode3D();
        EndDrawing();
    }

    CloseWindow();
}