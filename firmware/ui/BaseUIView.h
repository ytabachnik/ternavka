#ifndef BASE_UI_VIEW_H
#define BASE_UI_VIEW_H

#include <pico/stdlib.h>

class BaseUIModel;

/// @brief Base class for UI views.
class BaseUIView
{
public:
    BaseUIView(BaseUIModel* model) : model(model)
    {
    }

    virtual void update();

    // Render the particular section.
    virtual void render(uint8_t sectionIndex) {};

protected:
    BaseUIModel* model;
};

#endif // BASE_UI_VIEW_H
