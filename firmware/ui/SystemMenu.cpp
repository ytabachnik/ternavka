#include "SystemMenu.h"
#include <iostream>

SystemMenu::SystemMenu(BaseModel* model, BaseView* view)
    : MenuComponent("System Menu", model, view), activeMenu(nullptr)
{
}

void SystemMenu::setActiveMenu(MenuComponent* menu)
{
    activeMenu = menu;
}

void SystemMenu::handleKeyStateChanged(int8_t keyIndex)
{
    if (activeMenu)
    {
        activeMenu->handleKeyStateChanged(keyIndex);
        display();
    }
}

void SystemMenu::display() {
    if (activeMenu) {
        activeMenu->display();
    }
}

void SystemMenu::update() {
    if (activeMenu) {
        activeMenu->update();
    }
}

void SystemMenu::onAttemptToScrollBeforeFirstMenuItem() {
    std::cout << "Attempted to scroll before the first menu item." << std::endl;
}

void SystemMenu::onAttemptToScrollAfterLastMenuItem() {
    std::cout << "Attempted to scroll after the last menu item." << std::endl;
}
