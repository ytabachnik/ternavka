#include "DialogController.h"
#include <iostream>

DialogController::DialogController(const std::string& name, BaseUIModel* model, BaseUIView* view)
    : BaseUIController(name, model, view)
{
}

// Dialogs are always Terminal.
bool DialogController::isTerminal() const
{
    return true;
}

// Override virtual methods
void DialogController::onEntered() {
    std::cout << name << " dialog entered." << std::endl;
}

void DialogController::onSelected() {
    std::cout << name << " dialog selected." << std::endl;
}

void DialogController::onDeselected() {
    std::cout << name << " dialog deselected." << std::endl;
}
