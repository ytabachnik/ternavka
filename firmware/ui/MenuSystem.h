#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

#include <vector>
#include "MenuComponent.h"

class MenuSystem {
private:
    MenuComponent* rootMenuComponent;

public:
    MenuSystem();
    MenuSystem(MenuComponent* root);

    // Set the menu root.
    void setRoot(MenuComponent* root);

    // Handle the key state changed.
    void handleKeyStateChanged(int8_t keyIndex)
    {
        rootMenuComponent->handleKeyStateChanged(keyIndex);
    }
};

#endif // MENUSYSTEM_H
