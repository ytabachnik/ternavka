#ifndef BASE_MENU_COMPONENT_H
#define BASE_MENU_COMPONENT_H

class BaseModel;
class BaseView;

#include <string>

class BaseMenuComponent
{
public:
    BaseMenuComponent(const std::string& name, BaseModel* model, BaseView* view)
        : name(name), model(model), view(view)
    {
    }

    virtual void handleKeyStateChanged(int8_t keyIndex) = 0;
    virtual void display() = 0;
    virtual void update();

    virtual ~BaseMenuComponent() = default;

    // Method to distinguish between menus and dialogs
    virtual bool isTerminal() const = 0;

    // Virtual methods for menu actions
    virtual void onEntered() {}
    virtual void onExited() {}
    virtual void onSelected() {}
    virtual void onDeselected() {}

    const std::string getName() const{ return name; }

protected:
    std::string name;
    BaseModel* model;
    BaseView* view;
};

#endif // BASE_MENU_COMPONENT_H
