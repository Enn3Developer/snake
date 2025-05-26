#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "../../engine/Scene.h"
#include "../../engine/components/Alert.h"
#include "../../engine/components/Modal.h"
#include "../components/Snake.h"

class Label;

class GameScene final : public Scene {
private:
    Modal modal;
    Snake *snake;
    Label *pointsLabel;
    Alert *alert;
    int points;
    char *pointsStr;

public:
    GameScene();

    const char *getTitle() override;

    void run(RunContext *ctx) override;

    bool onEscape(RunContext *ctx) override;
};

#endif
