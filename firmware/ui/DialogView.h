#ifndef DIALOG_VIEW_H
#define DIALOG_VIEW_H

#include <iostream>
#include "BaseView.h"

class DialogView : public BaseView {
public:
    DialogView(BaseModel* model, BaseController* controller)
        : BaseView(model, controller) {}

    void render() override {
        // Implement rendering logic for the dialog view
        std::cout << "Rendering Dialog View" << std::endl;
    }
};

#endif // DIALOG_VIEW_H
