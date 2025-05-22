#ifndef SCENE_H
#define SCENE_H
#include "Drawable.h"
#include "context/DrawContext.h"
#include "context/InitContext.h"
#include "context/RunContext.h"

class Scene {
protected:
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
    /// `Drawable` attualmente in focus
    p_list focus;
    /// Posizione della finestra rispetto al terminale
    int startX, startY;

public:
    Scene();

    /// Registra un oggetto `Drawable`
    void add(Drawable *drawable);

    [[nodiscard]] Drawable *get(int idx) const;

    /// Sposta il focus verso la testa della lista
    void focusUp();

    /// Sposta il focus verso la coda della lista
    void focusDown();

    /// Usato quando si riceve un click del mouse
    void click(RunContext *ctx, int x, int y);

    /// Usato per centrare il testo
    static int getCenteredX(Drawable *drawable);

    /// Chiamata una sola volta quando la scena diventa la scena attuale nell'engine
    virtual void init(InitContext &ctx);

    /// Chiamata a ogni frame per eseguire la logica della scena
    virtual void run(RunContext *ctx);

    /// Chiamata a ogni frame per disegnare la scena
    virtual void draw(DrawContext *ctx);

    /// Chiamato la prima volta dall'engine quando istanzia una nuova scena
    virtual const char *getTitle();

    virtual ~Scene();
};

#endif
