#ifndef LASER_H
#define LASER_H
#include "../../sprites/Sprite.h"


class Laser final : public Sprite {
    const float speed{10};

public:
    Laser(const Texture &texture, Vector2 position, Rectangle collider);

    void draw() override;
};


#endif //LASER_H
