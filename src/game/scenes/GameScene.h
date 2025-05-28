#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "../../engine/Scene.h"
#include "../../engine/components/Alert.h"
#include "../../engine/components/Modal.h"
#include "../components/Snake.h"

#define ONE_MINUTE 60000
#define FIVE_MINUTES 300000

class Label;

class GameScene final : public Scene {
private:
    Modal *modal;
    Snake *snake;
    Label *pointsLabel;
    Alert *alert;
    Label *timerLabel;
    int points;
    char *pointsStr;
    char *timerStr;
    int timer;
    int bonusPoints;

public:
    GameScene();

    void setBonusPoints(int bonusPoints);

    const char *getTitle() override;

    void run(RunContext *ctx) override;

    bool onEscape(RunContext *ctx) override;
};

#endif
