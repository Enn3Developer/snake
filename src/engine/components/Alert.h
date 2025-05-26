#ifndef ALERT_H
#define ALERT_H
#include "../Actionable.h"
#include "../Drawable.h"

class Alert final : public Drawable, public Actionable {
private:
    const char *msg;
    bool open;
    int color_id;

public:
    Alert();

    void setMsg(const char *msg);

    bool isOpen();

    void openAlert();

    void closeAlert();

    int width() override;

    int height() override;

    void draw(DrawContext *ctx) override;

    bool action(RunContext *ctx) override;
};

#endif
