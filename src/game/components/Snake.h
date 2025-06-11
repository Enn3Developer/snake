#ifndef SNAKE_H
#define SNAKE_H
#include "../../engine/Actionable.h"
#include "../../engine/Drawable.h"

#define SNAKE_WIDTH 78
#define SNAKE_HEIGHT 28
#define HORIZONTAL_MOVEMENT_TICKS 3

typedef enum direction {
    D_UP, D_DOWN, D_LEFT, D_RIGHT
} Direction;

class Snake final : public Drawable, public Actionable {
private:
    struct position {
        int x;
        int y;
    };

    struct list {
        position pos;
        list *next;
        list *prev;
    };

    typedef list *p_list;

    p_list h_snake;
    p_list t_snake;

    bool (*snakeGrid)[SNAKE_WIDTH];
    int length;
    int speed;
    int remaining_ticks;
    int snake_color_id;
    int apple_color_id;
    position apple;
    Direction direction;
    int horizontalMovementTicks;

public:
    Snake(int length, int speed);

    void addSnakePosition(position pos);

    void generateApple();

    bool isInSnake(position pos);

    int tick();

    int width() override;

    int height() override;

    void draw(DrawContext *ctx) override;

    bool action(RunContext *ctx) override;
};

#endif
