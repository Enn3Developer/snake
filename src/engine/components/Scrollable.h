#ifndef SCROLLABLE_H
#define SCROLLABLE_H
#include "../Drawable.h"

class Scrollable final : public Drawable {
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
};

#endif
