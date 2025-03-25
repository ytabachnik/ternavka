#include "SystemMenu.h"

SystemMenu::SystemMenu() : activeMenu(nullptr) {}

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
