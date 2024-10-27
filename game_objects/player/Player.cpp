#include "Player.h"

#include <cstdio>

#include "../../sprites/Sprite.h"
#include "../laser/Laser.h"

Player::Player(const Texture &texture, const Vector2 position, const Rectangle collider) : Sprite(
    texture, position, collider) {
}

void Player::moveLeft() {
    position.x -= speed;
}

void Player::moveRight() {
    position.x += speed;
}

void Player::shoot() {
    if (!canShoot) return;
    canShoot = false;
    new Laser(LoadTexture("../assets/laser.png"), {position.x + collider.width / 2, position.y}, {0, 0, 8, 8});
}

void Player::draw() {
    shootCooldown -= GetFrameTime();

    if (shootCooldown <= 0) {
        canShoot = true;
        shootCooldown = shootCooldownTime;
    }
    Sprite::draw();
}
