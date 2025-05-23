#include "Button.h"
#include <cstring>

#include "../context/RunContext.h"

Button::Button() {
    this->hoverColor = -1;
    this->txt = "";
    this->click = nullptr;
}

Button::~Button() = default;

void Button::setText(const char *txt) {
    this->txt = txt;
}

void Button::setOnClick(void (*click)(RunContext *ctx)) {
    this->click = click;
}


void Button::draw(DrawContext *ctx) {
    if (this->hoverColor == -1) {
        this->hoverColor = ctx->registerColorPair(ColorPair(COLOR_BLACK, COLOR_WHITE));
    }
    if (this->hover) {
        ctx->enableColor(this->hoverColor);
    }
    ctx->writeAt(this->txt, this->x, this->y);
    if (this->hover) {
        ctx->disableColor(this->hoverColor);
    }
}

bool Button::action(RunContext *ctx) {
    if (ctx->getInput() == CLICKED || ctx->getInput() == CONFIRM) {
        if (this->click != nullptr) {
            this->click(ctx);
            return true;
        }
    }

    return false;
}

int Button::width() {
    return strlen(this->txt);
}
