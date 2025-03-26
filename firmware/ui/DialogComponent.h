#ifndef DIALOG_COMPONENT_H
#define DIALOG_COMPONENT_H

#include "BaseMenuComponent.h"
#include <string>

class DialogComponent : public BaseMenuComponent
{
public:
    DialogComponent(const std::string& name, BaseModel* model, BaseView* view);
    void handleKeyStateChanged(int8_t keyIndex) override;
    void display() override;

    // Method to distinguish between menus and dialogs
    bool isTerminal() const override;

        // Override virtual methods
        void onEntered() override;
        void onSelected() override;
        void onDeselected() override;
};

#endif // DIALOG_COMPONENT_H
