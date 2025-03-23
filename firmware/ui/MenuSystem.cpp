#include "MenuSystem.h"

MenuSystem::MenuSystem() : currentIndex(0) {}

void MenuSystem::addComponent(MenuComponent* component) {
    components.push_back(component);
}

void MenuSystem::switchTo(int index) {
    if (index >= 0 && index < components.size()) {
        components[currentIndex]->getModel()->update();
        currentIndex = index;
        components[currentIndex]->getModel()->update();
    }
}

void MenuSystem::handleButtonPress(int button) {
    if (currentIndex >= 0 && currentIndex < components.size()) {
        components[currentIndex]->getController()->handleButtonPress(button);
    }
}

void MenuSystem::displayCurrent() {
    if (currentIndex >= 0 && currentIndex < components.size()) {
        components[currentIndex]->getView()->render();
    }
}