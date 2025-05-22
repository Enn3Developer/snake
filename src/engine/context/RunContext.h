#ifndef RUNCONTEXT_H
#define RUNCONTEXT_H

class Scene;

typedef enum input_kind {
    NONE,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    CONFIRM,
    ESCAPE,
    CLICKED,
} InputKind;

class RunContext {
protected:
    /// L'input attuale da tastiera
    InputKind input;
    /// Posizione del mouse al momento del click
    int x, y;
    /// Puntatore ad un'eventuale richiesta di cambiamento di scena
    Scene *switchScene;
    /// Richiesta di chiusura da parte dell'engine
    bool exit;
    /// Forza l'engine a usare il `clear()` anziché di `werase(WINDOW*)`
    bool redraw;

public:
    RunContext();

    ~RunContext();

    /// Usato dall'engine per impostare l'input attuale
    void setInput(InputKind input);

    /// Usato dall'engine per impostare la posizione del mouse al momento del click
    void setMousePosition(int x, int y);

    [[nodiscard]] InputKind getInput() const;

    /// Ritorna x e y del mouse al momento del click
    [[nodiscard]] int *getMousePosition() const;

    /// Avvisa l'Engine di preparare una nuova scena e sostituirla con quella attuale
    void queueScene(Scene *scene);

    /// Avvisa l'engine di prepararsi per uscire dal gioco
    void queueExit();

    /// Avvisa l'engine di forzare un draw di tutto lo schermo anziche' della scena
    void forceRedraw();

    /// Usato dall'engine per controllare l'eventuale presenza di cambio di scena
    [[nodiscard]] bool sceneQueued() const;

    /// Usato dall'engine per controllare se è stata richiesta la chiusura dell'applicazione
    [[nodiscard]] bool exitQueued() const;

    /// Usato dall'engine per controllare se deve forzare il `clear()`
    bool redrawForced() const;

    /// Puntatore alla nuova scena da usare
    [[nodiscard]] Scene *newScene() const;
};

#endif
