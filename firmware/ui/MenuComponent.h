#ifndef MENU_COMPONENT_H
#define MENU_COMPONENT_H

#include "BaseMenuComponent.h"
#include <vector>
#include <string>

class MenuComponent : public BaseMenuComponent {
public:
    MenuComponent(const std::string& name, BaseModel* model, BaseView* view);
    void addSubMenu(BaseMenuComponent* subMenu);
    void handleKeyStateChanged(int8_t keyIndex) override;
    void display() override;

    // Method to distinguish between menus and dialogs
    bool isTerminal() const override;

    // Override virtual methods
    void onEntered() override;
    void onExited() override;
    void onSelected() override;
    void onDeselected() override;

    // Handling of the "scroll to left/scroll too right" methods.
    virtual void onAttemptToScrollBeforeFirstMenuItem();
    virtual void onAttemptToScrollAfterLastMenuItem();

private:
    MenuComponent* parent;
    std::vector<BaseMenuComponent*> subMenus;
    BaseMenuComponent* activeSubMenu;
    size_t selectedIndex;
};

#endif // MENU_COMPONENT_H
