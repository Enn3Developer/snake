#include "GameScene.h"

#include <cstdlib>
#include <ctime>

#include "MainScene.h"
#include "../../engine/Engine.h"
#include "../../engine/components/Label.h"

MainScene main_menu_scene;

GameScene::GameScene() {
    srand(time(nullptr));
    this->pointsStr = new char[50];
    this->points = 0;
    this->bonusPoints = 1;

    this->timerStr = new char[50];
    this->timer = ONE_MINUTE;

    this->snake = new Snake(6, 8);
    this->snake->setPosition(1, 1);

    this->modal = new Modal("Do you want to quit the game?");
    this->modal->setVisible(false);
    this->modal->setPosition(getCenteredX(this->modal), 12);

    this->alert = new Alert();
    this->alert->setVisible(false);

    this->pointsLabel = new Label;
    this->pointsLabel->setText(this->pointsStr);
    this->pointsLabel->setColor(*new ColorPair(COLOR_CYAN, COLOR_BLACK));
    this->pointsLabel->setPosition(60, 0);

    this->timerLabel = new Label;
    this->timerLabel->setText(this->timerStr);
    this->timerLabel->setColor(*new ColorPair(COLOR_YELLOW, COLOR_BLACK));
    this->timerLabel->setPosition(48, 0);

    sprintf(this->pointsStr, "Points: 0");
    sprintf(this->timerStr, "Time: %d", this->timer / 1000);

    this->add(this->snake);
    this->add(this->modal);
    this->add(this->alert);
    this->add(this->pointsLabel);
    this->add(this->timerLabel);

    this->moveFocus(0);
}

void GameScene::setBonusPoints(int bonusPoints) {
    this->bonusPoints = bonusPoints;
}

const char *GameScene::getTitle() {
    return "Snake";
}

void GameScene::run(RunContext *ctx) {
    // esegue la logica base della scena
    Scene::run(ctx);

    // se e' ancora aperto il modal, non fare nulla
    if (this->modal->isOpen()) return;

    // se l'alert e' ancora aperto, non fare nulla
    if (this->alert->isOpen()) return;
    // altrimenti, se e' stato chiuso ma e' ancora visibile
    if (this->alert->isVisible()) {
        // allora ritorna al menu principale
        main_menu_scene = *new MainScene();
        ctx->queueScene(&main_menu_scene);
    }

    int points = this->snake->tick();
    this->timer -= MILLIS_PER_FRAME;

    if (this->timer <= 0) {
        this->alert->setMsg("You won");
        this->alert->setVisible(true);
        this->alert->openAlert();
        this->alert->setPosition(getCenteredX(this->alert), 12);
        this->moveFocus(2);
    }

    sprintf(this->timerStr, "Time: %d", this->timer / 1000);

    if (points == -1) {
        this->alert->setMsg("You lost");
        this->alert->setVisible(true);
        this->alert->openAlert();
        this->alert->setPosition(getCenteredX(this->alert), 12);
        this->moveFocus(2);
    } else {
        this->points += points * this->bonusPoints;
        sprintf(this->pointsStr, "Points: %d", this->points);
    }

    // se il modal non e' visibile, non fare nulla
    if (!this->modal->isVisible()) return;

    // altrimenti (se deve essere chiuso perche' l'utente ha compiuto un'azione) allora rendilo invisibile
    this->modal->setVisible(false);
    // e, se l'utente ha confermato l'azione
    if (this->modal->isConfirmed()) {
        // allora ritorna al menu principale
        main_menu_scene = *new MainScene();
        ctx->queueScene(&main_menu_scene);
    }
    this->moveFocus(0);
}

bool GameScene::onEscape(RunContext *ctx) {
    // se il modal non e' ancora stato aperto
    if (!this->modal->isOpen()) {
        // allora rendilo visibile
        this->modal->setVisible(true);
        // avvisa il modal che e' stato aperto
        this->modal->openModal();
        // e sposta il focus li'
        this->moveFocus(1);
    }

    // infine, annulla l'uscita dal gioco
    return true;
}
