#include "Scrollable.h"

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
