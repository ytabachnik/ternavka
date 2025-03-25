#include "DialogView.h"
#include <iostream>

DialogView::DialogView(DialogModel* model) : model(model) {}

void DialogView::render() {
    std::cout << "Dialog: " << model->getName() << " Mode: " << model->getMode() << std::endl;
}
