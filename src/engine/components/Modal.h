#ifndef MODAL_H
#define MODAL_H
#include "../Actionable.h"
#include "../Drawable.h"

class Modal final : public Drawable, public Actionable {
private:
    const char *message;
    bool open;
    bool confirm;
    bool confirm_focused;
    int color_id;

public:
    Modal(const char *message);

    int width() override;

    int height() override;

    void openModal();

    void closeModal();

    bool isOpen();

    bool isConfirmed();

    bool action(RunContext *ctx) override;

    void draw(DrawContext *ctx) override;
};

#endif
