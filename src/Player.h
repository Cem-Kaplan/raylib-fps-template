#pragma once

#include "raylib.h"
#include "raymath.h"

class Player {
public:
    Camera3D camera;

    Vector3 velocity;

    float yaw;
    float pitch;

    float speed;
    float jumpForce;
    float gravity;
    bool grounded;

    Player();
    void Update(float delta);
};
