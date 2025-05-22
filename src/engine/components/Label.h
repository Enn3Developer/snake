#ifndef LABEL_H
#define LABEL_H
#include "../Drawable.h"

class Label final : public Drawable
{
private:
    /// ID del colore in uso
    int color;
    /// Colore
    ColorPair colorPair;
    /// Testo
    const char* txt;

public:
    Label();
    ~Label() override;
    void setText(const char* txt);
    void setColor(ColorPair color);
    /// Se il colore non viene ancora registrato lo registra, usa quel colore per scrivere nella finestra il testo
    void draw(DrawContext* ctx) override;
    int width() override;
};

#endif
