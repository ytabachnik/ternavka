#ifndef SYSTEM_MENU_H
#define SYSTEM_MENU_H

#include "MenuComponent.h"

class SystemMenu {
public:
    SystemMenu();
    void setActiveMenu(MenuComponent* menu);

    void handleKeyStateChanged(int8_t keyIndex);
    void display();

private:
    MenuComponent* activeMenu;
};

#endif // SYSTEM_MENU_H
