#include "Label.h"

#include <cstring>

Label::Label() {
    this->color = 0;
    this->colorPair = DEFAULT_COLOR_PAIR;
    this->txt = "";
}

Label::~Label() = default;

void Label::setText(const char *txt) {
    this->txt = txt;
}

void Label::setColor(const ColorPair color) {
    this->colorPair = color;
    this->color = -1;
}

void Label::draw(DrawContext *ctx) {
    // se il colore non e' stato ancora registrato
    if (this->color == -1) {
        // registra il colore e salva l'id corrispondente
        this->color = ctx->registerColorPair(this->colorPair);
    }

    // abilita il colore
    ctx->enableColor(this->color);
    // scrve il testo
    ctx->writeAt(this->txt, this->x, this->y);
    // infine disabilita il colore
    ctx->disableColor(this->color);
}

int Label::width() {
    return strlen(this->txt);
}
