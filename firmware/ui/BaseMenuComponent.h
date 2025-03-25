#ifndef BASE_MENU_COMPONENT_H
#define BASE_MENU_COMPONENT_H

#include <pico/stdlib.h>
#include <string>

class BaseMenuComponent
{
public:
    BaseMenuComponent(const std::string& name)
    {
        this->name = name;
    }

    virtual void handleKeyStateChanged(int8_t keyIndex) = 0;
    virtual void display() = 0;
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
};

#endif // BASE_MENU_COMPONENT_H
