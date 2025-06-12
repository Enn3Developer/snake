#ifndef SNAKE_H
#define SNAKE_H
#include "../../engine/Actionable.h"
#include "../../engine/Drawable.h"

#define SNAKE_WIDTH 78
#define SNAKE_HEIGHT 28
#define HORIZONTAL_MOVEMENT_TICKS 3
#define BONUS_TICKS 80
#define BASE_POINTS 7
#define BONUS_POINTS 3
#define MAX_INPUT 5

typedef enum direction {
    D_UP, D_DOWN, D_LEFT, D_RIGHT, D_NONE
} Direction;

typedef enum score_type {
    S_NONE, S_LOSE, S_OK, S_GOOD, S_GREAT
} ScoreType;

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

    struct buffer_list {
        Direction dir;
        buffer_list *next;
    };

    typedef buffer_list *p_buffer_list;

    p_buffer_list h_input;
    int len_input;

    bool (*snakeGrid)[SNAKE_WIDTH];
    int length;
    int speed;
    int remaining_ticks;
    int snake_color_id;
    int apple_color_id;
    position apple;
    Direction direction;
    Direction currentDirection;
    int horizontalMovementTicks;
    int bonusTicks;
    int combo;

public:
    Snake(int length, int speed);

    void addSnakePosition(position pos);

    void generateApple();

    bool isInSnake(position pos);

    ScoreType tick(int *combo);

    void addInput(Direction dir);

    Direction popInput();

    int width() override;

    int height() override;

    void draw(DrawContext *ctx) override;

    bool action(RunContext *ctx) override;
};

#endif
