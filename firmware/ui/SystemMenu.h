#ifndef SYSTEM_MENU_H
#define SYSTEM_MENU_H

#include "MenuComponent.h"

class SystemMenu : public MenuComponent {
public:
    SystemMenu(BaseModel* model, BaseView* view);
    void setActiveMenu(MenuComponent* menu);
    void handleKeyStateChanged(int8_t keyIndex);
    void display();
    void update();

    // Override virtual methods for scrolling
    void onAttemptToScrollBeforeFirstMenuItem() override;
    void onAttemptToScrollAfterLastMenuItem() override;

private:
    MenuComponent* activeMenu;
};

#endif // SYSTEM_MENU_H
