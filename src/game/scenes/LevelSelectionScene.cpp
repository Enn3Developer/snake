#include "LevelSelectionScene.h"

#include "GameScene.h"
#include "MainScene.h"

MainScene *main_scene_from_level_selection;
GameScene *game_scene_from_level_selection;

void startGame(RunContext *ctx, int level) {
    int speed = 2;
    int length = 2;
    int bonus = 1;

    switch (level) {
        case 1:
            speed = 7;
            length = 6;
            bonus = 1;
            break;
        case 2:
            speed = 5;
            length = 10;
            bonus = 3;
            break;
        case 3:
            speed = 3;
            length = 15;
            bonus = 7;
            break;
        default: break;
    }

    game_scene_from_level_selection = new GameScene(length, speed, level);
    game_scene_from_level_selection->setBonusPoints(bonus);
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

    if (this->focus == nullptr) return;

    if (this->focus->drawable == this->easy) {
        ctx->setBoxColor(ColorPair(COLOR_GREEN));
    } else if (this->focus->drawable == this->normal) {
        ctx->setBoxColor(ColorPair(COLOR_YELLOW));
    } else if (this->focus->drawable == this->hard) {
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
