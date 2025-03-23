#include "DialogModel.h"

DialogModel::DialogModel(const std::string& name) : name(name), mode(MAIN) {}

void DialogModel::setMode(DialogMode newMode) {
    mode = newMode;
    update();
}

std::string DialogModel::getName() const {
    return name;
}

DialogMode DialogModel::getMode() const {
    return mode;
}

void DialogModel::update() {
    // Update logic for DialogModel
}