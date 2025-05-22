#ifndef MAINSCENE_H
#define MAINSCENE_H
#include "../../engine/Scene.h"
#include "../../engine/components/Button.h"

class MainScene final : public Scene {
private:
    Button newGameBtn;
    Button leaderboardBtn;
    Button exitBtn;

public:
    MainScene();

    const char *getTitle() override;
};

void onExit(RunContext *ctx);

#endif
