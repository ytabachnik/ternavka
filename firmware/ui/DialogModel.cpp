#include "DialogModel.h"

DialogModel::DialogModel(const std::string& name) : Model(name), mode(MAIN) 
{
}

void DialogModel::setMode(DialogMode newMode) {
    mode = newMode;
    update();
}

DialogMode DialogModel::getMode() const {
    return mode;
}

void DialogModel::update() {
    // Update logic for DialogModel
}