#include "engine/Engine.h"
#include "game/scenes/MainScene.h"

int main() {
    // inizializzazione iniziale del gioco
    const auto engine = new Engine(30, 80, 40, 2);
    const auto mainScene = new MainScene();

    // avvio del gioco
    engine->start(mainScene);

    // assicuriamo che le risorse vengano liberate per pulire il terminale e uscire dalla modalita' curses
    delete mainScene;
    delete engine;
    return 0;
}
