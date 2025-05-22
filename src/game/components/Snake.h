#ifndef SNAKE_H
#define SNAKE_H
#include "../../engine/Drawable.h"

class Snake final : public Drawable {
public:
    int width() override;

    int height() override;

    void draw(DrawContext *ctx) override;
};

#endif
