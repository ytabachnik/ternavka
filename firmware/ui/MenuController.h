#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include "BaseUIController.h"
#include <vector>
#include <string>

class MenuController : public BaseUIController {
public:
    MenuController(const std::string& name, BaseUIModel* model, BaseUIView* view);

    // Add the subcontroller.
    void add(BaseUIController* subController);

    // Set the particular subcontroller as active.
    void setActive(BaseUIController* subController);

    void handleKeyStateChanged(uint8_t keyIndex) override;
    void display() override;

    void update() override
    {
        BaseUIController::update();

        if (activeSubcontroller)
        {
            activeSubcontroller->update();
        }
    }
    
    // Method to distinguish between menus and dialogs
    bool isTerminal() const override;

    // Override virtual methods
    void onEntered() override;
    void onExited() override;
    void onSelected() override;
    void onDeselected() override;

    // Handling of the "scroll to left/scroll too right" methods.
    virtual void onAttemptToScrollBeforeFirstMenuItem();
    virtual void onAttemptToScrollAfterLastMenuItem();

protected:
    // Key state changed handlers.
    // "Prev" key state is changed.
    bool prevKeyStateChanged();
    bool nextKeyStateChanged();
    bool OKKeyStateChanged();
    bool cancelKeyStateChanged();

    // Select active Subcontrol as Terminal.
    void selectActiveSubcontrollerIfTerminal();

private:
    MenuController* parent;
    std::vector<BaseUIController*> subControllers;
    BaseUIController* activeSubcontroller;
    size_t selectedIndex;
};

#endif // MENU_CONTROLLER_H
