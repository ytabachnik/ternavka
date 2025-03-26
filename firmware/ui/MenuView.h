#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include "BaseView.h"
#include <iostream>

class MenuView : public BaseView {
public:
    MenuView(BaseModel* model, BaseController* controller)
        : BaseView(model, controller) {}

    void render() override {
        // Implement rendering logic for the menu view
        std::cout << "Rendering Menu View" << std::endl;
    }
};

#endif // MENU_VIEW_H
