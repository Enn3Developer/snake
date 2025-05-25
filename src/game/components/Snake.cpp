#include "Snake.h"

#include "../../engine/context/RunContext.h"

Snake::Snake(int length, int speed) {
    this->snakeGrid = new bool[SNAKE_HEIGHT][SNAKE_WIDTH]{false};
    this->snake_color_id = -1;
    this->apple_color_id = -1;
    this->length = length;
    this->speed = speed;
    this->remaining_ticks = 0;
    for (int x = 10; x < length + 10; x++) {
        this->snakeGrid[12][x] = true;
    }

    this->h_snake = position{10, 12};
    this->t_snake = position{length + 10 - 1, 12};
    this->apple = position{50, 20};
    this->direction = D_LEFT;
}

void Snake::tick() {
    this->remaining_ticks -= 1;

    if (this->remaining_ticks > 0) return;
    this->remaining_ticks = speed;

    int dir_x = 0;
    int dir_y = 0;

    switch (this->direction) {
        case D_UP:
            dir_y -= 1;
            break;
        case D_DOWN:
            dir_y += 1;
            break;
        case D_LEFT:
            dir_x -= 1;
        case D_RIGHT:
            dir_x += 1;
    }

    this->h_snake.x += dir_x;
    this->h_snake.y += dir_y;

    this->snakeGrid[this->h_snake.y][this->h_snake.x] = true;
}

int Snake::height() {
    return SNAKE_HEIGHT;
}

int Snake::width() {
    return SNAKE_WIDTH;
}

void Snake::draw(DrawContext *ctx) {
    if (this->snake_color_id == -1) {
        this->snake_color_id = ctx->registerColorPair(*new ColorPair(COLOR_GREEN, COLOR_BLACK));
    }

    if (this->apple_color_id == -1) {
        this->apple_color_id = ctx->registerColorPair(*new ColorPair(COLOR_RED, COLOR_BLACK));
    }

    for (int x = 0; x < SNAKE_WIDTH; x++) {
        for (int y = 0; y < SNAKE_HEIGHT; y++) {
            if (this->snakeGrid[y][x]) {
                ctx->coloredWriteAt(this->snake_color_id, "o", this->x + x, this->y + y);
            }
        }
    }

    ctx->coloredWriteAt(this->snake_color_id, "@", this->x + this->h_snake.x, this->y + this->h_snake.y);

    ctx->coloredWriteAt(this->apple_color_id, "$", this->x + this->apple.x, this->y + this->apple.y);
}

bool Snake::action(RunContext *ctx) {
    switch (ctx->getInput()) {
        case UP:
            if (this->direction == D_DOWN) break;
            this->direction = D_UP;
            break;
        case DOWN:
            if (this->direction == D_UP) break;
            this->direction = D_DOWN;
            break;
        case LEFT:
            if (this->direction == D_RIGHT) break;
            this->direction = D_LEFT;
            break;
        case RIGHT:
            if (this->direction == D_LEFT) break;
            this->direction = D_RIGHT;
            break;
        default: break;
    }

    return false;
}

