#include "SubmenuController.h"

SubmenuController::SubmenuController(SubmenuModel* model, SubmenuView* view) : model(model), view(view) {}

void SubmenuController::handleButtonPress(int button) {
    if (button == 2 && model->getCurrentIndex() > 0) {
        model->setCurrentIndex(model->getCurrentIndex() - 1);
    } else if (button == 3 && model->getCurrentIndex() < model->getItems().size() - 1) {
        model->setCurrentIndex(model->getCurrentIndex() + 1);
    } else if (button == 6) {
        // Handle OK button to go deeper into nested menu
        model->setActive(false);
        MenuComponent* currentItem = model->getItems()[model->getCurrentIndex()];
        currentItem->getModel()->update();
        currentItem->getController()->handleButtonPress(button);
    } else if (button == 7) {
        // Handle Back button to go up one level
        model->setActive(true);
    }
    view->render();
}