#include "Scrollable.h"

#include "../context/RunContext.h"

// post originale: https://forum.gamemaker.io/index.php?threads/variable-jump-animation-speed-based-on-running-speed-with-lerp.12633/post-83164
float relerp(float oldmin, float oldmax, float value, float newmin, float newmax) {
    return (value - oldmin) / (oldmax - oldmin) * (newmax - newmin) + newmin;
}

Scrollable::Scrollable(int spacing, int viewportHeight, int viewportWidth) {
    this->spacing = spacing;
    this->viewportHeight = viewportHeight;
    this->viewportWidth = viewportWidth;
    this->size = 0;
    this->scrollHeight = 0;
    this->maxHeight = 0;
    this->scrollColorId = -1;
}

void Scrollable::add(Drawable *drawable) {
    // inizializza un elemento della lista
    const auto l = new list{drawable, nullptr, nullptr};

    // se la lista e' vuota
    if (this->h_drawables == nullptr) {
        // aggiungi l'elemento come unico elemento della lista (quindi sta sia in testa che in coda)
        this->h_drawables = l;
        this->t_drawables = l;

        // aumenta l'altezza massima aggiungendo l'altezza del drawable
        this->maxHeight += drawable->height();
    }
    // altrimenti
    else {
        // assegna l'elemento come elemento successivo alla coda
        this->t_drawables->next = l;

        // assegna come elemento precedente di quello che si sta aggiungendo la coda
        l->prev = this->t_drawables;

        // assegna come coda della lista l'elemento
        this->t_drawables = l;

        // aumenta l'altezza massima aggiungendo lo spacing e l'altezza del drawable
        this->maxHeight += this->spacing + drawable->height();
    }

    // incrementa il numero di elementi presenti nella lista
    this->size++;
}

void Scrollable::scrollBy(int rows) {
    this->scrollHeight += rows;

    // scrollHeight massimo
    if (this->scrollHeight + this->viewportHeight - 1 >= this->maxHeight)
        this->scrollHeight = this->maxHeight - this->viewportHeight + 1;

    // scrollHeight minimo
    if (this->scrollHeight < 0) this->scrollHeight = 0;
}

int Scrollable::height() {
    return this->viewportHeight;
}

int Scrollable::width() {
    return this->viewportWidth;
}

void Scrollable::draw(DrawContext *ctx) {
    if (this->scrollColorId == -1) {
        this->scrollColorId = ctx->registerColorPair(ColorPair(COLOR_BLACK, COLOR_WHITE));
    }

    // partendo dalla testa
    auto l = this->h_drawables;
    // impostiamo l'altezza attuale a 0
    int currentHeight = 0;

    // finche' ci stanno elementi da controllare
    while (l != nullptr) {
        // controlliamo se l'altezza attuale rientra nella viewport da renderizzare
        if (currentHeight < scrollHeight || currentHeight + l->drawable->height() >= scrollHeight + viewportHeight) {
            // se non lo e', passiamo direttamente al prossimo elemento aggiornando l'altezza attuale
            currentHeight += l->drawable->height() + this->spacing;
            l = l->next;
            continue;
        }

        // calcoliamo la posizione dell'elemento
        int x = this->x;
        int y = this->y + currentHeight - this->scrollHeight;

        // impostiamo la posizione all'elemento
        l->drawable->setPosition(x, y);

        // diamo il comando draw all'elemento
        l->drawable->draw(ctx);

        // ricalcoliamo la nuova altezza attuale
        currentHeight += l->drawable->height() + this->spacing;

        // finalmente, possiamo passare al nuovo elemento
        l = l->next;
    }

    float viewport_proportions = static_cast<float>(this->viewportHeight) / static_cast<float>(this->maxHeight);

    if (viewport_proportions >= 1.0) return;

    /* calcola l'altezza della scrollbar e il suo inizio
     *
     * post originale: https://forum.gamemaker.io/index.php?threads/scrollbar-code-how-do-i-calculate-y-and-height.57928/post-350442
     */
    float y_1 = relerp(0.0f, (float) this->maxHeight, (float) this->scrollHeight, (float) this->y,
                       (float) this->y + (float) this->viewportHeight);
    float y_2 = relerp(0.0f, (float) this->maxHeight, (float) this->scrollHeight + (float) this->viewportHeight,
                       (float) this->y, (float) this->y + (float) this->viewportHeight);

    int height = (int) (y_2 - y_1);

    ctx->drawBackground(this->scrollColorId, this->x + this->viewportWidth - 2, (int) y_1, 1, height);
}

bool Scrollable::action(RunContext *ctx) {
    switch (ctx->getInput()) {
        case SCROLL_UP:
        case UP:
            this->scrollBy(-1);
            return true;
        case SCROLL_DOWN:
        case DOWN:
            this->scrollBy(1);
            return true;
        default: return false;
    }
}
