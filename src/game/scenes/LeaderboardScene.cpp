#include "LeaderboardScene.h"

#include "MainScene.h"

MainScene main_scene;

void onMenu(RunContext *ctx) {
    // inizializza una nuova MainScene
    main_scene = *new MainScene();
    // e chiede all'engine di passare a quella scena
    ctx->queueScene(&main_scene);
}

// inizializza la scrollbar; per qualche motivo al compilatore non gli piace che la inizializzo dentro al costruttore
LeaderboardScene::LeaderboardScene(): scrollable(1, 27, 79) {
    // inizializzazione dei drawable
    this->testLabel = *new Label();
    this->testLabel.setText("Test");

    this->menuBtn = *new Button();
    this->menuBtn.setText("Main menu");
    this->menuBtn.setPosition(70, 28);
    this->menuBtn.setOnClick(onMenu);

    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);

    this->scrollable.setPosition(1, 1);

    this->add(&this->scrollable);
    this->add(&this->menuBtn);
}


const char *LeaderboardScene::getTitle() {
    return "Leaderboard";
}

bool LeaderboardScene::onEscape(RunContext *ctx) {
    onMenu(ctx);
    return true;
}
