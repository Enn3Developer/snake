#include "Button.h"
#include <cstring>

Button::Button()
{
    this->hoverColor = -1;
    this->txt = "";
    this->click = nullptr;
}

Button::~Button() = default;

void Button::setText(const char* txt)
{
    this->txt = txt;
}

void Button::setOnClick(void (*click)(RunContext* ctx))
{
    this->click = click;
}


void Button::draw(DrawContext* ctx)
{
    if (this->hoverColor == -1)
    {
        this->hoverColor = ctx->registerColorPair(ColorPair(COLOR_BLACK, COLOR_WHITE));
    }
    if (this->hover)
    {
        ctx->enableColor(this->hoverColor);
    }
    ctx->writeAt(this->txt, this->x, this->y);
    if (this->hover)
    {
        ctx->disableColor(this->hoverColor);
    }
}

void Button::action(RunContext* ctx)
{
    if (this->click != nullptr)
    {
        this->click(ctx);
    }
}

int Button::width()
{
    return strlen(this->txt);
}
