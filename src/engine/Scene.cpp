#include "Scene.h"
#include "Actionable.h"

Scene::Scene() {
    this->h_drawables = nullptr;
    this->t_drawables = nullptr;
    this->size = 0;
    this->focus = nullptr;
    this->startX = 0, this->startY = 0;
}

void Scene::add(Drawable *drawable) {
    const auto l = new list{drawable, nullptr, nullptr};
    if (this->h_drawables == nullptr) {
        this->h_drawables = l;
        this->t_drawables = l;
    } else {
        this->t_drawables->next = l;
        l->prev = this->t_drawables;
        this->t_drawables = l;
    }
    this->size++;
}

Drawable *Scene::get(int idx) const {
    p_list l = this->h_drawables;
    while (idx > 0 && l != nullptr) {
        l = l->next;
        idx--;
    }
    if (l == nullptr) return nullptr;
    return l->drawable;
}

void Scene::focusUp() {
    if (this->focus != nullptr) {
        this->focus->drawable->setHover(false);
        this->focus = this->focus->prev;
    }
    if (this->focus == nullptr) {
        this->focus = this->t_drawables;
    }

    bool loop = false;
    while (this->focus != nullptr) {
        if (dynamic_cast<Actionable *>(this->focus->drawable) != nullptr && this->focus->drawable->isVisible()) {
            this->focus->drawable->setHover(true);
            break;
        }
        this->focus = this->focus->prev;
        if (this->focus == nullptr && !loop) {
            loop = true;
            this->focus = this->t_drawables;
        }
    }
}

void Scene::focusDown() {
    if (this->focus != nullptr) {
        this->focus->drawable->setHover(false);
        this->focus = this->focus->next;
    }
    if (this->focus == nullptr) {
        this->focus = this->h_drawables;
    }

    bool loop = false;
    while (this->focus != nullptr) {
        if (dynamic_cast<Actionable *>(this->focus->drawable) != nullptr && this->focus->drawable->isVisible()) {
            this->focus->drawable->setHover(true);
            break;
        }
        this->focus = this->focus->next;
        if (this->focus == nullptr && !loop) {
            loop = true;
            this->focus = this->h_drawables;
        }
    }
}

Scene::~Scene() = default;

void Scene::draw(DrawContext *ctx) {
    p_list l = this->h_drawables;
    while (l != nullptr) {
        if (l->drawable->isVisible()) {
            l->drawable->draw(ctx);
        }
        l = l->next;
    }
}

void Scene::init(InitContext &ctx) {
    this->startX = ctx.getStartX(), this->startY = ctx.getStartY();
}

void Scene::run(RunContext *ctx) {
    switch (ctx->getInput()) {
        case UP:
            this->focusUp();
            break;
        case DOWN:
            this->focusDown();
            break;
        case CONFIRM:
            if (this->focus != nullptr) {
                if (const auto actionable = dynamic_cast<Actionable *>(this->focus->drawable);
                    actionable != nullptr) {
                    actionable->action(ctx);
                }
            }
            break;
        case CLICKED:
            const int *position = ctx->getMousePosition();
            this->click(ctx, position[0] - this->startX, position[1] - this->startY);
            break;
    }
}

void Scene::click(RunContext *ctx, const int x, const int y) {
    if (this->focus != nullptr) {
        this->focus->drawable->setHover(false);
        this->focus = nullptr;
    }
    p_list l = this->h_drawables;
    while (l != nullptr) {
        Drawable *drawable = l->drawable;
        const int *position = drawable->getPosition();
        const int drawX = position[0];
        const int drawY = position[1];
        if (x >= drawX && x < drawX + drawable->width()
            && (y >= drawY && y < drawY + drawable->height())) {
            if (auto *actionable = dynamic_cast<Actionable *>(drawable);
                actionable != nullptr) {
                drawable->setHover(true);
                this->focus = l;
                actionable->action(ctx);
                return;
            }
        }
        l = l->next;
    }
}

const char *Scene::getTitle() {
    return "Scene";
}

int Scene::getCenteredX(Drawable *drawable) {
    const auto x = 80 - drawable->width();
    return x % 2 ? x / 2 : (x - 1) / 2;
}
