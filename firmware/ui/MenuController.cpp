#include <iostream>
#include <algorithm>

#include "MenuController.h"
#include "KeyboardManager.h"

MenuController::MenuController(const std::string& name, BaseUIModel* model, BaseUIView* view,
    bool mainMenu) :
    BaseUIController(name, model, view), parent(nullptr), isMainMenu(mainMenu),
    currentSubController(nullptr), currentSubControllerIndex(0)
{
}

// Menu Components are NEVER Terminal.
bool MenuController::isTerminal() const
{
    return false;
}

void MenuController::add(BaseUIController* subController)
{
    subControllers.push_back(subController);
}

int8_t MenuController::activate(BaseUIController* subController)
{
    auto elemIter = std::find(subControllers.begin(), subControllers.end(), subController);
    if (elemIter == subControllers.end()) return -1; // No such element.

    int index = std::distance(subControllers.begin(), elemIter);

    // Deactivate the previous one, if exists.
    if (currentSubController)
    {
        deactivateAndDeselectCurrentSubcontroller();
    }

    currentSubController = subController;
    currentSubControllerIndex = index;

    activateAndSelectCurrentSubcontroller();
    return index;
}

bool MenuController::handleKeyStateChanged(KeyboardManager::KeyID keyID)
{
    // Ask the controller to handle keypress by itself firstly.
    if (currentSubController && currentSubController->isActive() &&
        currentSubController->handleKeyStateChanged(keyID))
    {
        return true;
    }

    switch (keyID)
    {
        case KeyboardManager::KeyID::Key1:
        {
            return prevKeyStateChanged();
        }

        case KeyboardManager::KeyID::Key2:
        {
            return nextKeyStateChanged();
        }

        case KeyboardManager::KeyID::Key5:
        {
            return OKKeyStateChanged();
        }

        case KeyboardManager::KeyID::Key6:
        {
            return cancelKeyStateChanged();
        }

        default: return false;
    }
}

void MenuController::handleKeyPressed(KeyboardManager::KeyID keyID, uint32_t timeSincePress)
{
    // Menu Controller does not perform any handling for pressed (and hold) key for now.
    if (currentSubController)
    {
        currentSubController->handleKeyPressed(keyID, timeSincePress);
    }
}

// "Prev" key state is changed.
bool MenuController::prevKeyStateChanged()
{
    if (subControllers.empty()) return false;

    if (currentSubControllerIndex == 0)
    {
        // No way to continue scrolling left.
        onAttemptToScrollBeforeFirstMenuItem();
        return false;
    }

    deactivateAndDeselectCurrentSubcontroller();
    currentSubControllerIndex --;
    currentSubController = subControllers[currentSubControllerIndex];
    activateAndSelectCurrentSubcontroller();

    return true;
}

// "Next" key state is changed.
bool MenuController::nextKeyStateChanged()
{
    if (subControllers.empty()) return false;

    if (currentSubControllerIndex == subControllers.size() - 1)
    {
        onAttemptToScrollAfterLastMenuItem();
        return false;
    }

    deactivateAndDeselectCurrentSubcontroller();
    currentSubControllerIndex++;
    currentSubController = subControllers[currentSubControllerIndex];
    activateAndSelectCurrentSubcontroller();

    return true;
}

void MenuController::deactivateAndDeselectCurrentSubcontroller()
{
    if (!currentSubController) return;

    if (currentSubController->isTerminal())
    {
        // Deactivating terminals automatically.
        currentSubController->setActive(false);
        currentSubController->onExited();
    }

    // Deselect all types of controllers.
    currentSubController->onDeselected();
}

void MenuController::activateAndSelectCurrentSubcontroller()
{
    if (!currentSubController) return;

    // Select all types of controllers.
    subControllers[currentSubControllerIndex]->onSelected();

    // Activate terminals automatically.
    if (currentSubController->isTerminal())
    {
        // Activating it automatically.
        currentSubController->setActive(true);
        currentSubController->onEntered();
    }
}

bool MenuController::OKKeyStateChanged()
{
    if (!subControllers.empty() && !currentSubController->isActive())
    {
        currentSubController->setActive(true);
        currentSubController->onEntered();

        return true;
    }

    return false;
}

bool MenuController::cancelKeyStateChanged()
{
    // Nowhere to exit from Main Menu.
    if (isMainMenu) return false;

    if (parent)
    {
        // Deactivating ourselves.
        onExited();
        setActive(false);
        parent->currentSubController = nullptr;

        parent->onEntered(); // Ensure parent menu is re-entered

        return true;
    }

    return false;
}

// Override virtual methods
void MenuController::onEntered()
{
    std::cout << name << " entered." << std::endl;
}

void MenuController::onExited()
{
    std::cout << name << " exited." << std::endl;
}

void MenuController::onSelected()
{
    std::cout << name << " selected." << std::endl;
}

void MenuController::onDeselected()
{
    std::cout << name << " deselected." << std::endl;
}

void MenuController::onAttemptToScrollBeforeFirstMenuItem()
{
    std::cout << name << " SCROLL TOO LEFT." << std::endl;
}

void MenuController::onAttemptToScrollAfterLastMenuItem()
{
    std::cout << name << " SCROLL TOO RIGHT." << std::endl;
}
