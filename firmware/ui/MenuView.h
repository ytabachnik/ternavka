#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include "BaseUIView.h"
#include <iostream>

class MenuView : public BaseUIView
{
public:
    MenuView(BaseUIModel* model) :
        BaseUIView(model)
        {
        }

    void render() override {
        // Implement rendering logic for the menu view
        std::cout << "Rendering Menu View" << std::endl;
    }
};

#endif // MENU_VIEW_H
