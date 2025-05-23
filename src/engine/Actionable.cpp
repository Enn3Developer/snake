#include "Actionable.h"

Actionable::~Actionable() = default;

bool Actionable::action(RunContext *ctx) {
    return false;
}
