#include "LevelSelectionScene.h"

#include "GameScene.h"
#include "MainScene.h"

MainScene *main_scene_from_level_selection;
GameScene *game_scene_from_level_selection;

void startGame(RunContext *ctx, int level) {
    // calcoliamo i parametri della partita in base al livello selezionato
    int speed = 2;
    int length = 2;
    int bonus = 1;

    switch (level) {
        case 1:
            speed = 20;
            length = 6;
            bonus = 3;
            break;
        case 2:
            speed = 15;
            length = 10;
            bonus = 7;
            break;
        case 3:
            speed = 10;
            length = 15;
            bonus = 11;
            break;
        default: break;
    }

    // ora creiamo la partita assegnando i parametri calcolati
    game_scene_from_level_selection = new GameScene(length, speed, level);
    game_scene_from_level_selection->setBonusPoints(bonus);

    // infine passiamo alla scena della partita
    ctx->queueScene(game_scene_from_level_selection);
}

void onEasy(RunContext *ctx) {
    startGame(ctx, 1);
}

void onNormal(RunContext *ctx) {
    startGame(ctx, 2);
}

void onHard(RunContext *ctx) {
    startGame(ctx, 3);
}

LevelSelectionScene::LevelSelectionScene() {
    // inizializzazione dei pulsanti con annessi dati (testo, colore, posizione e azione al click)
    this->easy = new Button();
    this->normal = new Button();
    this->hard = new Button();

    this->easy->setText("Easy");
    this->normal->setText("Normal");
    this->hard->setText("Hard");

    this->easy->setNormalColor(ColorPair(COLOR_GREEN, COLOR_BLACK));
    this->easy->setHoverColor(ColorPair(COLOR_GREEN, COLOR_WHITE));

    this->normal->setNormalColor(ColorPair(COLOR_YELLOW, COLOR_BLACK));
    this->normal->setHoverColor(ColorPair(COLOR_YELLOW, COLOR_WHITE));

    this->hard->setNormalColor(ColorPair(COLOR_RED, COLOR_BLACK));
    this->hard->setHoverColor(ColorPair(COLOR_RED, COLOR_WHITE));

    this->easy->setPosition(getCenteredX(this->easy), 8);
    this->normal->setPosition(getCenteredX(this->normal), 11);
    this->hard->setPosition(getCenteredX(this->hard), 14);

    this->easy->setOnClick(onEasy);
    this->normal->setOnClick(onNormal);
    this->hard->setOnClick(onHard);

    this->add(this->easy);
    this->add(this->normal);
    this->add(this->hard);
}

void LevelSelectionScene::run(RunContext *ctx) {
    Scene::run(ctx);

    // se il focus non esiste, non proseguiamo
    if (this->focus == nullptr) return;

    // se il focus e' il pulsante easy allora coloriamo la box di verde
    if (this->focus->drawable == this->easy) {
        ctx->setBoxColor(ColorPair(COLOR_GREEN));
    }
    // se il focus e' il pulsante normal allora coloriamo la box di giallo
    else if (this->focus->drawable == this->normal) {
        ctx->setBoxColor(ColorPair(COLOR_YELLOW));
    }
    // se il focus e' il pulsante hard allora coloriamo la box di rosso
    else if (this->focus->drawable == this->hard) {
        ctx->setBoxColor(ColorPair(COLOR_RED));
    }
}

bool LevelSelectionScene::onEscape(RunContext *ctx) {
    // ritorna al menu principale
    main_scene_from_level_selection = new MainScene();
    ctx->queueScene(main_scene_from_level_selection);

    // annullando l'azione della chiusura dell'engine
    return true;
}

const char *LevelSelectionScene::getTitle() {
    return "Select Level";
}
