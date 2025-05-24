#include "Modal.h"

#include <cstring>

#include "../context/RunContext.h"

Modal::Modal(const char *message) {
    this->message = message;
    this->open = false;
    this->confirm = false;
    this->confirm_focused = true;
    this->color_id = -1;
}

int Modal::height() {
    return 5;
}

int Modal::width() {
    // larghezza minima (cancel + ok + spacing)
    int min = 6 + 2 + 1;
    // larghezza del contenuto del messaggio
    int message_len = strlen(this->message);

    // ritorna il valore piu' grande tra i due + il padding ai lati
    return (min > message_len ? min : message_len) + 2;
}

void Modal::openModal() {
    this->open = true;
    this->confirm = false;
    this->confirm_focused = true;
}

void Modal::closeModal() {
    this->open = false;
}

bool Modal::isOpen() {
    return this->open;
}

bool Modal::isConfirmed() {
    return this->confirm;
}

bool Modal::action(RunContext *ctx) {
    switch (ctx->getInput()) {
        case ESCAPE:
        case NONE:
            break;
        case DOWN:
        case UP:
        case LEFT:
        case RIGHT:
            this->confirm_focused = !this->confirm_focused;
            break;
        case CONFIRM:
            this->confirm = this->confirm_focused;
            this->closeModal();
            break;
        case CLICKED:
            int *position = ctx->getMousePosition();
            int x = position[0];
            int y = position[1];
            int width = this->width();
            if (y == this->y + 3) {
                if (x >= this->x + 1 && x < this->x + 1 + 6) {
                    this->confirm_focused = false;
                    this->confirm = false;
                    this->closeModal();
                    break;
                }
                if (x >= this->x + width - 3 && x < this->x + width - 1) {
                    this->confirm_focused = true;
                    this->confirm = true;
                    this->closeModal();
                    break;
                }
            }
            break;
    }
    return true;
}

void Modal::draw(DrawContext *ctx) {
    if (this->color_id == -1) {
        this->color_id = ctx->registerColorPair(*new ColorPair(COLOR_BLACK, COLOR_WHITE));
    }

    int width = this->width();
    int height = this->height();

    ctx->drawBackground(this->color_id, this->x, this->y, width, height);
    ctx->drawBox(this->color_id, this->x, this->y, width, height);
    ctx->coloredWriteAt(this->color_id, this->message, this->x + 1, this->y + 1);
    ctx->coloredWriteAt(this->confirm_focused ? this->color_id : 0, "Cancel", this->x + 1, this->y + 3);
    ctx->coloredWriteAt(this->confirm_focused ? 0 : this->color_id, "Ok", this->x + width - 3, this->y + 3);
}
