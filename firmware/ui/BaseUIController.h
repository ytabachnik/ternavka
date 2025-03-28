#ifndef BASE_UI_CONTROLLER_H
#define BASE_UI_CONTROLLER_H

class BaseUIModel;
class BaseUIView;

#include "hal/KeyboardManager.h"
#include <string>

class BaseUIController
{
public:
    BaseUIController(const std::string& name, BaseUIModel* model, BaseUIView* view)
        : name(name), model(model), view(view)
    {
    }

    virtual void handleKeyStateChanged(KeyboardManager::KeyID keyID) = 0;

    virtual void display() = 0;
    virtual void update();

    virtual ~BaseUIController() = default;

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
    BaseUIModel* model;
    BaseUIView* view;
};

#endif // BASE_MENU_COMPONENT_H
