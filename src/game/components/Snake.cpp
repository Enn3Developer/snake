#include "Snake.h"

#include <cstdlib>

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
        auto pos = position{x, 12};
        this->addSnakePosition(pos);
    }

    this->apple = position{50, 20};
    this->direction = D_UP;
}

void Snake::addSnakePosition(position pos) {
    auto new_pos = new list{pos, nullptr, nullptr};
    if (this->h_snake == nullptr) {
        this->h_snake = new_pos;
        this->t_snake = new_pos;
        return;
    }

    new_pos->next = this->h_snake;
    this->h_snake->prev = new_pos;
    this->h_snake = new_pos;
}

void Snake::generateApple() {
    int width = this->width();
    int height = this->height();

    do {
        this->apple = {rand() % width, rand() % height};
    } while (isInSnake(this->apple));
}

bool Snake::isInSnake(position pos) {
    for (p_list l = this->h_snake; l != nullptr; l = l->next) {
        if (pos.x == l->pos.x && pos.y == l->pos.y) return true;
    }

    return false;
}

int Snake::tick() {
    this->remaining_ticks -= 1;

    if (this->remaining_ticks > 0) return 0;
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
            break;
        case D_RIGHT:
            dir_x += 1;
            break;
    }

    auto pos = position{this->h_snake->pos.x + dir_x, this->h_snake->pos.y + dir_y};

    if (pos.x < 0) pos.x = this->width() - 1;
    if (pos.y < 0) pos.y = this->height() - 1;

    if (pos.x >= this->width()) pos.x = 0;
    if (pos.y >= this->height()) pos.y = 0;

    if (this->snakeGrid[pos.y][pos.x]) {
        return -1;
    }

    this->snakeGrid[this->t_snake->pos.y][this->t_snake->pos.x] = false;
    this->t_snake->prev->next = nullptr;
    this->t_snake = this->t_snake->prev;

    this->addSnakePosition(pos);
    this->snakeGrid[this->h_snake->pos.y][this->h_snake->pos.x] = true;

    if (pos.x == apple.x && pos.y == apple.y) {
        this->generateApple();
        return 5;
    }

    return 0;
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

    auto pos = this->h_snake;
    ctx->coloredWriteAt(this->snake_color_id, "@", this->x + pos->pos.x, this->y + pos->pos.y);
    pos = pos->next;

    while (pos != nullptr) {
        ctx->coloredWriteAt(this->snake_color_id, "o", this->x + pos->pos.x, this->y + pos->pos.y);
        pos = pos->next;
    }

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

    return true;
}

