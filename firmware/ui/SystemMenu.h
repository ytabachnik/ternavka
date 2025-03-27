#ifndef SYSTEM_MENU_H
#define SYSTEM_MENU_H

#include "MenuController.h"

class SystemMenu : public MenuController
{
public:
    SystemMenu(BaseUIModel* model, BaseUIView* view);
    void setActiveMenu(MenuController* menu);
    void handleKeyStateChanged(int8_t keyIndex);
    void display();
    void update();

    // Override virtual methods for scrolling
    void onAttemptToScrollBeforeFirstMenuItem() override;
    void onAttemptToScrollAfterLastMenuItem() override;

private:
    MenuController* activeMenu;
};

#endif // SYSTEM_MENU_H
