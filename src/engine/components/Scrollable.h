#ifndef SCROLLABLE_H
#define SCROLLABLE_H
#include "../Actionable.h"
#include "../Drawable.h"

#define MIN_SCROLLBAR_HEIGHT 5

class Scrollable final : public Drawable, public Actionable {
private:
    /// Lista per gestire tutti gli oggetti `Drawable`, non è circolare
    struct list {
        Drawable *drawable;
        list *next;
        list *prev;
    };

    typedef list *p_list;
    /// Testa della lista
    p_list h_drawables;
    /// Coda della lista
    p_list t_drawables;
    /// Numero di elementi nella lista
    int size;

    /// Spazio verticale tra un elemento e un altro
    int spacing;

    /// Altezza totale di tutti gli elementi + lo spacing
    int maxHeight;

    /// Altezza attuale nella scrollbar (ovvero a che altezza si trova la prima riga)
    int scrollHeight;

    /// Altezza massima renderizzabile
    int viewportHeight;

    /// Larghezza massima renderizzabile
    int viewportWidth;

    int scrollColorId;

public:
    Scrollable(int spacing, int viewportHeight, int viewportWidth);

    void add(Drawable *drawable);

    void scrollBy(int rows);

    int height() override;

    int width() override;

    void draw(DrawContext *ctx) override;

    bool action(RunContext *ctx) override;
};

#endif
