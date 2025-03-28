#ifndef DIALOG_VIEW_H
#define DIALOG_VIEW_H

#include <pico/stdlib.h>
#include <iostream>
#include "BaseUIView.h"

class DialogView : public BaseUIView {
public:
    DialogView(BaseUIModel* model) : BaseUIView(model)
    {
    }

    void render(uint8_t sectionIndex) override
    {
        // Implement rendering logic for the dialog view
        std::cout << "Rendering Dialog View Section " << sectionIndex << std::endl;
    }
};

#endif // DIALOG_VIEW_H
