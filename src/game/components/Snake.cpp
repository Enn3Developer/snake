#include "Snake.h"

int Snake::height() {
    return SNAKE_HEIGHT;
}

int Snake::width() {
    return SNAKE_WIDTH;
}

void Snake::draw(DrawContext *ctx) {
}

bool Snake::action(RunContext *ctx) {
    return false;
}

