#include "BaseUIController.h"
#include "BaseUIView.h"

void BaseUIController::update()
{
    view->update();
}
