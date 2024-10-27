#ifndef SPRITE_H
#define SPRITE_H
#include <map>
#include <raylib.h>
#include <vector>

class Sprite {
protected:
    static uint last_id;
    Texture texture{};
    Vector2 position{};
    Rectangle collider{};

public:
    uint id{};

    virtual ~Sprite() = default;

    Sprite(const Texture &texture, Vector2 position, Rectangle collider);

    static std::map<uint, Sprite *> sprites;

    static void drawAll();

    virtual void draw();

    void destroy() const;

    [[nodiscard]]
    Vector2 getPosition() const { return position; };

    [[nodiscard]]
    Rectangle getCollider() const { return collider; };

    [[nodiscard]]
    bool checkCollision(const Sprite &other) const;
};


#endif
