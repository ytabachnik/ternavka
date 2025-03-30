#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include "BaseUIController.h"
#include <vector>
#include <string>

class MenuController : public BaseUIController
{
public:
    MenuController(const std::string& name, BaseUIModel* model, BaseUIView* view,
        bool mainMenu);

    // Add the subcontroller.
    void add(BaseUIController* subController);

    // Activate the controller previously added, returns it index.
    int8_t activate(BaseUIController* subController);

    bool handleKeyStateChanged(KeyboardManager::KeyID keyID) override;
    void handleKeyPressed(KeyboardManager::KeyID keyID, uint32_t timeSincePress) override;

    // Call periodically to update system internals.
    void update() override
    {
        BaseUIController::update();

        if (currentSubController)
        {
            currentSubController->update();
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

    // Check/set whether next-level menu is active.
    bool isNextLevelMenuActive();
    bool setNextLevelMenuActive(bool value);

    // Activation/Selection stuff.
    void deactivateAndDeselectCurrentSubcontroller();
    void activateAndSelectCurrentSubcontroller();

private:
    bool isMainMenu;
    MenuController* parent;

    std::vector<BaseUIController*> subControllers;
    BaseUIController* currentSubController;
    size_t currentSubControllerIndex;
};

#endif // MENU_CONTROLLER_H
