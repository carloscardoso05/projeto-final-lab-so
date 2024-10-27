#include "Ovni.h"

#include <ranges>

#include "../laser/Laser.h"

Ovni::Ovni(const Texture &texture, const Vector2 position, const Rectangle collider) : Sprite(
    texture, position, collider) {
}

void Ovni::draw() {
    for (const auto &sprite: sprites | std::views::values) {
        if (const auto *laser = dynamic_cast<Laser *>(sprite)) {
            if (laser->checkCollision(*this)) {
                sprites.erase(id);
                sprites.erase(laser->id);
                break;
            }
        }
    }
    position.y += speed;
    collider.y = position.y;
    Sprite::draw();
}
