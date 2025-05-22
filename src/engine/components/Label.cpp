#include "Label.h"

#include <cstring>

Label::Label()
{
    this->color = 0;
    this->colorPair = DEFAULT_COLOR_PAIR;
    this->txt = "";
}

Label::~Label() = default;

void Label::setText(const char* txt)
{
    this->txt = txt;
}


void Label::setColor(const ColorPair color)
{
    this->colorPair = color;
    this->color = -1;
}

void Label::draw(DrawContext* ctx)
{
    if (this->color == -1)
    {
        this->color = ctx->registerColorPair(this->colorPair);
    }
    ctx->enableColor(this->color);
    ctx->writeAt(this->txt, this->x, this->y);
    ctx->disableColor(this->color);
}

int Label::width()
{
    return strlen(this->txt);
}
