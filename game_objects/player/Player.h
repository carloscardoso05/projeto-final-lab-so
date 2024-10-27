#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>
#include "../../sprites/Sprite.h"

class Player final : public Sprite {
    const float speed{10};
    bool canShoot{true};
    const float shootCooldownTime{0.5f}; // Tempo de recarga em segundos
    float shootCooldown{shootCooldownTime};

public:
    Player(const Texture &texture, Vector2 position, Rectangle collider);

    void moveLeft();

    void moveRight();

    void shoot();

    void draw() override;
};


#endif
