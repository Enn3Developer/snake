#include "GameScene.h"

#include "MainScene.h"
#include "../../engine/components/Label.h"

MainScene main_menu_scene;

GameScene::GameScene(): modal("Do you want to quit the game?") {
    this->pointsStr = new char[50];
    this->points = 0;

    this->snake = new Snake(6, 8);
    this->snake->setPosition(1, 1);

    this->modal.setVisible(false);
    this->modal.setPosition(getCenteredX(&modal), 12);

    this->alert = new Alert();
    this->alert->setVisible(false);

    this->pointsLabel = new Label;
    this->pointsLabel->setText(this->pointsStr);
    this->pointsLabel->setColor(*new ColorPair(COLOR_CYAN, COLOR_BLACK));
    this->pointsLabel->setPosition(60, 0);

    sprintf(this->pointsStr, "Points: 0");

    this->add(this->snake);
    this->add(&this->modal);
    this->add(this->alert);
    this->add(this->pointsLabel);

    this->moveFocus(0);
}

const char *GameScene::getTitle() {
    return "Snake";
}

void GameScene::run(RunContext *ctx) {
    // esegue la logica base della scena
    Scene::run(ctx);

    // ottiene il puntatore al modal della scena e lo casta a Modal
    Drawable *modal_drawable = this->get(1);
    auto *modal = dynamic_cast<Modal *>(modal_drawable);

    // se e' ancora aperto il modal, non fare nulla
    if (modal->isOpen()) return;

    // se l'alert e' ancora aperto, non fare nulla
    if (this->alert->isOpen()) return;
    // altrimenti, se e' stato chiuso ma e' ancora visibile
    if (this->alert->isVisible()) {
        // allora ritorna al menu principale
        main_menu_scene = *new MainScene();
        ctx->queueScene(&main_menu_scene);
    }

    int points = this->snake->tick();

    if (points == -1) {
        this->alert->setMsg("You lost");
        this->alert->setVisible(true);
        this->alert->openAlert();
        this->alert->setPosition(getCenteredX(this->alert), 12);
        this->moveFocus(2);
    } else {
        this->points += points;
        sprintf(this->pointsStr, "Points: %d", this->points);
    }

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
    this->moveFocus(0);
}

bool GameScene::onEscape(RunContext *ctx) {
    // ottiene il puntatore al modal della scena e lo casta a Modal
    Drawable *modal_drawable = this->get(1);
    auto *modal = dynamic_cast<Modal *>(modal_drawable);

    // se il modal non e' ancora stato aperto
    if (!modal->isOpen()) {
        // allora rendilo visibile
        modal->setVisible(true);
        // avvisa il modal che e' stato aperto
        modal->openModal();
        // e sposta il focus li'
        this->moveFocus(1);
    }

    // infine, annulla l'uscita dal gioco
    return true;
}
