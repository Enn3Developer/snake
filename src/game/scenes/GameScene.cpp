#include "GameScene.h"

#include "MainScene.h"

MainScene main_menu_scene;

GameScene::GameScene(): modal("Do you want to quit the game?") {
    this->modal.setVisible(false);
    this->modal.setPosition(getCenteredX(&modal), 12);

    this->add(&this->modal);
}

const char *GameScene::getTitle() {
    return "Snake";
}

void GameScene::run(RunContext *ctx) {
    Scene::run(ctx);

    Drawable *modal_drawable = this->get(0);
    auto *modal = dynamic_cast<Modal *>(modal_drawable);

    if (modal->isOpen()) return;


    if (!modal->isVisible()) return;

    modal->setVisible(false);
    if (modal->isConfirmed()) {
        main_menu_scene = *new MainScene();
        ctx->queueScene(&main_menu_scene);
    }
}

bool GameScene::onEscape(RunContext *ctx) {
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

    return true;
}
