#include "Sprite.h"

#include <map>
#include <ranges>

#include "../configuration/Configuration.cpp"

uint Sprite::last_id = 0;
std::map<uint, Sprite *> Sprite::sprites;

Sprite::Sprite(const Texture &texture, const Vector2 position, const Rectangle collider) : texture(texture),
    position(position), collider(collider) {
    this->id = last_id++;
    sprites.emplace(this->id, this);
    puts("Sprite adicionado");
}

void Sprite::draw() {
    collider.x = position.x;
    collider.y = position.y;
    DrawTexture(this->texture, static_cast<int>(this->position.x), static_cast<int>(this->position.y), WHITE);
    if constexpr (DEBUG)
        DrawRectangleLines(static_cast<int>(this->collider.x), static_cast<int>(this->collider.y),
                           static_cast<int>(this->collider.width), static_cast<int>(this->collider.height), RED);
}

void Sprite::destroy() const {
    UnloadTexture(this->texture);
    sprites.erase(this->id);
}

bool Sprite::checkCollision(const Sprite &other) const {
    return CheckCollisionRecs(this->collider, other.collider);
}

void Sprite::drawAll() {
    for (const auto val: sprites | std::views::values) {
        val->draw();
    }
}
