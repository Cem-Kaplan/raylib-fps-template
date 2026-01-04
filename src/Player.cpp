#include "Player.h"
#include <cmath>

static bool CheckCollisionPlayerBox(Vector3 pos, float radius, BoundingBox box) {
    Vector3 closest;

    closest.x = Clamp(pos.x, box.min.x, box.max.x);
    closest.y = Clamp(pos.y, box.min.y, box.max.y);
    closest.z = Clamp(pos.z, box.min.z, box.max.z);

    float dx = pos.x - closest.x;
    float dz = pos.z - closest.z;

    return (dx*dx + dz*dz) < (radius * radius);
}


Player::Player() {
    camera.position = { 0.0f, 1.8f, 0.0f };
    camera.target   = { 0.0f, 1.8f, 1.0f };
    camera.up       = { 0.0f, 1.0f, 0.0f };
    camera.fovy     = 75.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    radius = 0.35f;
    height = 1.8f;

    yaw = 0.0f;
    pitch = 0.0f;

    velocity = { 0.0f, 0.0f, 0.0f };

    speed = 6.0f;
    jumpForce = 3.5f;
    gravity = 9.8f;
    grounded = true;

    DisableCursor();
}

void Player::Update(float delta, BoundingBox* walls, int wallCount) {
    // =====================
    // Maus-Look (Yaw/Pitch)
    // =====================
    Vector2 mouse = GetMouseDelta();
    float sensitivity = 0.0025f;

    yaw   -= mouse.x * sensitivity;
    pitch -= mouse.y * sensitivity;

    pitch = Clamp(pitch, -1.5f, 1.5f);

    Vector3 forward = {
        cosf(pitch) * sinf(yaw),
        sinf(pitch),
        cosf(pitch) * cosf(yaw)
    };
    forward = Vector3Normalize(forward);

    Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));

    // =====================
    // Bewegung
    // =====================
    Vector3 move = { 0 };

    if (IsKeyDown(KEY_W)) move = Vector3Add(move, forward);
    if (IsKeyDown(KEY_S)) move = Vector3Subtract(move, forward);
    if (IsKeyDown(KEY_D)) move = Vector3Add(move, right);
    if (IsKeyDown(KEY_A)) move = Vector3Subtract(move, right);

    if (Vector3Length(move) > 0.0f)
        move = Vector3Normalize(move);

    move = Vector3Scale(move, speed * delta);

    // X Bewegung
    Vector3 nextPos = camera.position;
    nextPos.x += move.x;

    bool hit = false;
    for (int i = 0; i < wallCount; i++) {
        if (CheckCollisionPlayerBox(nextPos, radius, walls[i])) {
            hit = true;
            break;
        }
    }
    if (!hit)
        camera.position.x = nextPos.x;

    // Z Bewegung
    nextPos = camera.position;
    nextPos.z += move.z;

    hit = false;
    for (int i = 0; i < wallCount; i++) {
        if (CheckCollisionPlayerBox(nextPos, radius, walls[i])) {
            hit = true;
            break;
        }
    }
    if (!hit)
        camera.position.z = nextPos.z;

    // =====================
    // Jump + Gravity
    // =====================
    if (grounded && IsKeyPressed(KEY_SPACE)) {
        velocity.y = jumpForce;
        grounded = false;
    }

    velocity.y -= gravity * delta;
    camera.position.y += velocity.y * delta;

    if (camera.position.y <= 1.8f) {
        camera.position.y = 1.8f;
        velocity.y = 0.0f;
        grounded = true;
    }

    // =====================
    // Kamera-Target
    // =====================
    camera.target = Vector3Add(camera.position, forward);
}
