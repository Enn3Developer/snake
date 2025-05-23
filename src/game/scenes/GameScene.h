#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "../../engine/Scene.h"
#include "../../engine/components/Modal.h"

class GameScene final : public Scene {
private:
    bool modal_open = false;
    bool modal_confirm = false;
    Modal modal;

public:
    GameScene();

    const char *getTitle() override;

    bool onEscape(RunContext *ctx) override;
};

#endif
