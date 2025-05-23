#ifndef MODAL_H
#define MODAL_H
#include "../Actionable.h"
#include "../Drawable.h"

class Modal final : public Drawable, public Actionable {
private:
    const char *message;
    bool *open;
    bool *confirm;

public:
    Modal(const char *message, bool *open, bool *confirm);

    int width() override;

    int height() override;
};

#endif
