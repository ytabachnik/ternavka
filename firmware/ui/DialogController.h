#ifndef DIALOG_COMPONENT_H
#define DIALOG_COMPONENT_H

#include "BaseUIController.h"
#include <string>

class DialogController : public BaseUIController
{
public:
    DialogController(const std::string& name, BaseUIModel* model, BaseUIView* view);
    void handleKeyStateChanged(uint8_t keyIndex) override;
    void display() override;

    // Method to distinguish between menus and dialogs
    bool isTerminal() const override;

        // Override virtual methods
        void onEntered() override;
        void onSelected() override;
        void onDeselected() override;
};

#endif // DIALOG_COMPONENT_H
