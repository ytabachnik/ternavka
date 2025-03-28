#include "SystemMenu.h"
#include <iostream>

SystemMenu::SystemMenu(BaseUIModel* model, BaseUIView* view)
    : MenuController("System Menu", model, view), activeMenu(nullptr)
{
}

void SystemMenu::setActiveMenu(MenuController* menu)
{
    if (activeMenu)
    {
        activeMenu->onDeselected();
    }

    activeMenu = menu;

    if (activeMenu)
    {
        activeMenu->onSelected();
    }
}

void SystemMenu::handleKeyStateChanged(uint8_t keyIndex)
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
