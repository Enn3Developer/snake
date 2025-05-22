#include "Drawable.h"

Drawable::Drawable() {
    this->visible = true;
    this->hover = false;
    this->x = this->y = 0;
}

bool Drawable::isVisible() const {
    return this->visible;
}

void Drawable::setVisible(const bool visible) {
    this->visible = visible;
}

void Drawable::setHover(const bool hover) {
    this->hover = hover;
}

void Drawable::setPosition(const int x, const int y) {
    this->x = x;
    this->y = y;
}

int *Drawable::getPosition() const {
    return new int[]{this->x, this->y};
}

Drawable::~Drawable() = default;

void Drawable::draw(DrawContext *ctx) {
}

int Drawable::height() {
    return 1;
}

int Drawable::width() {
    return 1;
}

