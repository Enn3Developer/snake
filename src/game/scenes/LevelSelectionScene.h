#ifndef LEVELSELECTIONSCENE_H
#define LEVELSELECTIONSCENE_H
#include "../../engine/Scene.h"
#include "../../engine/components/Button.h"

class LevelSelectionScene final : public Scene {
private:
    Button *easy;
    Button *normal;
    Button *hard;
    Button *impossible;
    Button *god;

public:
    LevelSelectionScene();

    void run(RunContext *ctx) override;

    bool onEscape(RunContext *ctx) override;

    const char *getTitle() override;
};

#endif
