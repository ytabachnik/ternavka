#include "SpeedDialogController.h"

SpeedDialogController::SpeedDialogController(SpeedDialogModel* model, SpeedDialogView* view) : model(model), view(view) {}

void SpeedDialogController::handleButtonPress(int button) {
    if (button == 4) {
        model->increaseSpeed();
    } else if (button == 5) {
        model->decreaseSpeed();
    }
    view->render();
}
