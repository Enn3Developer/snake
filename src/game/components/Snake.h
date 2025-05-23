#ifndef SNAKE_H
#define SNAKE_H
#include "../../engine/Actionable.h"
#include "../../engine/Drawable.h"

class Snake final : public Drawable, public Actionable {
public:
    int width() override;

    int height() override;

    void draw(DrawContext *ctx) override;

    bool action(RunContext *ctx) override;
};

#endif
