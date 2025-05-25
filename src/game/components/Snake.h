#ifndef SNAKE_H
#define SNAKE_H
#include "../../engine/Actionable.h"
#include "../../engine/Drawable.h"

#define SNAKE_WIDTH 80
#define SNAKE_HEIGHT 27

typedef enum direction {
    D_UP, D_DOWN, D_LEFT, D_RIGHT
} Direction;

class Snake final : public Drawable, public Actionable {
private:
    struct position {
        int x;
        int y;
    };

    bool (*snakeGrid)[SNAKE_WIDTH];
    int length;
    int speed;
    int remaining_ticks;
    int snake_color_id;
    int apple_color_id;
    position h_snake;
    position t_snake;
    position apple;
    Direction direction;

public:
    Snake(int length, int speed);

    void tick();

    int width() override;

    int height() override;

    void draw(DrawContext *ctx) override;

    bool action(RunContext *ctx) override;
};

#endif
