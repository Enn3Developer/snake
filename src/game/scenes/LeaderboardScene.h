#ifndef LEADERBOARDSCENE_H
#define LEADERBOARDSCENE_H
#include "../Score.h"
#include "../../engine/Scene.h"
#include "../../engine/components/Button.h"
#include "../../engine/components/Label.h"
#include "../../engine/components/Scrollable.h"

class LeaderboardScene final : public Scene {
private:
    struct list {
        Score score;
        list *next;
    };

    typedef list *p_list;
    p_list head;
    int list_size;

    Scrollable *scrollable;
    Button *menuBtn;

public:
    LeaderboardScene();

    void addScore(Score score);

    const char *getTitle() override;

    bool onEscape(RunContext *ctx) override;
};

#endif
