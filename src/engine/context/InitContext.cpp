#include "InitContext.h"

InitContext::InitContext() {
    this->startX = 0, this->startY = 0;
}

InitContext::~InitContext() = default;

void InitContext::setStart(const int x, const int y) {
    this->startX = x, this->startY = y;
}

int InitContext::getStartX() const {
    return this->startX;
}

int InitContext::getStartY() const {
    return this->startY;
}
