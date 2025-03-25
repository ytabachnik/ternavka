#include "SpeedDialogView.h"
#include <iostream>

SpeedDialogView::SpeedDialogView(SpeedDialogModel* model) : model(model) {}

void SpeedDialogView::render() {
    std::cout << "Speed Dialog: " << model->getName() << " Speed: " << model->getSpeed() << std::endl;
}