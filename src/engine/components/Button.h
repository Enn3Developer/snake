#ifndef BUTTON_H
#define BUTTON_H
#include "../Actionable.h"
#include "../Drawable.h"

class Button final : public Drawable, public Actionable
{
private:
    /// ID del colore da usare quando è in focus
    int hoverColor;
    /// Testo del bottone
    const char* txt;
    /// Funzione da eseguire quando viene premuto
    void (*click)(RunContext* ctx);

public:
    Button();
    ~Button() override;
    void setText(const char* txt);
    void setOnClick(void (*click)(RunContext* ctx));
    /// Registra la prima volta il colore di quando è in focus, dopodichè in base a se in focus o meno lo abilita
    void draw(DrawContext* ctx) override;
    /// Rimanda l'azione alla funzione da eseguire
    void action(RunContext* ctx) override;
    int width() override;
};

#endif
