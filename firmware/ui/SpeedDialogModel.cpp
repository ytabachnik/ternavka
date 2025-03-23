#include "SpeedDialogModel.h"

SpeedDialogModel::SpeedDialogModel(const std::string& name, int initialSpeed) : name(name), speed(initialSpeed) {}

void SpeedDialogModel::increaseSpeed() {
    speed++;
    update();
}

void SpeedDialogModel::decreaseSpeed() {
    speed--;
    update();
}

std::string SpeedDialogModel::getName() const {
    return name;
}

int SpeedDialogModel::getSpeed() const {
    return speed;
}

void SpeedDialogModel::update() {
    // Update logic for SpeedDialogModel
}
