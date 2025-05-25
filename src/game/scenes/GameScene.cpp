#include "GameScene.h"

#include "MainScene.h"

MainScene main_menu_scene;

GameScene::GameScene(): modal("Do you want to quit the game?") {
    this->snake = new Snake(3, 4);

    this->modal.setVisible(false);
    this->modal.setPosition(getCenteredX(&modal), 12);

    this->add(&this->modal);
    this->add(this->snake);

    this->moveFocus(1);
}

const char *GameScene::getTitle() {
    return "Snake";
}

void GameScene::run(RunContext *ctx) {
    // esegue la logica base della scena
    Scene::run(ctx);

    this->snake->tick();

    // ottiene il puntatore al modal della scena e lo casta a Modal
    Drawable *modal_drawable = this->get(0);
    auto *modal = dynamic_cast<Modal *>(modal_drawable);

    // se e' ancora aperto il modal, non fare nulla
    if (modal->isOpen()) return;

    // se il modal non e' visibile, non fare nulla
    if (!modal->isVisible()) return;

    // altrimenti (se deve essere chiuso perche' l'utente ha compiuto un'azione) allora rendilo invisibile
    modal->setVisible(false);
    // e, se l'utente ha confermato l'azione
    if (modal->isConfirmed()) {
        // allora ritorna al menu principale
        main_menu_scene = *new MainScene();
        ctx->queueScene(&main_menu_scene);
    }
}

bool GameScene::onEscape(RunContext *ctx) {
    // ottiene il puntatore al modal della scena e lo casta a Modal
    Drawable *modal_drawable = this->get(0);
    auto *modal = dynamic_cast<Modal *>(modal_drawable);

    // se il modal non e' ancora stato aperto
    if (!modal->isOpen()) {
        // allora rendilo visibile
        modal->setVisible(true);
        // avvisa il modal che e' stato aperto
        modal->openModal();
        // e sposta il focus li'
        this->moveFocus(0);
    }

    // infine, annulla l'uscita dal gioco
    return true;
}
