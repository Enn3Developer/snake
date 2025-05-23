#ifndef LEADERBOARDSCENE_H
#define LEADERBOARDSCENE_H
#include "../../engine/Scene.h"
#include "../../engine/components/Label.h"
#include "../../engine/components/Scrollable.h"

class LeaderboardScene final : public Scene {
private:
    Label testLabel;
    Scrollable scrollable;

public:
    LeaderboardScene();

    const char *getTitle() override;
};

#endif
