#include "Button.h"
#include <cstring>

#include "../context/RunContext.h"

Button::Button() {
    this->hoverColor = -1;
    this->normalColor = 0;
    this->txt = "";
    this->click = nullptr;

    this->normalColorPair = DEFAULT_COLOR_PAIR;
    this->hoverColorPair = ColorPair(COLOR_BLACK, COLOR_WHITE);
}

Button::~Button() = default;

void Button::setText(const char *txt) {
    this->txt = txt;
}

void Button::setNormalColor(ColorPair color) {
    this->normalColorPair = color;
    this->normalColor = -1;
}

void Button::setHoverColor(ColorPair color) {
    this->hoverColorPair = color;
    this->hoverColor = -1;
}

void Button::setOnClick(void (*click)(RunContext *ctx)) {
    this->click = click;
}

void Button::draw(DrawContext *ctx) {
    if (this->hoverColor == -1) {
        this->hoverColor = ctx->registerColorPair(this->hoverColorPair);
    }

    if (this->normalColor == -1) {
        this->normalColor = ctx->registerColorPair(this->normalColorPair);
    }

    if (this->hover) {
        ctx->enableColor(this->hoverColor);
    } else {
        ctx->enableColor(this->normalColor);
    }

    ctx->writeAt(this->txt, this->x, this->y);

    if (this->hover) {
        ctx->disableColor(this->hoverColor);
    } else {
        ctx->disableColor(this->normalColor);
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
