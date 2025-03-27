#ifndef BASE_UI_VIEW_H
#define BASE_UI_VIEW_H

class BaseUIModel;

/// @brief Base class for UI views.
class BaseUIView
{
public:
    BaseUIView(BaseUIModel* model) : model(model)
    {
    }

    virtual void update();

    virtual void render() = 0;

protected:
    BaseUIModel* model;
};

#endif // BASE_UI_VIEW_H
