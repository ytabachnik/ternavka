#ifndef DIALOG_VIEW_H
#define DIALOG_VIEW_H

#include <iostream>
#include "BaseUIView.h"

class DialogView : public BaseUIView {
public:
    DialogView(BaseUIModel* model) : BaseUIView(model)
    {
    }

    void render() override
    {
        // Implement rendering logic for the dialog view
        std::cout << "Rendering Dialog View" << std::endl;
    }
};

#endif // DIALOG_VIEW_H
