#include "SubmenuView.h"
#include <iostream>

SubmenuView::SubmenuView(SubmenuModel* model) : model(model) {}

void SubmenuView::render() {
    if (model->getActive()) {
        std::cout << "Submenu: " << model->getName() << std::endl;
        model->getItems()[model->getCurrentIndex()]->getView()->render();
    }
}
