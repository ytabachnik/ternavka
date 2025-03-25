#ifndef MENU_COMPONENT_H
#define MENU_COMPONENT_H

#include "BaseMenuComponent.h"
#include <vector>
#include <string>

class MenuComponent : public BaseMenuComponent {
public:
    MenuComponent(const std::string& name);
    void addSubMenu(BaseMenuComponent* subMenu);

    void handleKeyStateChanged(int8_t keyIndex) override;
    void display();

    // Method to distinguish between menus and dialogs
    bool isTerminal() const override;

    // New methods
    virtual void onEntered();
    virtual void onExited();
    virtual void onSelected();
    virtual void onDeselected();

private:
    MenuComponent* parent;
    std::vector<BaseMenuComponent*> subMenus;
    BaseMenuComponent* activeSubMenu;
    size_t selectedIndex;
};

#endif // MENU_COMPONENT_H
