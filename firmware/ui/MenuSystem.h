#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

#include <vector>
#include "MenuComponent.h"

class MenuSystem {
private:
    std::vector<MenuComponent*> components;
    int currentIndex;
public:
    MenuSystem();
    void addComponent(MenuComponent* component);
    void switchTo(int index);
    void handleButtonPress(int button);
    void displayCurrent();
};

#endif // MENUSYSTEM_H
