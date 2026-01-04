#include "Player.h"
#include <cmath>

Player::Player() {
    camera.position = { 0.0f, 1.8f, 0.0f };
    camera.target   = { 0.0f, 1.8f, 1.0f };
    camera.up       = { 0.0f, 1.0f, 0.0f };
    camera.fovy     = 75.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    yaw = 0.0f;
    pitch = 0.0f;

    velocity = { 0.0f, 0.0f, 0.0f };

    speed = 6.0f;
    jumpForce = 3.5f;
    gravity = 9.8f;
    grounded = true;

    DisableCursor();
}

void Player::Update(float delta) {
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
    if (IsKeyDown(KEY_W))
        camera.position = Vector3Add(camera.position, Vector3Scale(forward, speed * delta));
    if (IsKeyDown(KEY_S))
        camera.position = Vector3Subtract(camera.position, Vector3Scale(forward, speed * delta));
    if (IsKeyDown(KEY_D))
        camera.position = Vector3Add(camera.position, Vector3Scale(right, speed * delta));
    if (IsKeyDown(KEY_A))
        camera.position = Vector3Subtract(camera.position, Vector3Scale(right, speed * delta));

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
