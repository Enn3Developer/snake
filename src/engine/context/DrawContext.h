#ifndef DRAWCONTEXT_H
#define DRAWCONTEXT_H
#include <ncurses.h>
#include "../ColorPair.h"

constexpr int MAX_COLORS = 32;
const auto DEFAULT_COLOR_PAIR = ColorPair(COLOR_WHITE);

class DrawContext
{
private:
    /// Finestra principale
    WINDOW* win;
    /// Titolo della finestra
    const char* title;
    /// Colori registrati
    ColorPair* colors;
    /// Numero di colori registrati
    short registeredColors;

public:
    DrawContext();
    ~DrawContext();
    /// Usato dall'engine durante l'inizializzazione
    void setWindow(WINDOW* win);
    [[nodiscard]] WINDOW* getWindow() const;
    /// Usato dall'engine alla fine della fase `draw`
    void refresh() const;
    /// Preparazione per la fase `draw`
    void prepare(bool redraw) const;
    /// Imposta il titolo della finestra, usato principalmente dall'engine
    void setTitle(const char* title);
    /// Registra un nuovo colore, ritorna l'id da usare per quel colore
    int registerColorPair(ColorPair colorPair);
    /// Abilita un certo colore
    void enableColor(int color) const;
    /// Disabilita un certo colore
    void disableColor(int color) const;
    /// Scrive del testo dentro alla finestra alla fine del cursore
    void write(const char* txt) const;
    /// Scrive del testo dentro alla finestra alla posizione richiesta
    void writeAt(const char* txt, int x, int y) const;
};

#endif
