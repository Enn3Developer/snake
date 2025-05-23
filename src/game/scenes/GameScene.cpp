#include "GameScene.h"

GameScene::GameScene(): modal("Do you want to quit the game?", &this->modal_open, &this->modal_confirm) {
    this->modal.setVisible(false);

    this->add(&this->modal);
}

const char *GameScene::getTitle() {
    return "Snake";
}

bool GameScene::onEscape(RunContext *ctx) {
    // se il modal non e' ancora stato aperto
    if (!this->modal_open) {
        // allora rendilo visibile
        this->modal.setVisible(true);
        // e sposta il focus li'
        this->moveFocus(0);
    }

    return true;
}
