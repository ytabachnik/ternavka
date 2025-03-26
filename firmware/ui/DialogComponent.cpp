#include "DialogComponent.h"
#include <iostream>

DialogComponent::DialogComponent(const std::string& name, BaseModel* model, BaseView* view)
    : BaseMenuComponent(name, model, view)
{
}

void DialogComponent::handleKeyStateChanged(int8_t keyIndex)
{
    // Dialogs do not handle key presses other than navigation
}

// Dialogs are always Terminal.
bool DialogComponent::isTerminal() const
{
    return true;
}

void DialogComponent::display() {
    std::cout << "Dialog: " << name << std::endl;
}

// Override virtual methods
void DialogComponent::onEntered() {
    std::cout << name << " dialog entered." << std::endl;
}

void DialogComponent::onSelected() {
    std::cout << name << " dialog selected." << std::endl;
}

void DialogComponent::onDeselected() {
    std::cout << name << " dialog deselected." << std::endl;
}
