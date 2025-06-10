#include "MainScene.h"

#include "GameScene.h"
#include "LeaderboardScene.h"
#include "LevelSelectionScene.h"

LeaderboardScene leaderboard_scene;
LevelSelectionScene *level_selection;

void onExit(RunContext *ctx) {
    // avvisa l'engine di uscire dal gioco
    ctx->queueExit();
}

void onLeaderboard(RunContext *ctx) {
    // inizializza una nuova LeaderboardScene
    leaderboard_scene = *new LeaderboardScene();
    // e chiede all'engine di passare a quella scena
    ctx->queueScene(&leaderboard_scene);
}

void onGame(RunContext *ctx) {
    // inizializza una nuova LevelSelectionScene
    level_selection = new LevelSelectionScene();
    // e chiede all'engine di passare a quella scena
    ctx->queueScene(level_selection);
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
    this->newGameBtn.setOnClick(onGame);
    this->leaderboardBtn.setOnClick(onLeaderboard);
    this->exitBtn.setOnClick(onExit);
}

const char *MainScene::getTitle() {
    // titolo della scena
    return "Snake";
}
