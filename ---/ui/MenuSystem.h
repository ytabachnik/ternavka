#ifndef MENUSYSTEM_H
#define MENUSYSTEM_H

#include <vector>
#include "BaseMenuComponent.h"

class MenuSystem {
private:
    BaseMenuComponent* rootMenuComponent;

public:
    MenuSystem();
    MenuSystem(BaseMenuComponent* root);

    // Set the menu root.
    void setRoot(BaseMenuComponent* root);

    // Handle the key state changed.
    void handleKeyStateChanged(int8_t keyIndex)
    {
        rootMenuComponent->handleKeyStateChanged(keyIndex);
    }
};

#endif // MENUSYSTEM_H
