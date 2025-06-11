#include "DrawContext.h"

DrawContext::DrawContext() {
    // inizializziamo con valori di default il DrawContext
    this->win = nullptr;
    this->title = "";
    this->colors = new ColorPair[MAX_COLORS]{DEFAULT_COLOR_PAIR};
    this->registeredColors = 0;

    // e registriamo un colore di default come primo colore
    this->registerColorPair(DEFAULT_COLOR_PAIR);
}

DrawContext::~DrawContext() = default;

void DrawContext::setWindow(WINDOW *win) {
    this->win = win;
}

WINDOW *DrawContext::getWindow() const {
    return this->win;
}

void DrawContext::prepare(const bool redraw) const {
    // se viene forzato il redraw dell'intera finestra
    if (redraw) {
        // allora facciamo il clean
        clear();
    } else {
        // altrimenti solo il werase
        werase(this->win);
    }

    // riprepariamo la box della finestra
    box(this->win, 0, 0);
    // e disegniamo pure il titolo
    mvwprintw(this->win, 0, 2, this->title);
}

void DrawContext::refresh() const {
    wrefresh(this->win);
}

void DrawContext::setTitle(const char *title) {
    this->title = title;
}

int DrawContext::registerColorPair(const ColorPair colorPair) {
    // se il colore richiesto e' quello di default
    if (colorPair == DEFAULT_COLOR_PAIR) {
        // ritorniamo immediatamente 0
        return 0;
    }

    // controlliamo se il colore richiesto e' gia' stato registrato
    for (int i = 0; i < this->registeredColors; i++) {
        if (this->colors[i] == colorPair) {
            // in caso affermativo, ritorniamo l'indice del colore + 1
            // (l'indice 0 e' occupato dal colore di default)
            return i + 1;
        }
    }

    // se non abbiamo trovato il colore tra quelli registrati, controlliamo se possiamo registrarne di altri
    if (this->registeredColors >= MAX_COLORS) {
        printw("REACHED MAXIMUM REGISTERED COLORS");
        refresh();
        exit_curses(1);
    }

    // se possiamo, salviamo il colore in memoria
    this->colors[this->registeredColors] = colorPair;
    this->registeredColors += 1;
    // e registriamolo
    init_pair(this->registeredColors, colorPair.foreground, colorPair.background);

    // alla fine, ritorniamo l'id del colore
    return this->registeredColors;
}

void DrawContext::enableColor(const int color) const {
    wattron(this->win, COLOR_PAIR(color));
}

void DrawContext::disableColor(const int color) const {
    wattroff(this->win, COLOR_PAIR(color));
}

void DrawContext::write(const char *txt) const {
    wprintw(win, txt);
}

void DrawContext::writeAt(const char *txt, const int x, const int y) const {
    mvwprintw(win, y, x, txt);
}

void DrawContext::coloredWriteAt(int color, const char *txt, int x, int y) {
    this->enableColor(color);

    this->writeAt(txt, x, y);

    this->disableColor(color);
}

void DrawContext::drawBackground(int color, int x, int y, int width, int height) {
    this->enableColor(color);

    // per ogni pixel del rettangolo del background
    for (int currentX = x; currentX < width + x; currentX++) {
        for (int currentY = y; currentY < height + y; currentY++) {
            // scrive un carattere vuoto con il colore richiesto
            this->writeAt(" ", currentX, currentY);
        }
    }

    this->disableColor(color);
}

void DrawContext::drawBox(int color, int x, int y, int width, int height) {
    this->enableColor(color);

    // le due linee orizzontali (sopra, sotto)
    mvwhline(this->win, y, x, 0, width);
    mvwhline(this->win, y + height - 1, x, 0, width);

    // le due linee verticali (sinistra, destra)
    mvwvline(this->win, y, x, 0, height);
    mvwvline(this->win, y, x+width - 1, 0, height);

    // infine, i quattro angoli (U = sopra, L = sotto; L = sinistra, R = destra)
    mvwaddch(this->win, y, x, ACS_ULCORNER);
    mvwaddch(this->win, y, x+width-1, ACS_URCORNER);
    mvwaddch(this->win, y+height-1, x, ACS_LLCORNER);
    mvwaddch(this->win, y+height-1, x+width-1, ACS_LRCORNER);

    this->disableColor(color);
}
