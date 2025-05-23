#include "LeaderboardScene.h"

LeaderboardScene::LeaderboardScene(): scrollable(1, 20, 20) {
    this->testLabel = *new Label();
    this->testLabel.setText("Test");

    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);
    this->scrollable.add(&testLabel);

    this->scrollable.setPosition(1, 1);

    this->add(&this->scrollable);
}


const char *LeaderboardScene::getTitle() {
    return "Leaderboard";
}
