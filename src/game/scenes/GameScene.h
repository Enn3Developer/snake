#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "../../engine/Scene.h"
#include "../../engine/components/Modal.h"

class GameScene final : public Scene {
private:
    Modal modal;

public:
    GameScene();

    const char *getTitle() override;

    void run(RunContext *ctx) override;

    bool onEscape(RunContext *ctx) override;
};

#endif
