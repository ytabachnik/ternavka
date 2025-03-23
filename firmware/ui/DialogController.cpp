#include "DialogController.h"

DialogController::DialogController(DialogModel* model, DialogView* view) : model(model), view(view) {}

void DialogController::handleButtonPress(int button) {
    if (button == 6) {
        model->setMode(GREEN);
    } else if (button == 7) {
        model->setMode(BLUE);
    }
    view->render();
}
