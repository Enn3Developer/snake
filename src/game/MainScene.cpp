#include "MainScene.h"

void onExit(RunContext *ctx) {
    // avvisa l'engine di uscire dal gioco
    ctx->queueExit();
}

MainScene::MainScene() {
    // inizializzazione degli elementi grafici
    this->newGameBtn = *new Button();
    this->leaderboardBtn = *new Button();
    this->exitBtn = *new Button();

    // aggiunta degli elementi grafici nella scena
    this->add(&this->newGameBtn);
    this->add(&this->leaderboardBtn);
    this->add(&this->exitBtn);

    // impostazione del testo
    this->newGameBtn.setText("New Game");
    this->leaderboardBtn.setText("Leaderboard");
    this->exitBtn.setText("Exit");

    // impostazione della posizione nella scena
    this->newGameBtn.setPosition(getCenteredX(&this->newGameBtn), 8);
    this->leaderboardBtn.setPosition(getCenteredX(&this->leaderboardBtn), 11);
    this->exitBtn.setPosition(getCenteredX(&this->exitBtn), 14);

    // impostazione delle azioni dei pulsanti
    this->exitBtn.setOnClick(onExit);
}

const char *MainScene::getTitle() {
    // titolo della scena
    return "Snake";
}

