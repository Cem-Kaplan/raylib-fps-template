#include "raylib.h"
#include "cmath"
#include "raymath.h"

int main() {
    const int WIN_WIDTH = 800;
    const int WIN_HEIGHT = 600;
    const char *WIN_TITLE = "Spiel";
    int FOV = 60;

    InitWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
    SetTargetFPS(60);
    DisableCursor();

    Camera3D cam = {0};
    cam.position = {7,7,7};
    cam.up = {0,1,0};
    cam.target = {0,1,0};
    cam.fovy = FOV;
    cam.projection = CAMERA_PERSPECTIVE;

    float yaw = 0.0f;
    float pitch = 0.0f;
    float sensitivity = 0.003f;

    Texture2D textur = LoadTexture("../assets/textures/Ground.png");

    Mesh mesh = GenMeshCube(2,2,2);
    Model model = LoadModelFromMesh(mesh);

    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = textur;
float speed;
    while(!WindowShouldClose()) {
        ClearBackground(SKYBLUE);

        Vector2 mouse = GetMouseDelta();

        yaw -= mouse.x * sensitivity;
        pitch -= mouse.y * sensitivity;

        if(pitch > 1.5f) pitch = 1.5f;
        if(pitch < -1.5f) pitch = -1.5f;

        Vector3 forward = {
            cosf(pitch) * sinf(yaw),
            sinf(pitch),
            cosf(pitch) * cosf(yaw)
        };

        cam.target = Vector3Add(cam.position, forward);
        // lernen
        Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, cam.up));


        if (IsKeyDown(KEY_W)) cam.position = Vector3Add(cam.position, Vector3Scale(forward, speed));
        if (IsKeyDown(KEY_S)) cam.position = Vector3Subtract(cam.position, Vector3Scale(forward, speed));
        if (IsKeyDown(KEY_D)) cam.position = Vector3Add(cam.position, Vector3Scale(right, speed));
        if (IsKeyDown(KEY_A)) cam.position = Vector3Subtract(cam.position, Vector3Scale(right, speed));

        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            speed = 10.0f * GetFrameTime();
        } else {
            speed = 5.0f * GetFrameTime();
        }

        cam.target = Vector3Add(cam.position, forward);
        //
        BeginDrawing();
        BeginMode3D(cam);

            DrawPlane({0,0,0}, {50,50}, GREEN);
            DrawCube({45, 0, 5}, 5, 5, 5, GRAY);
            DrawModel(model, {-45,0,0}, 5, WHITE);

        EndMode3D();
        EndDrawing();
    }
}