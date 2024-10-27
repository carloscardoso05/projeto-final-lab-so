#include "Laser.h"

Laser::Laser(const Texture &texture, const Vector2 position, const Rectangle collider) : Sprite(
    texture, position, collider) {
}

void Laser::draw() {
    position.y -= speed;
    collider.y = position.y;
    Sprite::draw();
}
