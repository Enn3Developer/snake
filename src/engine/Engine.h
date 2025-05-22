#ifndef ENGINE_H
#define ENGINE_H
#include "Scene.h"

#define MILLIS_PER_FRAME 30

class Engine
{
private:
    /// Contesto grafico
    DrawContext drawContext;
    /// Scena attuale
    Scene* scene;
    int startX, startY;

public:
    /// Prepara ncurses e crea la finestra principale
    Engine(int height, int width, int startX, int startY);
    /// Punto d'avvio del gioco
    void start(Scene* scene);
    /// Inizializza una scena
    void initScene(Scene* scene);
    /// Legge l'input dall'utente e lo salva nel `RunContext`
    static void input(RunContext* ctx);
    /// Eseguita in loop costante, richiama `input` e `draw` oltre a gestire il `RunContext`
    void run();
    /// Prepara e chiama la funzione `draw` della scena attualmente in uso
    void draw(bool redraw);
    /// Cambia il titolo della finestra
    void setTitle(const char* title);
    /// Ferma il processo attuale per il numero di millisecondi specificati
    static void sleep(unsigned int millis);
    /// Ritorna il tempo attuale in millisecondi
    static int64_t millis();
    ~Engine();
};

#endif
