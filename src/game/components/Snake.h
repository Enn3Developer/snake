#ifndef SNAKE_H
#define SNAKE_H
#include "../../engine/Actionable.h"
#include "../../engine/Drawable.h"

#define SNAKE_WIDTH 80
#define SNAKE_HEIGHT 27

class Snake final : public Drawable, public Actionable {
private:
    bool *snakeGrid[];
    int length;
    int h_snake;
    int t_snake;
    int apple;

public:
    int width() override;

    int height() override;

    void draw(DrawContext *ctx) override;

    bool action(RunContext *ctx) override;
};

#endif
