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
        : name(name), model(model), view(view), isControllerActive(false)
    {
    }

    // Handle the single key state change (once per press).
    virtual bool handleKeyStateChanged(KeyboardManager::KeyID keyID)
    {
        return false;
    };

    // Handle the continious key press
    virtual void handleKeyPressed(KeyboardManager::KeyID keyID, uint32_t timeSincePress) {}

    virtual void update();

    virtual ~BaseUIController() = default;

    // Method to distinguish between menus and dialogs
    virtual bool isTerminal() const = 0;

    // Virtual methods for menu actions
    virtual void onEntered() {}
    virtual void onExited() {}
    virtual void onSelected() {}
    virtual void onDeselected() {}

    // Whether this level is active.
    bool isActive() {return isControllerActive; }
    void setActive(bool value) { isControllerActive = value; }
    
    const std::string getName() const{ return name; }

    // Access to the proper model type.
    template<class T> T* getModel()
    {
        return static_cast<T*>(model);
    }

protected:
    // Activity flag.
    bool isControllerActive;

    std::string name;
    BaseUIModel* model;
    BaseUIView* view;
};

#endif // BASE_MENU_COMPONENT_H
