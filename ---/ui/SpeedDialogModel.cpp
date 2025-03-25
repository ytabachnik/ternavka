#include "SpeedDialogModel.h"

SpeedDialogModel::SpeedDialogModel(const std::string& name, int initialSpeed) :
    Model(name),
    speed(initialSpeed)
{
}

void SpeedDialogModel::increaseSpeed()
{
    speed++;
    update();
}

void SpeedDialogModel::decreaseSpeed() {
    speed--;
    update();
}

int SpeedDialogModel::getSpeed() const {
    return speed;
}

void SpeedDialogModel::update() {
    // Update logic for SpeedDialogModel
}
