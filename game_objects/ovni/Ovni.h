#ifndef OVNI_H
#define OVNI_H
#include "../../sprites/Sprite.h"


class Ovni final : public Sprite {
    const float speed{1};

public:
    Ovni(const Texture &texture, Vector2 position, Rectangle collider);

    void draw() override;
};


#endif //OVNI_H
