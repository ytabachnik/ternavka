#ifndef DIALOG_COMPONENT_H
#define DIALOG_COMPONENT_H

#include "BaseMenuComponent.h"
#include <string>

class DialogComponent : public BaseMenuComponent
{
public:
    DialogComponent(const std::string& name);
    void handleKeyStateChanged(int8_t keyIndex) override;
    void display() override;

    // Method to distinguish between menus and dialogs
    bool isTerminal() const override;

    // New methods
    virtual void onEntered();
    virtual void onSelected();
    virtual void onDeselected();
};

#endif // DIALOG_COMPONENT_H
