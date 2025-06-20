#include "RunContext.h"

#include "DrawContext.h"

RunContext::RunContext() {
    // valori di default del RunContext
    this->input = NONE;
    this->switchScene = nullptr;
    this->exit = false;
    this->redraw = false;
    this->x = 0, this->y = 0;
    this->boxColor = DEFAULT_COLOR_PAIR;
}

RunContext::~RunContext() = default;

void RunContext::setInput(const InputKind input) {
    this->input = input;
}

void RunContext::setMousePosition(const int x, const int y) {
    this->x = x, this->y = y;
}

InputKind RunContext::getInput() const {
    return this->input;
}

int RunContext::getMouseX() {
    return this->x;
}

int RunContext::getMouseY() {
    return this->y;
}

int *RunContext::getMousePosition() const {
    return new int[]{this->x, this->y};
}

void RunContext::queueExit() {
    this->exit = true;
}

void RunContext::queueScene(Scene *scene) {
    this->switchScene = scene;
}

void RunContext::forceRedraw() {
    this->redraw = true;
}

bool RunContext::exitQueued() const {
    return this->exit;
}

bool RunContext::sceneQueued() const {
    return this->switchScene != nullptr;
}

bool RunContext::redrawForced() const {
    return this->redraw;
}

Scene *RunContext::newScene() const {
    return this->switchScene;
}

void RunContext::setBoxColor(ColorPair color) {
    this->boxColor = color;
}

ColorPair RunContext::getBoxColor() {
    return this->boxColor;
}
